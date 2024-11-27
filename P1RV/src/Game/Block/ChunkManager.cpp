#include "ChunkManager.h"

void ChunkManager::AddChunk(Chunk* chunk)
{
	chunks.insert(make_pair(chunk->getPosition(),chunk));
}

unordered_map<Vector2I, Chunk*,Vector2I::HashFoncteur>* ChunkManager::GetActiveChunks()
{
	return &chunks;
}

void ChunkManager::LoadChunks(const Vector3I& coordonneesJoueur)
{
	//on va tenter de charger tout les chunks à 3/4 chunks de distance
}

void ChunkManager::GenerateChunk(const Vector2I& coordonnesChunk)
{
}
