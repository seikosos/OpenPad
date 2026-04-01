#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h> 
#include <BleGamepad.h>
#include <Bounce2.h>    
#include <Adafruit_MPU6050.h>
#include <map> 
#include "tusb.h" // when i was testing it wouldnt work without this so this is here, more like it kept complaining
// Adafruit_TinyUSB is for usb connections, BleGamepad for normal bluetooth gamepad, Adafruit_MPU6050 for the JoySticks and some general libs for other stuff

#include "Handlers/BleGamepadHandler.h"

BleGamepad *bleGamepad = new BleGamepad("OpenPad", "seikoso", 100);
BleGamepadConfiguration *config = new BleGamepadConfiguration();
BleGamepadHandler Blehandler = BleGamepadHandler();

ButtonConfig* homeBtn = nullptr;

void setup() {
	Serial.begin(115200);
	Serial.println("hi i work");

	for (ButtonConfig& btn : Buttons) {
		if (btn.pin >= 34) {
			pinMode(btn.pin, INPUT);
		} else {
			pinMode(btn.pin, INPUT_PULLUP);
		}

		btn.debouncer.attach(btn.pin);
    	btn.debouncer.interval(5);
	}

	for (ButtonConfig& btn : SpecialButtons) {
		if (btn.pin >= 34) {
			pinMode(btn.pin, INPUT);
		} else {
			pinMode(btn.pin, INPUT_PULLUP);
		}

		btn.debouncer.attach(btn.pin);
    	btn.debouncer.interval(5);

		if (btn.label == "Home") {
            homeBtn = &btn;
        }
	}

	homeBtn->debouncer.update();
	//also at some point i need to check if usb conenction supports using this controller as controlelr andthen use usb protocol for controller but thats later issue
	if (homeBtn->debouncer.fell()) {
		// insert code later for other modes cuz to lazy rn
	} else {
    	Blehandler.Init(config, bleGamepad);
	}
}

void loop() {
	if (bleGamepad->isConnected()) {
		Blehandler.MainButtons();
		Blehandler.SpecialButton();
	}
	delay(5);
}