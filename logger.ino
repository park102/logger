#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>

File File;

Adafruit_MS8607 ms8607;
void setup(void) {
    Serial.begin(115200);
    while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

    Serial.println("Adafruit MS8607 test!");

    // Try to initialize!
    if (!ms8607.begin()) {
        Serial.println("Failed to find MS8607 chip");
        while (1) { delay(10); }
    }
    Serial.println("MS8607 Found!");

    ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);

    ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);

    SD.begin(4)

}

void loop() {
    sensors_event_t temp, pressure, humidity;
    ms8607.getEvent(&pressure, &temp, &humidity);
    Serial.print("Temperature: ");Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Pressure: ");Serial.print(pressure.pressure); Serial.println(" hPa");
    Serial.print("Humidity: ");Serial.print(humidity.relative_humidity); Serial.println(" %rH");
    Serial.println("");
    File.open("log.txt", FILE_WRITE);
    File.print("Temp: ");File.print(temp.temperature);File.println(" c")
    File.print("Pressure: ");File.print(pressure.pressure); File.println(" hPa");
    File.print("Humidity: ");File.print(humidity.relative_humidity); File.println(" %rH");
    File.close();
    Serial.println("");

    delay(1000);
}
