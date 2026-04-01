#include "BleGamepadHandler.h"

void BleGamepadHandler::MainButtons() {
    bool sendReport = false;
    for (ButtonConfig& btn : Buttons) {
        btn.debouncer.update();

        if (btn.debouncer.fell()) {
            bleGamepad->press(btn.Button);
            sendReport = true;
        } else if (btn.debouncer.rose()) {
            bleGamepad->release(btn.Button);
            sendReport = true;
        }
    }
    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::SpecialButton() {
    bool sendReport = false;
    for (ButtonConfig& btn : SpecialButtons) {
        btn.debouncer.update();

        if (btn.debouncer.changed()) {
            bool pressed = btn.debouncer.fell();

            if (btn.label == "Home") {
                pressed ? bleGamepad->pressHome() : bleGamepad->releaseHome();
                sendReport = true;
            } else if (btn.label == "Menu") {
                pressed ? bleGamepad->pressMenu() : bleGamepad->releaseMenu();
                sendReport = true;
            }
        }
    }

    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd) {
    config = configd;
    bleGamepad = bleGamepadd;

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