#include "PurpleLight.h"

PurpleLight::PurpleLight() : PurpleLight(0,0,0)
{
}

PurpleLight::PurpleLight(int i, int j, int k) : LightBlock(i,j,k)
{
	textures.at(0) = "Assets/Block/purple_light.png";  //arriere
	textures.at(1) = "Assets/Block/purple_light.png";  //devant
	textures.at(2) = "Assets/Block/purple_light.png";  //gauche
	textures.at(3) = "Assets/Block/purple_light.png";  //droit
	textures.at(4) = "Assets/Block/purple_light.png";  //bas
	textures.at(5) = "Assets/Block/purple_light.png";  //haut
}

PurpleLight::PurpleLight(const Vector3I& p) : PurpleLight(p.getX(), p.getY(), p.getZ())
{
}
