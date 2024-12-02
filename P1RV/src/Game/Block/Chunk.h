#pragma once
#include <array>
#include "Block.h"
#include "../Maths/Vector2I.h"
#include "../Maths/Vector3I.h"
using namespace std;

//Classe repr�sentant un chunk, un chunk est un esemble de blocs d�limit� dans l'espace, c'est du 16*64*16
class Chunk
{
protected:
	//On stock les blocks dans une unordered map car �a nous garantit un acc�s et un ajout rapide des blocks et que si on aurait pris un tableau on aurait bcp d'espace occup� non utilis� 
	//car la majorit� des blocks d'un chunk sont vides
	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur> blocks; 
	Vector2I xzPosition;

	int sizeX;
	int sizeY;
	int sizeZ;
public:
	Chunk();
	Chunk(int xPosition, int zPosition);
	Chunk(const Vector2I& v);

	void AddBlock(Block* b);//ajoute un block dans un chunk � la position correspondante
	void FillBottomWithSnow(void);
	void FillBottomWithGrass(void);


	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* GetBlocks(void);
	//si le bloc existe d�j� il est replac� est d�truit

	Vector2I getPosition();
	int getSizeX();
	int getSizeY();
	int getSizeZ();
};

