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
	void LoadTexture(string fileName, Shader& shader);
	unordered_map<string, int> texIDMap;
public:
	//charge l'entierete des textures et donne leur id aux shaders
	void Load(Shader shader);
	
	//Prend en entree le chemin vers une texture (elle doit deja etre chargee) et la place comme texture utilisee pour les prochains rendus
	void BindTexture(string fileName) const;
};

