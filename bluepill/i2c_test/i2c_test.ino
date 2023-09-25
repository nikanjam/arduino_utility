// Project: I2C test on bluepill board
// at this project just scan i2c bus for find devices.

// Default pin i2c for bluepill:
// Wire1 -> (SCL, SDA):(PB6, PB7)
// Wire2 -> (SCL, SDA):(PB10, PB11)



#include <Wire.h>

// For use IIC2 define this:
//  TwoWire WIRE2 (2,I2C_FAST_MODE);
//  #define Wire WIRE2


void setup() {

  Serial.begin(115200);
  Wire.begin();
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) 
        Serial.print("0");
      Serial.println(address, HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}