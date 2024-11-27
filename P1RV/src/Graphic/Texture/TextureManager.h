#pragma once
#include "../../Include.h"
#include "../Shader/shader_s.h"
#include <utility>
#include <string>
#include <unordered_map>

using namespace std;

class TextureManager
{
protected:
	void LoadTexture(string fileName, Shader shader);
	unordered_map<string, int> texIDMap;
public:
	void Load(Shader shader);
	
	void BindTexture(string fileName) const;
};

