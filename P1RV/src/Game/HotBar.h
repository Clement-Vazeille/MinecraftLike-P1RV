#pragma once
#include "Block/Block.h"
#include "Block/SpecificBlocks/GrassBlock.h"
#include "Block/SpecificBlocks/GrassBlockSnow.h"
#include "Block/SpecificBlocks/CraftingTable.h"
#include "Block/SpecificBlocks/BirchWood.h"
#include "Block/SpecificBlocks/Stone.h"
#include "Block/SpecificBlocks/Dirt.h"
#include "Block/SpecificBlocks/Leaves.h"
#include "Block/SpecificBlocks/OakPlank.h"
#include "Block/SpecificBlocks/OakWood.h"
#include "Block/SpecificBlocks/Water.h"

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

