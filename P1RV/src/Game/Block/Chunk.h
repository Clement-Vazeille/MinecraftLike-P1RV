#pragma once
#include <array>
#include "Block.h"
#include "../Maths/Vector2I.h"
#include "../Maths/Vector3I.h"
using namespace std;
class Chunk
{
protected:
	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur> blocks; //hashmap qui contient les diff�rents blocs du chunk
	Vector2I xyPosition;

	int sizeX;
	int sizeY;
	int sizeZ;
public:
	Chunk();
	Chunk(int xPosition, int yPosition);

	void AddBlock(Block* b);//ajoute un block dans un chunk � la position correspondante
	void FillBottomWithSnow(void);

	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* GetBlocks(void);
	//si le bloc existe d�j� il est replac� est d�truit

	Vector2I getPosition();
	int getSizeX();
	int getSizeY();
};

