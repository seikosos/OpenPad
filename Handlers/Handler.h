#pragma once
#include <map>
#include <Bounce2.h>
#include "ButtonConfig.h"

struct Handler {
    virtual void MainButtons() = 0;
    virtual void SpecialButton() = 0;
    virtual ~Handler() = default;
};