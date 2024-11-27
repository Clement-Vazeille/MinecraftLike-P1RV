#pragma once
#include "../Block.h"
class GrassBlock :
    public Block
{
public:
    GrassBlock();
    GrassBlock(int i, int j, int k);
    GrassBlock(const Vector3I& p);
};

