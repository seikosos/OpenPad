#include "BleGamepadHandler.h"
#include <Adafruit_MCP23X17.h>

void BleGamepadHandler::MainButtons() {
    uint16_t pinStates = mcp->readGPIOAB();
    bool sendReport = false;

    for (ButtonConfig& btn : Buttons) {
        bool currentState = !((pinStates >> btn.mcpPin) & 1);

        if (currentState != btn.lastState) {
            if (currentState) {
                bleGamepad->press(btn.Button);
            } else {
                bleGamepad->release(btn.Button);
            }
            btn.lastState = currentState;
            sendReport = true;
        }
    }
    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::SpecialButton() {
    uint16_t pinStates = mcp->readGPIOAB();
    bool sendReport = false;

    for (ButtonConfig& btn : SpecialButtons) {
        bool currentState = !((pinStates >> btn.mcpPin) & 1);

        if (currentState != btn.lastState) {

            if (btn.label == "Home") {
                currentState ? bleGamepad->pressHome() : bleGamepad->releaseHome();
                sendReport = true;
            } else if (btn.label == "Menu") {
                currentState ? bleGamepad->pressMenu() : bleGamepad->releaseMenu();
                sendReport = true;
            }
            btn.lastState = currentState;
            sendReport = true;
        }
    }

    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, Adafruit_MCP23X17* mcpp) {
    config = configd;
    bleGamepad = bleGamepadd;
    mcp = mcpp;

    config->setButtonCount(10);
    config->setControllerType(CONTROLLER_TYPE_GAMEPAD);
    config->setIncludeHome(true);
    config->setIncludeMenu(true);
    config->setIncludeStart(true);
    config->setIncludeSelect(true);
    config->setAutoReport(false);
    config->setIncludeGyroscope(true);

    bleGamepad->begin(config);
};