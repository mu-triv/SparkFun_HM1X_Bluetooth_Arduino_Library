/*
  HM1X Bluetooth SoftwareSerial Configure Device
  Updated Support for HM1X devices 
  By: Niel Cansino
  Date: May 4, 2020
  License: This code is public domain but you buy me a beer 
  if you use this and we meet someday (Beerware license).

  Demonstrates how to configure the HM-19's BLE name,
  and how to reset the module. Also prints out BLE
  addresses (not configurable).

  Works well with a DSD-Tech HM-19 board -- 
  connecting via software serial (D3, D4)

  Hardware Connections:
  DSD-Tech HM-19 ------------------- Arduino Uno
       GND ----------------------------- GND
       3.3V ---------------------------- 5V
       TX ------------------------------ 3
       RX ------------------------------ 4
*/

// Use Library Manager or download here: https://github.com/sparkfun/SparkFun_HM1X_Bluetooth_Arduino_Library
#include <SparkFun_HM1X_Bluetooth_Arduino_Library.h>
#include <SoftwareSerial.h>

HM1X_BT bt(HM19);

SoftwareSerial btSerial(3, 4);

// BLE and EDR device names
String edrName = "MyEDR";
String bleName = "MyBLE";

void setup() {
  Serial.begin(9600); // Serial debug port @ 9600 bps

  // bt.begin --
  // in this case takes a HardwareSerial connection and
  // a desired serial baud rate.
  // Returns true on success
  if (bt.begin(btSerial, 9600) == false) {
    Serial.println(F("Failed to connect to the HM-13."));
    while (1) ;
  }
  boolean setName = false;
  Serial.println("Ready to Bluetooth!");

  boolean resetRequired = false; // Reset is required on name change
  // getEdrName returns a string containing EDR device name
  if (bt.getEdrName() != edrName) {
    Serial.println("Setting new EDR name");
    // Set EDR device name
    if (bt.setEdrName(edrName) == HM1X_SUCCESS) {
      Serial.println("Set EDR name");
      setName = true;
      resetRequired = true;
    }
  }
  // getEdrName returns a string containing BLE device name
  if (bt.getBleName() != bleName) {
    Serial.println("Setting new BLE name");
    // Set BLE device name
    if (bt.setBleName(bleName) == HM1X_SUCCESS) {
      Serial.println("Set BLE name to " + bleName);
      resetRequired = true;
    }
  } else {
    Serial.println("BLE name is: " + bleName);
  }
  
  Serial.println("EDR address: " + bt.edrAddress());
  Serial.println("BLE address: " + bt.bleAddress());

  if (resetRequired) {
    Serial.println("Resetting BT module. Wait a few seconds.");
    bt.reset();
  }
}

void loop() {
  if (bt.available()) {
    Serial.write((char) bt.read());
  }
  if (Serial.available()) {
    bt.write((char) Serial.read());
  } 
}
