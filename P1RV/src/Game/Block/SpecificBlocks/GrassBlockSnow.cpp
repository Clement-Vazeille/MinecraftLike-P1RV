#include "GrassBlockSnow.h"

GrassBlockSnow::GrassBlockSnow() : GrassBlockSnow(0, 0, 0)
{
}

GrassBlockSnow::GrassBlockSnow(int i, int j, int k) : Block(i, j, k)
{
	textures.at(0) = "Assets/Block/grass_block_snow_side.png";  //arrière
	textures.at(1) = "Assets/Block/grass_block_snow_side.png"; //devant
	textures.at(2) = "Assets/Block/grass_block_snow_side.png"; //gauche
	textures.at(3) = "Assets/Block/grass_block_snow_side.png";  //droit
	textures.at(4) = "Assets/Block/dirt.png";   //bas
	textures.at(5) = "Assets/Block/grass_block_snow_top.png";   //haut
}

GrassBlockSnow::GrassBlockSnow(const Vector3I& p) : GrassBlockSnow(p.getX(), p.getY(), p.getZ())
{
}