# dynamixel-shield-toolbox
## Overview
This is a small library of arduino projects/functions and tools to help with development on the dynamixel shield for arduino. Though the team at ROBOTIS is working hard to bring the arduino library up to speed I personally found development on the shield to be very difficult for beginners. This is a small set of tools to help make starting new projects with the shield easier.

The shield is relatively new and as such the library is evolving constantly. Please see the [ROBOTIS eManual](https://emanual.robotis.com/docs/en/parts/interface/dynamixel_shield/) for up-to-date information and changelogs.

## Introduction
The dynamixel shield is, as far as I know, the most compact way to connect multiple dynamixel servos to an arduino. However it can also be pretty finicky; when I was setting it up I was constantly running into problems that weren't really addressed on the forum or in any of the documentation. To help beginners, I'll summarize my experience getting the shield and working. If you already have a working shield, then skip to [Setup](#setup).

If using an arduino board that performs serial communication [using pins 0 or 1](https://www.arduino.cc/reference/en/language/functions/communication/serial/) then attempting to communicate with dynamixel motors and also attempting to read from or write to serial will cause both streams to be corrupted. [ROBOTIS suggests](http://en.robotis.com/service/forum_view.php?bbs_no=2407675&page=1&save_sca=&sca=&save_stx=shield&stx=shield&sfl=wr_subject||wr_content) purchasing a [LN-101](https://emanual.robotis.com/docs/en/parts/interface/ln-101/) USB-to-Serial Adapter to circumvent this, which I what I'm using. In my experience, using and arduino UNO, this is the only way to get around this problem.

You'll also need to pick up the correct power supply for your motors. I picked up a variable power supply that can supply between 5 and 15 volts at 3 amps, and I'm powering both XL320 and XL430 motors using the 7.5v setting. See the datasheet for your motor to ensure you don't exceede the operating voltage.

Install the shield on the arduino, wire the power supply to the board, and then make sure to remove the jumper just below the power supply so that the board is running on external power before plugging it in. Finally, plug in the LN-101 and the arduino to the computer. 

To flash a new project to the arduino, make sure that the upload switch on the shield has been switched to 'upload', and the arduino IDE is connected to the `dev/ttyAMC*` port (corresponding to the arduino's USBconnection), not the `dev/ttyUSB*` port (corresponding to the shields USB connection). This is a little cumbersome; you can only flash to the arduino's port and only monitor the shield's port. If you try to flash to the shield's port you'll get an error. 

Make sure the libraries from [Setup](#setup) are installed. Flash the project, and then switch the upload switch on the shield from 'upload' to 'dynamixel'. At this point your script should run. 

## Setup
Essentially coppied from the [ROBOTIS eManual](https://emanual.robotis.com/docs/en/parts/interface/dynamixel_shield/).
1) Install Dynamixel Shield on Arduino.
2) Install Dynamixel Shield Library. \
Add the two required libraries: DYNAMIXEL2Arduino, and DYNAMIXELShield (Libraries can be added using Sketch -> Include Library -> Manage Libraries). Make sure to install DYNAMIXELShield version 1.0, not 0.5.

## Usage
### update_baudrate
If you're using the DynamixelShield you'll probably need to update the baudrate of one or more of your motors. Use this script to do that.

To use the script:
1) Update the value of `const uint8_t DXL_ID` so that it matches the ID of the motor you want to change. Motors have a default id of 1, so if you don't know what the id is then probably just leave it as 1. 
1) Update the value of `cost uint32_t OLD_BAUDRATE` to the current baudrate of the motor. For XL320 motors this is 1000000. For XL430 motors this is 57600. 
2) Update the value of `const uint32_t NEW_BAUDRATE` to the desired new baudrate of the motor.
3) Run the script. The motor should flash twice if the change was successful.

### update_id 
If you're using the DynamixelShield you'll probably need to update the id of one or more of your motors. Use this script to do that.

To use the script do the following:
1) Update the value of `const uint8_t OLD_ID` so that it matches the ID of the motor you want to change. Motors have a default id of 1, so if you don't know what the id is then probably just leave it as 1. 
1) Update the value of `cost uint8_t NEW_ID` to the desired new id of the motor. 
1) Update the value of `const uint32_t BAUDRATE` to the current baudrate of the motor. For XL320 motors this is 1000000. For XL430 motors this is 57600. 
1) Run the script. The motor should flash twice if the change was successful.

### scan_dynamixel_and_flash
Based on an arduino project by ROBOTIS to help find out if your servos are connected properly. Unfortunately, if you're using an UNO it doesn't work because the Dynamixels disrupt serial communication. 

This program circumvents this problem by flashing leds on dynamixels that are successfully found by the shield. Just a quick way to check if everything is properly connected.

### pyduino-lite
A link to one of my other repos that enables speedy serial communication with the arduino. I found that for some reason commands sent via the serial communicator on the shield are corrupted more often than commands sent via the traditional serial method. PyDuino implements double sided checksum to avoid this problem. 

pyduino-lite provides an example with 2 XL320 motors and 2 XL430 motors that provides methods to:
* control motors using velocity commands,
* control motors using position commands,
* read the position of any connected motor.