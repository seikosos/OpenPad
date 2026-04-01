#pragma once
#include <BleGamepad.h>
#include <Bounce2.h>

struct ButtonConfig {
    int pin;
    String label;
	int Button;
    Bounce debouncer;
};

inline ButtonConfig Buttons[] = {
    {4, "A", BUTTON_1},
    {5, "B", BUTTON_2},
	{6, "X", BUTTON_3},
    {7, "Y", BUTTON_4},
	{15, "L", BUTTON_5},
    {16, "R", BUTTON_6},
	{17, "ZL", BUTTON_7},
    {18, "ZR", BUTTON_8},
};

inline ButtonConfig SpecialButtons[] = {
    {8, "LSC"},
    {3, "RSC"},
	{38, "Home"},
    {37, "Select"}
};