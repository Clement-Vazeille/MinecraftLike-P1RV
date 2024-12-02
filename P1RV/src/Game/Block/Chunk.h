#pragma once
#include <array>
#include "Block.h"
#include "../Maths/Vector2I.h"
#include "../Maths/Vector3I.h"
using namespace std;

//Classe représentant un chunk, un chunk est un esemble de blocs délimité dans l'espace, c'est du 16*64*16
class Chunk
{
protected:
	//On stock les blocks dans une unordered map car ça nous garantit un accès et un ajout rapide des blocks et que si on aurait pris un tableau on aurait bcp d'espace occupé non utilisé 
	//car la majorité des blocks d'un chunk sont vides
	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur> blocks; 
	Vector2I xzPosition;

	int sizeX;
	int sizeY;
	int sizeZ;
public:
	Chunk();
	Chunk(int xPosition, int zPosition);
	Chunk(const Vector2I& v);

	void AddBlock(Block* b);//ajoute un block dans un chunk à la position correspondante
	void FillBottomWithSnow(void);
	void FillBottomWithGrass(void);


	unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* GetBlocks(void);
	//si le bloc existe déjà il est replacé est détruit

	Vector2I getPosition();
	int getSizeX();
	int getSizeY();
	int getSizeZ();
};

