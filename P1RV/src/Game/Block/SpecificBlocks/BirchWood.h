#pragma once
#include "../Block.h"
class BirchWood :
    public Block
{
public:
    BirchWood();
    BirchWood(int i, int j, int k);
    BirchWood(const Vector3I& p);
};

