#include "ChunkManager.h"
#include <iostream>

void ChunkManager::AddChunk(Chunk* chunk)
{
	if(!chunks.count(chunk->getPosition())) //test de non existence du chunk
		chunks.insert(make_pair(chunk->getPosition(),chunk));
}

unordered_map<Vector2I, Chunk*,Vector2I::HashFoncteur>* ChunkManager::GetActiveChunks()
{
	return &chunks;
}

void ChunkManager::LoadChunks(const glm::vec3& coordonneesJoueur)
{
	//on va tenter de charger tout les chunks à 3/4 chunks de distance
	Vector2I chunkjoueur(coordonneesJoueur.x / 16, coordonneesJoueur.z / 16);
	if (coordonneesJoueur.x < 0)
		chunkjoueur += Vector2I(-1, 0);
	if (coordonneesJoueur.z < 0)
		chunkjoueur += Vector2I(0, -1);

	//chunkjoueur += Vector2I(0,0);

	this->GenerateChunk(chunkjoueur);
	//cout << "chunk   " << chunkjoueur.getX() << "; " << chunkjoueur.getZ() << endl;
	//cout << "joueur   " << coordonneesJoueur.x << ";" << coordonneesJoueur.z << endl;

	this->GenerateChunk(chunkjoueur + Vector2I(1, 1));
	this->GenerateChunk(chunkjoueur + Vector2I(0, 1));
	this->GenerateChunk(chunkjoueur + Vector2I(-1, 1));
	this->GenerateChunk(chunkjoueur + Vector2I(1, 0));
	this->GenerateChunk(chunkjoueur + Vector2I(-1, 0));
	this->GenerateChunk(chunkjoueur + Vector2I(1, -1));
	this->GenerateChunk(chunkjoueur + Vector2I(0, -1));
	this->GenerateChunk(chunkjoueur + Vector2I(-1, -1));
}

void ChunkManager::GenerateChunk(const Vector2I& coordonneesChunk)
{
	if (!chunks.count(coordonneesChunk)) //test de non existence du chunk 
	{
		Chunk* chunk = new Chunk(coordonneesChunk);
		if ((coordonneesChunk.getX() + coordonneesChunk.getZ()) % 2 == 0)
			chunk->FillBottomWithSnow();
		else
			chunk->FillBottomWithGrass();
		this->AddChunk(chunk);
	}
}
