/* 
  Copyright (C) 2014 Kristian Lauszus, TKJ Electronics.
  Copyright (C) 2023 Lay31415

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 */

#include <PS4USB.h>
#include "HID-Project.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

// Function set button for boolean
////////////////////
void setButton(uint8_t key, bool state) {
  if (state) {
    Gamepad.press(key);
  } else {
    Gamepad.release(key);
  }
}
#define JOY_ANALOG_MIN -32768
#define JOY_ANALOG_MAX 32767

void setup() {
  Gamepad.begin();
  if (Usb.Init() == -1) {
    while (1); // Halt
  }
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    Gamepad.xAxis(0);
    Gamepad.yAxis(0);
    if(PS4.getButtonPress(UP)) Gamepad.yAxis(JOY_ANALOG_MIN);
    if(PS4.getButtonPress(DOWN)) Gamepad.yAxis(JOY_ANALOG_MAX);
    if(PS4.getButtonPress(LEFT)) Gamepad.xAxis(JOY_ANALOG_MIN);
    if(PS4.getButtonPress(RIGHT)) Gamepad.xAxis(JOY_ANALOG_MAX);
    setButton( 1, PS4.getButtonPress(CIRCLE));
    setButton( 2, PS4.getButtonPress(CROSS));
    setButton( 3, PS4.getButtonPress(TRIANGLE));
    setButton( 4, PS4.getButtonPress(SQUARE));
    setButton( 5, PS4.getButtonPress(L1));
    setButton( 6, PS4.getButtonPress(R1));
    setButton( 7, PS4.getButtonPress(L2));
    setButton( 8, PS4.getButtonPress(R2));
    setButton( 9, PS4.getButtonPress(SHARE));
    setButton(10, PS4.getButtonPress(OPTIONS));
    setButton(11, PS4.getButtonPress(TOUCHPAD));
    setButton(12, PS4.getButtonPress(L3));
    setButton(13, PS4.getButtonPress(R3));
    Gamepad.write();
  }
}
