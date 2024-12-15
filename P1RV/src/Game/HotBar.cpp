#include "HotBar.h"

HotBar::HotBar() : 
	blocks{nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}
{
}

HotBar::~HotBar()
{
	for (Block* block : blocks)
	{
		if (block != nullptr)
			delete block;
	}
}

void HotBar::initialise(void)
{
	blocks.at(0) = new GrassBlock;
	blocks.at(1) = new GrassBlockSnow;
	blocks.at(2) = new CraftingTable;
	blocks.at(3) = new BirchWood;
}

array<Block*, 10>* HotBar::getBlocks(void)
{
	return &blocks;
}
