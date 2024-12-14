#include "Chunk.h"
#include <iostream>
#include "SpecificBlocks/GrassBlockSnow.h"
#include "SpecificBlocks/GrassBlock.h"

#include "SpecificBlocks/CraftingTable.h"

Chunk::Chunk() : Chunk(0,0)
{
	
}

Chunk::Chunk(int xPosition, int zPosition) : 
	xzPosition(xPosition,zPosition),
	sizeX(16),sizeY(64),sizeZ(16)
{
}

Chunk::Chunk(const Vector2I& v) : Chunk(v.getX(),v.getZ())
{
}

void Chunk::AddBlock(Block* b)
{
	if (b != nullptr)
	{
		Vector3I blockPosition = b->getPosition();

		//check if the bloc is in the chunk
		if (blockPosition.getX() < 0 || blockPosition.getX() >= sizeX ||
			blockPosition.getY() < 0 || blockPosition.getY() >= sizeY ||
			blockPosition.getZ() < 0 || blockPosition.getZ() >= sizeZ
			)
		{
			cout << "Le jeu a essaye d'ajouter un bloc a un chunk en dehors de ce chunk" << endl;
			return;
		}
		blocks.insert(make_pair(blockPosition, b));
	}
}

void Chunk::DestroyBlock(const Vector3I& coordBlock)
{
	//test d'existence du block
	if (blocks.count(coordBlock))
	{
		if (blocks.at(coordBlock)!=nullptr)
			delete blocks.at(coordBlock);
		blocks.erase(coordBlock);
	}
}

void Chunk::FillBottomWithSnow(void)
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int z = 0; z < sizeZ; z++)
		{
			GrassBlockSnow* snow = new GrassBlockSnow(x, 0, z);
			this->AddBlock(snow);
		}
	}
}

void Chunk::FillBottomWithGrass(void)
{
	for (int x = 0; x < sizeX; x++)
	{
		for (int z = 0; z < sizeZ; z++)
		{
			GrassBlock* grass = new GrassBlock(x, 0, z);
			this->AddBlock(grass);
		}
	}
	CraftingTable* grass = new CraftingTable(8, 1, 8);
	this->AddBlock(grass);
}

unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* Chunk::GetBlocks(void)
{
	return &blocks;
}

Vector2I Chunk::getPosition()
{
	return xzPosition;
}

int Chunk::getSizeX()
{
	return sizeX;
}

int Chunk::getSizeY()
{
	return sizeY;
}

int Chunk::getSizeZ()
{
	return sizeZ;
}
