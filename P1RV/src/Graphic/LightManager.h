#pragma once
#include "Shader/shader_s.h"
//class qui a pour but d'envoyer aux shaders les informations de la scène sur les lumières
class LightManager
{
public:
	LightManager();
	void Update(Shader& shader,float time);
};

