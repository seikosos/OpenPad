#include "BleGamepadHandler.h"

void BleGamepadHandler::MainButtons() {
    uint16_t pinStates = mcp1->readGPIOAB();
    bool sendReport = false;

    for (ButtonConfig& btn : Buttons) {
        bool currentState = !((pinStates >> btn.mcpPin) & 1);

        if (currentState != btn.lastState) {
            currentState ? bleGamepad->press(btn.Button) : bleGamepad->release(btn.Button);
            btn.lastState = currentState;
            sendReport = true;
        }
    }
    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::SpecialButton() {
    uint16_t pinStates2 = mcp2->readGPIOAB();
    bool sendReport = false;

    for (ButtonConfig& btn : SpecialButtons) {
        bool currentState = !((pinStates2 >> btn.mcpPin) & 1);

        if (currentState != btn.lastState) {
            if (btn.label == "Home") {
                currentState ? bleGamepad->pressHome() : bleGamepad->releaseHome();
            } else if (btn.label == "Select") {
                currentState ? bleGamepad->pressSelect() : bleGamepad->releaseSelect();
            } else if (btn.label == "Start") {
                currentState ? bleGamepad->pressStart() : bleGamepad->releaseStart();
            } else if (btn.label == "Menu") {
                currentState ? bleGamepad->pressMenu() : bleGamepad->releaseMenu();
            } else if (btn.label == "LSC" || btn.label == "RSC") {
                currentState ? bleGamepad->press(btn.Button) : bleGamepad->release(btn.Button);
            } else {
                
            }
            btn.lastState = currentState;
            sendReport = true;
        }
    }

    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, Adafruit_MCP23X17* mcpp1, Adafruit_MCP23X17* mcpp2) {
    config = configd;
    bleGamepad = bleGamepadd;
    mcp1 = mcpp1;
    mcp2 = mcpp2;

    config->setButtonCount(8);
    config->setControllerType(CONTROLLER_TYPE_GAMEPAD);
    config->setIncludeHome(true);
    config->setIncludeMenu(true);
    config->setIncludeStart(true);
    config->setIncludeSelect(true);
    config->setAutoReport(false);
    config->setIncludeGyroscope(true);
    config->setHatSwitchCount(1);

    bleGamepad->begin(config);
};