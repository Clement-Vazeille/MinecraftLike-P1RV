#pragma once
#include "Shader/shader_s.h"
#include "MaFenetre.h"
//class qui a pour but d'envoyer aux shaders les informations de la scène sur les lumières
class LightManager
{
private: 
	void AddPointLight(glm::vec3& position,int id,const glm::vec3& color, Shader& shader);
public:
	LightManager();
	void Update(Shader& shader,float time, MaFenetre* fenetre);
};

