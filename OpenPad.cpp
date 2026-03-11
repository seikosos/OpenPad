#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h> 
#include <BleGamepad.h>       
#include <Adafruit_MPU6050.h>   
#include "tusb.h" // when i was testing it wouldnt work without this so this is here, more like it kept complaining
// Adafruit_TinyUSB is for usb connections, BleGamepad for normal bluetooth gamepad, Adafruit_MPU6050 for the JoySticks and some general libs for other stuff

BleGamepad bleGamepad("OpenPad", "seikoso", 100);

BleGamepadConfiguration *config = new BleGamepadConfiguration();

struct ButtonConfig {
    int pin;
    char label;
	int Button;
};

const ButtonConfig Buttons[] = {
    {4, 'A', BUTTON_1},
    {5, 'B', BUTTON_2}
};

void setup() {
	Serial.begin(115200);
	Serial.println("hi i work");

	for (const ButtonConfig& btn : Buttons) {
        pinMode(btn.pin, INPUT_PULLUP);
    }

	config->setButtonCount(16);
	config->setControllerType(CONTROLLER_TYPE_GAMEPAD);
	config->setIncludeHome(true);
	config->setIncludeMenu(true);
	config->setIncludeStart(true);
	config->setIncludeSelect(true);
	config->setAutoReport(true);
	config->setIncludeGyroscope(true);

	bleGamepad.begin(config);
}

void loop() {
	if (bleGamepad.isConnected()) {
		for (const auto& btn : Buttons) {
			if (digitalRead(btn.pin) == LOW) {
				bleGamepad.press(btn.Button);
			} else {
				bleGamepad.release(btn.Button);
			}
		}
	}
	delay(5);
}