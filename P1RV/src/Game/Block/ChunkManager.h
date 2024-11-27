#pragma once
#include "Chunk.h"
#include <unordered_map>
#include "../Maths/Vector2I.h"
class ChunkManager
{
private:
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur> chunks;
public:
	void AddChunk(Chunk* chunk);
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	
	void LoadChunks(const glm::vec3& coordonneesJoueur); //fonction qui va charger les chunks � proximit� du joueur

	void GenerateChunk(const Vector2I& coordonnesChunk); //fonction qui prend en entr�e une coordonn�e dans le rep�re chunk et qui va placer un chunk � cet emplacement si il n'y en a pas d�j� un
};
