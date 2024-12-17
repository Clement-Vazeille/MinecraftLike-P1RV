#include "Leaves.h"

Leaves::Leaves() : Leaves(0,0,0)
{
}

Leaves::Leaves(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/leaves.png";  //arriere
	textures.at(1) = "Assets/Block/leaves.png"; //devant
	textures.at(2) = "Assets/Block/leaves.png"; //gauche
	textures.at(3) = "Assets/Block/leaves.png";  //droit
	textures.at(4) = "Assets/Block/leaves.png";   //bas
	textures.at(5) = "Assets/Block/leaves.png";   //haut
}

Leaves::Leaves(const Vector3I& p) : Leaves(p.getX(), p.getY(), p.getZ())
{
}
