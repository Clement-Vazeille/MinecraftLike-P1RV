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
	Vector3I blockPosition = b->getPosition();

	//check if the bloc is in the chunk
	if (blockPosition.getX() < 0 || blockPosition.getX() >= sizeX ||
		blockPosition.getY() < 0 || blockPosition.getY() >= sizeY ||
		blockPosition.getZ() < 0 || blockPosition.getZ() >= sizeZ
		)
	{
		cout << "Le jeu a essayé d'ajouter un bloc à un chunk en dehors de ce chunk" << endl;
		return;
	}
	//delete blocks.at(blockPosition);
	blocks.insert(make_pair(blockPosition,b));
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
	CraftingTable* grass = new CraftingTable(8, 5, 8);
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
