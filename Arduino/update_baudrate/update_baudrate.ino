/* 
  Copyright 2020, Nikolas Lamb. 

  update_baudrate
    If you're using the DynamixelShield you'll probably need to update the 
    baudrate of one or more of your motors. Use this script to do that. 

    To use the script do the following:
    1) Update the value of:
            const uint8_t DXL_ID
      so that it matches the ID of the motor you want to change. Motors have 
      a default id of 1, so if you don't know what the id is then probably just
      leave it as 1. 
    2) Update the value of:
            cost uint32_t OLD_BAUDRATE
      to the current baudrate of the motor. For XL320 motors this is 1000000. 
      For XL430 motors this is 57600. 
    3) Update the value of:
            const uint32_t NEW_BAUDRATE
      to the desired new baudrate of the motor.
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

  const uint8_t DXL_ID = 1;
  const uint32_t OLD_BAUDRATE = 57600;
  const uint32_t NEW_BAUDRATE = 1000000; //1Mbsp
  
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(OLD_BAUDRATE);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  DEBUG_SERIAL.print("PROTOCOL ");
  DEBUG_SERIAL.print(DXL_PROTOCOL_VERSION, 1);
  DEBUG_SERIAL.print(", ID ");
  DEBUG_SERIAL.print(DXL_ID);
  DEBUG_SERIAL.print(": ");
  if(dxl.ping(DXL_ID) == true) {
    DEBUG_SERIAL.print("ping succeeded!");
    DEBUG_SERIAL.print(", Baudrate: ");
    DEBUG_SERIAL.println(OLD_BAUDRATE);
    
    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(DXL_ID);
    // Set a new baudrate(1Mbps) for DYNAMIXEL
    dxl.setBaudrate(DXL_ID, NEW_BAUDRATE);
    DEBUG_SERIAL.println("Baudrate has been successfully changed to 1Mbps");

    // Change to the new baudrate for communication.
    dxl.begin(NEW_BAUDRATE);

    dxl.ledOn(DXL_ID);
    delay(500);
    dxl.ledOff(DXL_ID);
    delay(500);
    dxl.ledOn(DXL_ID);
    delay(500);
    dxl.ledOff(DXL_ID);
  }
  else{
    DEBUG_SERIAL.println("ping failed!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
