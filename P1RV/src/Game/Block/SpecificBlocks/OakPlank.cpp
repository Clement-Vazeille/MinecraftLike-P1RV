#include "OakPlank.h"

OakPlank::OakPlank() : OakPlank(0,0,0)
{
}

OakPlank::OakPlank(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/oak_Plank.png";  //arriere
	textures.at(1) = "Assets/Block/oak_Plank.png"; //devant
	textures.at(2) = "Assets/Block/oak_Plank.png"; //gauche
	textures.at(3) = "Assets/Block/oak_Plank.png";  //droit
	textures.at(4) = "Assets/Block/oak_Plank.png";   //bas
	textures.at(5) = "Assets/Block/oak_Plank.png";   //haut
}

OakPlank::OakPlank(const Vector3I& p) : OakPlank(p.getX(), p.getY(), p.getZ())
{
}
