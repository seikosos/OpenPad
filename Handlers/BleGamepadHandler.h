#pragma once
#include "Handler.h"
#include <BleGamepad.h>

class BleGamepadHandler : public Handler {
public:
    BleGamepadConfiguration* config;
    BleGamepad* bleGamepad;
    Adafruit_MCP23X17* mcp;

    void MainButtons() override;
    void SpecialButton() override;
    void Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, Adafruit_MCP23X17* mcpp);
};