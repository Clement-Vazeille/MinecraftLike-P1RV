#include "Chunk.h"
#include <iostream>
#include "SpecificBlocks/GrassBlockSnow.h"

Chunk::Chunk() : Chunk(0,0)
{
	
}

Chunk::Chunk(int xPosition, int yPosition) : 
	xyPosition(xPosition,yPosition),
	sizeX(16),sizeY(16),sizeZ(64)
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
		for (int y = 0; y < sizeY; y++)
		{
			GrassBlockSnow* snow = new GrassBlockSnow(x, 0, y);
			this->AddBlock(snow);
		}
	}
}

unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* Chunk::GetBlocks(void)
{
	return &blocks;
}

Vector2I Chunk::getPosition()
{
	return xyPosition;
}

int Chunk::getSizeX()
{
	return sizeX;
}

int Chunk::getSizeY()
{
	return sizeY;
}
