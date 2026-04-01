#pragma once
#include "Handler.h"
#include <BleGamepad.h>

class WiiHandler : public Handler {
public:
    BleGamepadConfiguration* config;
    BleGamepad* bleGamepad;
    std::map<String, Bounce> *debouncers;

    void MainButtons() override;
    void SpecialButton() override;
    void Init();
};