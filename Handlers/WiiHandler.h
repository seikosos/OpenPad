#pragma once
#include "Handler.h"

class WiiHandler : public Handler {
public:
    void MainButtons() override;
    void SpecialButton() override;
    void Init();
};