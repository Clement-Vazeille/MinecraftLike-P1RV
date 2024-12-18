#include "Block.h"
#include <iostream>
Block::Block() : Block(0,0,0)
{
}

Block::Block(int i, int j, int k) : position (i,j,k), 
	textures({ 
	"Assets/Block/birch_log.png", //arrière
	"Assets/Block/birch_log.png", //devant
	"Assets/Block/birch_log.png", //gauche
	"Assets/Block/birch_log.png", //droit
	"Assets/Block/birch_log.png", //haut
	"Assets/Block/birch_log.png"  //bas
		})
{
}

Block::Block(const Vector3I& p) : Block(p.getX(),p.getY(),p.getZ())
{
}

Vector3I Block::getPosition(void)
{
	return position;
}

string Block::getTexturei(int i)
{
	return textures[i];
}

bool Block::hasCollisions(void) const
{
	return true;
}


