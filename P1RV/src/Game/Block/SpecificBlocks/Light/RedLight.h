#pragma once
#include "LightBlock.h"
class RedLight :
    public LightBlock
{
public:
    RedLight();
    RedLight(int i, int j, int k);
    RedLight(const Vector3I& p);
};

