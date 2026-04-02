#pragma once
#include <map>
#include "ButtonConfig.h"

struct Handler {
    virtual void MainButtons() = 0;
    virtual void SpecialButton() = 0;
    virtual ~Handler() = default;
};