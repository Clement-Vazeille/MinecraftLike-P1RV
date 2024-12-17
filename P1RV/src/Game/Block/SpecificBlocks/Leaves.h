#pragma once
#include "../Block.h"
class Leaves :
    public Block
{
public:
    Leaves();
    Leaves(int i, int j, int k);
    Leaves(const Vector3I& p);
};

