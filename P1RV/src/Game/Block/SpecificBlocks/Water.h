#pragma once
#include "../Block.h"
class Water :
    public Block
{
public:
    Water();
    Water(int i, int j, int k);
    Water(const Vector3I& p);
};

