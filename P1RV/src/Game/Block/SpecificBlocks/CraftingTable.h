#pragma once
#include "../Block.h"

class CraftingTable :
    public Block
{
public:
    CraftingTable();
    CraftingTable(int i, int j, int k);
    CraftingTable(const Vector3I& p);
};

