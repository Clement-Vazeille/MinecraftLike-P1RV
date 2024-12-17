#include "OakWood.h"

OakWood::OakWood() : OakWood(0,0,0)
{
}

OakWood::OakWood(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/oak_Side.png";  //arriere
	textures.at(1) = "Assets/Block/oak_Side.png"; //devant
	textures.at(2) = "Assets/Block/oak_Side.png"; //gauche
	textures.at(3) = "Assets/Block/oak_Side.png";  //droit
	textures.at(4) = "Assets/Block/oak_Top.png";   //bas
	textures.at(5) = "Assets/Block/oak_Top.png";   //haut
}

OakWood::OakWood(const Vector3I& p) : OakWood(p.getX(), p.getY(), p.getZ())
{
}
