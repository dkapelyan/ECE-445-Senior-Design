#include <Wire.h>
#include <math.h>

#define SENSOR_ADDR 0x28
#define FULL_MEASURE_CMND 0xAC
#define SENSOR_STATUS_MASK 0xC0000000
#define SENSOR_PRESSURE_MASK 0x3FFF0000
#define SENSOR_TEMPERATURE_MASK 0xFFFF
#define NovaAddr 0x28


unsigned long ps_data;
//int n;
unsigned int data=0, pressure=0, temp=0;
double pressure_converted;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting");
    Wire.begin();
}

void loop() {
    ps_data = 0;
    
    Wire.beginTransmission(SENSOR_ADDR);
    Wire.write(FULL_MEASURE_CMND);
    Wire.endTransmission(false);
    unsigned char n = Wire.requestFrom(SENSOR_ADDR, 4);
    Wire.requestFrom(SENSOR_ADDR, 4);
    for (n; n > 0; n--) {
        ps_data = (ps_data << 8) | Wire.read();
    }
    pressure_converted = ((ps_data & SENSOR_PRESSURE_MASK) >> 16)/pow(2,14)*2.5;

    Serial.print("Status: ");
    Serial.println((ps_data & SENSOR_STATUS_MASK) >> 30);   //SENSOR_STATUS_MASK 0xC0000000
    
    Serial.print("Pressure: ");
    Serial.println((ps_data & SENSOR_PRESSURE_MASK) >> 16);   //SENSOR_PRESSURE_MASK 0x3FFF0000
    
    Serial.print("Pressure PSI: ");
    Serial.println(pressure_converted,8);
    
    Serial.print("Pressure mmHg: ");
    Serial.println(pressure_converted*51.7149,8);


    //Serial.print("Temperature: ");  
    //Serial.println((ps_data & SENSOR_TEMPERATURE_MASK) >> 2);   //SENSOR_TEMPERATURE_MASK 0xFFFF
    Serial.println("=============");
    delay(500);


  delay(1000);
}