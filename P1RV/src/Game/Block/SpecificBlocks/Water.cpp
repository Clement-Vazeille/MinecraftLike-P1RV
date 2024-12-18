#include "Water.h"

Water::Water() : Water(0,0,0)
{
}

Water::Water(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/water.png";  //arriere
	textures.at(1) = "Assets/Block/water.png"; //devant
	textures.at(2) = "Assets/Block/water.png"; //gauche
	textures.at(3) = "Assets/Block/water.png";  //droit
	textures.at(4) = "Assets/Block/water.png";   //bas
	textures.at(5) = "Assets/Block/water.png";   //haut
}

Water::Water(const Vector3I& p) : Water(p.getX(),p.getY(),p.getZ())
{
}

bool Water::hasCollisions(void) const
{
	return false;
}
