#pragma once
#include <array>
#include "Block.h"
#include "../Maths/Vector2I.h"
#include "../Maths/Vector3I.h"
using namespace std;
class Chunk
{
protected:
	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur> blocks; //hashmap qui contient les différents blocs du chunk
	Vector2I xyPosition;

	int sizeX;
	int sizeY;
	int sizeZ;
public:
	Chunk();
	Chunk(int xPosition, int yPosition);

	void AddBlock(Block* b);//ajoute un block dans un chunk à la position correspondante
	void FillBottomWithSnow(void);

	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* GetBlocks(void);
	//si le bloc existe déjà il est replacé est détruit

	Vector2I getPosition();
	int getSizeX();
	int getSizeY();
};

