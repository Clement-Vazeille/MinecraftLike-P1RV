#include "Stone.h"

Stone::Stone() : Stone(0,0,0)
{
}

Stone::Stone(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/stone.png";  //arriere
	textures.at(1) = "Assets/Block/stone.png"; //devant
	textures.at(2) = "Assets/Block/stone.png"; //gauche
	textures.at(3) = "Assets/Block/stone.png";  //droit
	textures.at(4) = "Assets/Block/stone.png";   //bas
	textures.at(5) = "Assets/Block/stone.png";   //haut
}

Stone::Stone(const Vector3I& p) : Stone(p.getX(), p.getY(), p.getZ())
{
}
