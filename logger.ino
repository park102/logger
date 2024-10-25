#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>

File myFile;

Adafruit_MS8607 ms8607;
void setup(void) {
    pinMode(LED_BUILTIN, OUTPUT);

    // Try to initialize!
    if (!ms8607.begin()) {
        digitalWrite(LED_BUILTIN,HIGH);


        while (1) { delay(10); }
    }

    ms8607.setHumidityResolution(MS8607_HUMIDITY_RESOLUTION_OSR_8b);

    ms8607.setPressureResolution(MS8607_PRESSURE_RESOLUTION_OSR_4096);

  if (!SD.begin(4)) {
    while(true){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
    
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    }
  }

     if (myFile) {


    SD.remove("log.txt");

  }



}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    sensors_event_t temp, pressure, humidity;
    ms8607.getEvent(&pressure, &temp, &humidity);
    myFile = SD.open("log.txt", FILE_WRITE);
    myFile.print("Temp: ");myFile.print(temp.temperature);myFile.println(" c");
    myFile.print("Pressure: ");myFile.print(pressure.pressure); myFile.println(" hPa");
    myFile.print("Humidity: ");myFile.print(humidity.relative_humidity); myFile.println(" %rH");
    
    myFile.println("");
    myFile.close();
    digitalWrite(LED_BUILTIN, LOW);
    delay(10000);
}
