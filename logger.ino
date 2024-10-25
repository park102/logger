#include <Wire.h>
#include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <SD.h>

File myFile;

Adafruit_MS8607 ms8607;
void setup(void) {
    pinMode(LED_BUILTIN, OUTPUT);
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

  if (!SD.begin(4)) {
    Serial.println("Card init. failed!");
    while(true){
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
    
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    }
  }
    myFile = SD.open("log.txt"); 

     if (myFile) {


    while (myFile.available()) {


      Serial.write(myFile.read());


    }


    myFile.close();
    SD.remove("log.txt");

  }



}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    sensors_event_t temp, pressure, humidity;
    ms8607.getEvent(&pressure, &temp, &humidity);
    Serial.print("Temperature: ");Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Pressure: ");Serial.print(pressure.pressure); Serial.println(" hPa");
    Serial.print("Humidity: ");Serial.print(humidity.relative_humidity); Serial.println(" %rH");
    Serial.println("");
    myFile = SD.open("log.txt", FILE_WRITE);
    myFile.print("Temp: ");myFile.print(temp.temperature);myFile.println(" c");
    myFile.print("Pressure: ");myFile.print(pressure.pressure); myFile.println(" hPa");
    myFile.print("Humidity: ");myFile.print(humidity.relative_humidity); myFile.println(" %rH");
//    myFile.println("hello world");
    myFile.println("");
    myFile.close();
    Serial.println("");
digitalWrite(LED_BUILTIN, LOW);
    delay(10000);
}
