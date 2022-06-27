#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SparkFun_SCD30_Arduino_Library.h" //Click here to get the library: http://librarymanager/All#SparkFun_SCD30
SCD30 airSensor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

uint16_t co2_data;
float temp_data;
float hum_data;

void read_data()
{
  if (airSensor.dataAvailable())
  {
    Serial.print("co2(ppm):");
    co2_data = airSensor.getCO2();
    Serial.print(co2_data);

    Serial.print(" temp(C):");
    temp_data = airSensor.getTemperature();
    Serial.print(temp_data, 1);

    Serial.print(" humidity(%):");
    hum_data = airSensor.getHumidity();
    Serial.print(hum_data, 1);

    Serial.println();
  }
  else
    Serial.println("Waiting for new data");
}

void show_data(void)
{
  display.clearDisplay();
  delay(10);
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(32, 0);
  display.println("Monitoring");
  display.setCursor(10, 20);
  display.print("CO2  : ");
  display.print(co2_data);
  display.println(" PPM");
  display.setCursor(10, 35);
  display.print("Tmp : ");
  display.print(temp_data);
  display.println(" C");
  display.setCursor(10, 50);
  display.print("Hum : ");
  display.print(hum_data);
  display.println(" %");
  display.display(); // Show initial text
}

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  if (airSensor.begin() == false)
  {
    Serial.println("Air sensor not detected. Please check wiring. Freezing...");
    while (1)
      ;
  }
  display.clearDisplay();
}

void loop()
{
  read_data();
  show_data();
  delay(1000);
}