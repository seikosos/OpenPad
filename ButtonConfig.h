#pragma once
#include <BleGamepad.h>
#include <Bounce2.h>

struct ButtonConfig {
    uint8_t mcpPin;
    String label;
	int Button;
    bool lastState = true;
};

inline ButtonConfig Buttons[] = {
    {0, "A", BUTTON_1},
    {1, "B", BUTTON_2},
    {2, "X", BUTTON_3},
    {3, "Y", BUTTON_4},
    {4, "L", BUTTON_5},
    {5, "R", BUTTON_6},
    {6, "ZL", BUTTON_7},
    {7, "ZR", BUTTON_8}
};

inline ButtonConfig SpecialButtons[] = {
    {8, "UP", DPAD_UP},
    {9, "DOWN", DPAD_DOWN},
    {10, "LEFT", DPAD_LEFT},
    {11, "RIGHT", DPAD_RIGHT},
    {12, "LSC", BUTTON_9},
    {13, "RSC", BUTTON_10},
    {14, "Home", 0},
    {15, "Select", 0}
};