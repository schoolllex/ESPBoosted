#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_TSL2591.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_NeoPixel.h>

#include "pins_arduino.h"
#define SD_CS_PIN       13
#define NEOPIXEL_PIN    21
#define BUZZER_PIN      12

Adafruit_BME280 bme;
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);
Adafruit_MPU6050 mpu;
Adafruit_ADS1115 ads;
Adafruit_MCP23X17 mcp;
Adafruit_NeoPixel strip(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- Start custom ESP32 board ---");

  Wire.begin();

  strip.begin();
  strip.setBrightness(50);
  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show();

  pinMode(BUZZER_PIN, OUTPUT);
  tone(BUZZER_PIN, 1000, 200);

  if (!bme.begin(0x76)) {
    Serial.println("[Error] BME280 not found!");
  } else {
    Serial.println("[OK] BME280 work.");
  }

  if (!tsl.begin()) {
    Serial.println("[Error] TSL2591 not found!");
  } else {
    Serial.println("[OK] TSL2591 work.");
    tsl.setGain(TSL2591_GAIN_MED);
    tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
  }

  if (!mpu.begin()) {
    Serial.println("[Error] MPU6050 not found!");
  } else {
    Serial.println("[OK] MPU6050 work.");
  }

  if (!ads.begin()) {
    Serial.println("[Error] ADS1115 not found!");
  } else {
    Serial.println("[OK] ADS1115 work.");
  }

  if (!mcp.begin_I2C(0x20)) {
    Serial.println("[Error] MCP23017 not found!");
  } else {
    Serial.println("[OK] MCP23017 work.");
    mcp.pinMode(0, OUTPUT);
  }

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("[Error] SD card missing or fail!");
  } else {
    Serial.println("[OK] SD card ready.");
    uint8_t cardType = SD.cardType();
    if (cardType != CARD_NONE) {
      Serial.printf("SD card size : %llu MB\n", (SD.cardSize() / (1024 * 1024)));
    }
  }

  Serial.println("--- System ready! ---");
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
}

void loop() {
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float press = bme.readPressure() / 100.0F;

  Serial.printf("Temp: %.2f C | Hum: %.2f %% | Press: %.2f hPa\n", temp, hum, press);

  uint32_t lum = tsl.getFullLuminosity();
  uint16_t ir = lum >> 16;
  uint16_t full = lum & 0xFFFF;
  Serial.printf("Light - Lux: %.2f (IR: %d, Full: %d)\n", tsl.calculateLux(full, ir), ir, full);

  sensors_event_t a, g, temp_imu;
  mpu.getEvent(&a, &g, &temp_imu);
  Serial.printf("Accel (m/s^2) -> X: %.2f, Y: %.2f, Z: %.2f\n", a.acceleration.x, a.acceleration.y, a.acceleration.z);

  Serial.println("----------------------------------------");
  delay(3000);
}
