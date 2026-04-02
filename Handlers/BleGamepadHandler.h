#pragma once
#include "Handler.h"
#include <BleGamepad.h>
#include <Adafruit_MCP23X17.h>

class BleGamepadHandler : public Handler {
public:
    BleGamepadConfiguration* config;
    BleGamepad* bleGamepad;
    Adafruit_MCP23X17* mcp1;
    Adafruit_MCP23X17* mcp2;

    void MainButtons() override;
    void SpecialButton() override;
    void Init(BleGamepadConfiguration* configd, BleGamepad* bleGamepadd, Adafruit_MCP23X17* mcpp1, Adafruit_MCP23X17* mcpp2);
};