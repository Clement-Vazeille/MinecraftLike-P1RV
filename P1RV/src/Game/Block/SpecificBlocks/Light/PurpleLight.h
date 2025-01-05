#pragma once
#include "LightBlock.h"
class PurpleLight :
    public LightBlock
{
public:
    PurpleLight();
    PurpleLight(int i, int j, int k);
    PurpleLight(const Vector3I& p);
};

