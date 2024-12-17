#pragma once
#include "../Block.h"
class Stone :
    public Block
{
public:
    Stone();
    Stone(int i, int j, int k);
    Stone(const Vector3I& p);
};

