#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h> 
#include <BleGamepad.h>
#include <Bounce2.h>    
#include <Adafruit_MPU6050.h>
#include <map> 
#include "tusb.h" // when i was testing it wouldnt work without this so this is here, more like it kept complaining
#include <Adafruit_MCP23X17.h>
// Adafruit_TinyUSB is for usb connections, BleGamepad for normal bluetooth gamepad, Adafruit_MPU6050 for the JoySticks and some general libs for other stuff

#include "Handlers/BleGamepadHandler.h"

BleGamepad *bleGamepad = new BleGamepad("OpenPad", "seikoso", 100);
BleGamepadConfiguration *config = new BleGamepadConfiguration();
BleGamepadHandler Blehandler = BleGamepadHandler();

ButtonConfig* homeBtn = nullptr;

Adafruit_MCP23X17 mcp;

void setup() {
	Serial.begin(115200);
	Serial.println("hi i work");

	if (!mcp.begin_I2C(0x20)) {
		Serial.println("MCP23017 Error!");
	}

	for (ButtonConfig& btn : Buttons) {
		mcp.pinMode(btn.mcpPin, INPUT_PULLUP);
	}

	for (ButtonConfig& btn : SpecialButtons) {
		mcp.pinMode(btn.mcpPin, INPUT_PULLUP);

		if (btn.label == "Home") {
            homeBtn = &btn;
        }
	}

	uint16_t pinStates = mcp.readGPIOAB();
	bool isHomePressed = !((pinStates >> homeBtn->mcpPin) & 1);
	//also at some point i need to check if usb conenction supports using this controller as controlelr andthen use usb protocol for controller but thats later issue
	if (homeBtn->lastState != isHomePressed) {
		homeBtn->lastState = isHomePressed;
	} else {
    	Blehandler.Init(config, bleGamepad, &mcp);
	}
}

void loop() {
	if (bleGamepad->isConnected()) {
		Blehandler.MainButtons();
		Blehandler.SpecialButton();
	}
	delay(5);
}