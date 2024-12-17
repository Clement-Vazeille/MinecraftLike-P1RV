#include "Dirt.h"
#include <iostream>

Dirt::Dirt() : Dirt(0,0,0)
{
}

Dirt::Dirt(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/dirt.png";  //arriere
	textures.at(1) = "Assets/Block/dirt.png"; //devant
	textures.at(2) = "Assets/Block/dirt.png"; //gauche
	textures.at(3) = "Assets/Block/dirt.png";  //droit
	textures.at(4) = "Assets/Block/dirt.png";   //bas
	textures.at(5) = "Assets/Block/dirt.png";   //haut
}

Dirt::Dirt(const Vector3I& p) : Dirt(p.getX(), p.getY(), p.getZ())
{
}
