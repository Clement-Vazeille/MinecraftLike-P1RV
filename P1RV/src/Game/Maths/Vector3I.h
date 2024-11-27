#pragma once
#include <unordered_map>

class Vector3I
{
private:
	int x;
	int y;
	int z;
public:
	Vector3I();
	Vector3I(int x, int y,int z);

	void setX(int x);
	void setY(int y);
	void setZ(int z);

	int getX(void) const;
	int getY(void) const;
	int getZ(void) const;


	void operator+= (const Vector3I& param);
	Vector3I operator+ (const Vector3I& param) const;
	Vector3I operator- (const Vector3I& param) const;
	Vector3I operator* (const int& param) const;
	bool operator== (const Vector3I& param) const;

	//Foncteur de hachage qu'on créer pour pouvoir faire des hashmaps de Vector2I
	struct HashFoncteur
	{
		size_t operator()(const Vector3I& param) const //TODO faire des recherches/tests pour voir si on peut faire une fonction de hashage avec moins de collisions
		{
			size_t xHash = std::hash<int>()(param.getX());
			size_t yHash = (std::hash<int>()(param.getY()) << 1)>>1;
			size_t zHash = std::hash<int>()(param.getZ()) << 1;
			return xHash ^ yHash ^ zHash; //on fait un XOR binaire des différents hash pour les combiner en un seul hash
		}
	};
};

