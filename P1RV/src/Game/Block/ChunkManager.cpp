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

bool ChunkManager::isPositionAllowed(const glm::vec3& coordonneesJoueur)
{
	Vector2I chunkjoueur(coordonneesJoueur.x / 16, coordonneesJoueur.z / 16);
	if (coordonneesJoueur.x < 0)
		chunkjoueur += Vector2I(-1, 0);
	if (coordonneesJoueur.z < 0)
		chunkjoueur += Vector2I(0, -1);

	Vector3I blockjoueur(static_cast<int>(coordonneesJoueur.x) % 16, static_cast<int>(coordonneesJoueur.y), static_cast<int>(coordonneesJoueur.z) % 16);

	if (chunks.count(chunkjoueur))
	{
		//cout << blockjoueur.getX() <<" " << blockjoueur.getY() << " " << blockjoueur.getZ() << " Test :" << chunks[chunkjoueur]->GetBlocks()->count(blockjoueur) << endl;

		//marche pas du tout pour les coordonnées négatives
		if (chunks[chunkjoueur]->GetBlocks()->count(blockjoueur))
			return false;
	}
	return true;
}
