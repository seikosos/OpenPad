#include "BleGamepadHandler.h"

void BleGamepadHandler::MainButtons() {
    bool sendReport = false;
    for (const auto& btn : Buttons) {
        debouncers->at(btn.label).update();

        if (debouncers->at(btn.label).fell()) {
            bleGamepad->press(btn.Button);
            sendReport = true;
        } else if (debouncers->at(btn.label).rose()) {
            bleGamepad->release(btn.Button);
            sendReport = true;
        }
    }
    if (sendReport) {
        bleGamepad->sendReport();
    }
};

bool HomeButton(Bounce state, BleGamepad *bleGamepad) {
    if (state.fell()) {
        bleGamepad->pressHome();
        return true;
    } else if (state.rose()) {
        bleGamepad->releaseHome();
        return true;
    }
    return false;
};

void BleGamepadHandler::SpecialButton() {
    bool sendReport = false;
    for (const auto& btn : SpecialButtons) {
        debouncers->at(btn.label).update();

        if (btn.label == "Home") {
            HomeButton(debouncers->at(btn.label), bleGamepad);
        }
    }
    if (sendReport) {
        bleGamepad->sendReport();
    }
};

void BleGamepadHandler::Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, std::map<String, Bounce> *debouncer) {
    config = configd;
    bleGamepad = bleGamepadd;
    debouncers = debouncer;

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