#pragma once
#include "Block/Block.h"
#include "Block/SpecificBlocks/GrassBlock.h"
#include "Block/SpecificBlocks/GrassBlockSnow.h"
#include "Block/SpecificBlocks/CraftingTable.h"
#include "Block/SpecificBlocks/BirchWood.h"

#include <array>
class HotBar
{
private:
	array<Block*, 10> blocks;
public:
	HotBar();
	~HotBar();
	void initialise(void);
	array<Block*, 10>* getBlocks(void);
};

