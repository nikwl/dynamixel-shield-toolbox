/* 
  Copyright 2020, Nikolas Lamb. 

  update_id
    If you're using the DynamixelShield you'll probably need to update the 
    id of one or more of your motors. Use this script to do that. 

    To use the script do the following:
    1) Update the value of:
            const uint8_t OLD_ID
      so that it matches the ID of the motor you want to change. Motors have 
      a default id of 1, so if you don't know what the id is then probably just
      leave it as 1. 
    2) Update the value of:
            cost uint8_t NEW_ID
      to the desired new id of the motor. 
    3) Update the value of:
            const uint32_t BAUDRATE
      to the current baudrate of the motor. For XL320 motors this is 1000000. 
      For XL430 motors this is 57600. 
    4) Run the script. The motor should flash twice if the change was 
      successful.
*/
#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif

const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

void setup() {
  // put your setup code here, to run once:

  const uint8_t OLD_ID = 1;
  const uint8_t NEW_ID = 4;
  const int32_t BAUDRATE = 1000000;
  
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(BAUDRATE);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("PROTOCOL ");
  DEBUG_SERIAL.print(DXL_PROTOCOL_VERSION, 1);
  DEBUG_SERIAL.print(", ID ");
  DEBUG_SERIAL.print(OLD_ID);
  DEBUG_SERIAL.print(": ");
  if(dxl.ping(OLD_ID) == true) {
    DEBUG_SERIAL.print("ping succeeded!");
    DEBUG_SERIAL.print(", Model Number: ");
    DEBUG_SERIAL.println(dxl.getModelNumber(OLD_ID));
    
    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(OLD_ID);
    
    // set a new ID for DYNAMIXEL. Do not use ID 200
    dxl.setID(OLD_ID, NEW_ID);
    DEBUG_SERIAL.println("ID has been successfully changed to: " + (String)NEW_ID);

    dxl.ledOn(NEW_ID);
    delay(500);
    dxl.ledOff(NEW_ID);
    delay(500);
    dxl.ledOn(NEW_ID);
    delay(500);
    dxl.ledOff(NEW_ID);
  }
  else{
    DEBUG_SERIAL.println("ping failed!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
