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
	
	void LoadChunks(const Vector3I& coordonneesJoueur);
	void GenerateChunk(const Vector2I& coordonnesChunk);
};
