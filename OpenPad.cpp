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

std::map<String, Bounce> *debouncers = new std::map<String, Bounce>;

BleGamepad *bleGamepad = new BleGamepad("OpenPad", "seikoso", 100);
BleGamepadConfiguration *config = new BleGamepadConfiguration();
BleGamepadHandler Blehandler = BleGamepadHandler();

void setup() {
	Serial.begin(115200);
	Serial.println("hi i work");

	for (const ButtonConfig& btn : Buttons) {
        pinMode(btn.pin, INPUT_PULLUP);

		debouncers->at(btn.label) = Bounce();
		debouncers->at(btn.label).attach(btn.pin);
        debouncers->at(btn.label).interval(5);
    }

	for (const ButtonConfig& btn : SpecialButtons) {
		pinMode(btn.pin, INPUT_PULLUP);

		debouncers->at(btn.label) = Bounce();
		debouncers->at(btn.label).attach(btn.pin);
        debouncers->at(btn.label).interval(5);
	}

	debouncers->at("Home").update();
	//also at some point i need to check if usb conenction supports using this controller as controlelr andthen use usb protocol for controller but thats later issue
	if (debouncers->at("Home").fell()) {
		// insert code later for other modes cuz to lazy rn
	} else {
    	Blehandler.Init(config, bleGamepad, debouncers);
	}
}

void loop() {
	if (bleGamepad->isConnected()) {
		Blehandler.MainButtons();
		Blehandler.SpecialButton();
	}
	delay(5);
}