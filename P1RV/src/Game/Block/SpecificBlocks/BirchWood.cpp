#include "BirchWood.h"

BirchWood::BirchWood() : BirchWood(0,0,0)
{
}

BirchWood::BirchWood(int i, int j, int k) : Block(i,j,k)
{
	textures.at(0) = "Assets/Block/birch_log.png";  //arrière
	textures.at(1) = "Assets/Block/birch_log.png"; //devant
	textures.at(2) = "Assets/Block/birch_log.png"; //gauche
	textures.at(3) = "Assets/Block/birch_log.png";  //droit
	textures.at(4) = "Assets/Block/birch_log_top.png";   //bas
	textures.at(5) = "Assets/Block/birch_log_top.png";   //haut
}

BirchWood::BirchWood(const Vector3I& p) : BirchWood(p.getX(), p.getY(), p.getZ())
{
}
