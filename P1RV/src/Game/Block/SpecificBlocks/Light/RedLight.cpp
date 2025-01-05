#include "RedLight.h"

RedLight::RedLight() : RedLight(0,0,0)
{
}

RedLight::RedLight(int i, int j, int k) : LightBlock(i,j,k)
{
	color = glm::vec3(200.f / 255.f, 0.f / 255.f, 0.f / 255.f);
	textures.at(0) = "Assets/Block/red_light.png";  //arriere
	textures.at(1) = "Assets/Block/red_light.png";  //devant
	textures.at(2) = "Assets/Block/red_light.png";  //gauche
	textures.at(3) = "Assets/Block/red_light.png";  //droit
	textures.at(4) = "Assets/Block/red_light.png";  //bas
	textures.at(5) = "Assets/Block/red_light.png";  //haut
}

RedLight::RedLight(const Vector3I& p) : RedLight(p.getX(), p.getY(), p.getZ())
{
}
