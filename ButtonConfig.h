#pragma once
#include <BleGamepad.h>

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
    {0, "UP", DPAD_UP},
    {1, "DOWN", DPAD_DOWN},
    {2, "LEFT", DPAD_LEFT},
    {3, "RIGHT", DPAD_RIGHT},
    {4, "LSC", BUTTON_9},
    {5, "RSC", BUTTON_10},
    {6, "Home", 0, false},
    {7, "Select", 0},
    {8, "Start", 0},
    {9, "Menu", 0},
};