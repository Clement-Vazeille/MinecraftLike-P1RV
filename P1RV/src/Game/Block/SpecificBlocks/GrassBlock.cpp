#include "GrassBlock.h"

GrassBlock::GrassBlock() : GrassBlock(0,0,0)
{
}

GrassBlock::GrassBlock(int i, int j, int k) : Block(i, j, k)
{
	textures.at(0) = "Assets/Block/grass_block_side.png";  //arrière
	textures.at(1) = "Assets/Block/grass_block_side.png"; //devant
	textures.at(2) = "Assets/Block/grass_block_side.png"; //gauche
	textures.at(3) = "Assets/Block/grass_block_side.png";  //droit
	textures.at(4) = "Assets/Block/dirt.png";   //bas
	textures.at(5) = "Assets/Block/grass_block_top.png";   //haut
}

GrassBlock::GrassBlock(const Vector3I& p) : GrassBlock(p.getX(), p.getY(), p.getZ())
{
}
