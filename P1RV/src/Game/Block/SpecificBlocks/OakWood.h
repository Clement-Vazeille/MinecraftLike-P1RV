#pragma once
#include "../Block.h"
class OakWood :
    public Block
{
public:
    OakWood();
    OakWood(int i, int j, int k);
    OakWood(const Vector3I& p);
};

