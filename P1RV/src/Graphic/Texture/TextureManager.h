#pragma once
#include "../../IncludeLibrairies.h"
#include "../Shader/shader_s.h"
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

//Classe permettant de charger et utiliser des textures
class TextureManager
{
protected:
	void LoadTexture(string fileName, Shader shader);
	unordered_map<string, int> texIDMap;
public:
	//charge l'entièretEdes textures et donne leur id aux shaders
	void Load(Shader shader);
	
	//Prend en entrée le chemin vers une texture (elle doit déjEêtre chargée) et la place comme texture utilisée pour les prochains rendus
	void BindTexture(string fileName) const;
};

