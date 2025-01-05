#pragma once
#include "../../Block.h"
class LightBlock :
    public Block
{
public:
    LightBlock(int i, int j, int k);

    bool isLight(void) const override;
};

