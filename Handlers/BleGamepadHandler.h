#pragma once
#include "Handler.h"
#include <BleGamepad.h>

class BleGamepadHandler : public Handler {
public:
    BleGamepadConfiguration* config;
    BleGamepad* bleGamepad;
    std::map<String, Bounce> *debouncers;

    void MainButtons() override;
    void SpecialButton() override;
    void Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, std::map<String, Bounce> *debouncer);
};