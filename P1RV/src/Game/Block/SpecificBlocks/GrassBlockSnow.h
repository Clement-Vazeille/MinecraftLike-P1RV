#pragma once
#include "../Block.h"
class GrassBlockSnow :
    public Block
{
public:
    GrassBlockSnow();
    GrassBlockSnow(int i, int j, int k);
    GrassBlockSnow(const Vector3I& p);
};

