#pragma once
#include "../Block.h"
class OakPlank :
    public Block
{
public:
    OakPlank();
    OakPlank(int i, int j, int k);
    OakPlank(const Vector3I& p);
};

