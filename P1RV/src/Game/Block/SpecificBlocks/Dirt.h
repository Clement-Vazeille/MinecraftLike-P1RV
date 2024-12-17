#pragma once
#include "../Block.h"
class Dirt :
    public Block
{
public:
    Dirt();
    Dirt(int i, int j, int k);
    Dirt(const Vector3I& p);
};

