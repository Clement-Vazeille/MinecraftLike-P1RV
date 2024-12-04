#pragma once
#include <unordered_map>
#include "../../IncludeLibrairies.h"

//Classe représentant des Vecteurs d'entiers à 2 dimensions
class Vector2I
{
private:
	int x;
	int z;
public:
	Vector2I();
	Vector2I(int x, int z);
	
	//conversion d'une coordonne 3d dans l'appli en une coordonnée de chunk
	Vector2I(const glm::vec3& coordonneesJoueur);

	void setX(int x);
	void setZ(int z);
	
	int getX(void) const;
	int getZ(void) const;

	void operator+= (const Vector2I& param);
	Vector2I operator+ (const Vector2I& param) const;
	Vector2I operator- (const Vector2I& param) const;
	Vector2I operator* (const int& param) const;
	bool operator== (const Vector2I& param) const;

	//Foncteur de hachage qu'on créer pour pouvoir faire des hashmaps de Vector2I
	struct HashFoncteur
	{
		size_t operator()(const Vector2I& param) const
		{
			size_t xHash = std::hash<int>()(param.getX());
			size_t yHash = std::hash<int>()(param.getZ()) << 1;
			return xHash ^ yHash;
		}
	};
};

