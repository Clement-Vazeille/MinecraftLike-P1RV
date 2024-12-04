#include "ChunkManager.h"
#include <iostream>
#include <algorithm>

int ChunkManager::DistanceChunks(const Vector2I& coordonnesChunk1, const Vector2I& coordonnesChunk2)
{
	return abs(coordonnesChunk1.getX()-coordonnesChunk2.getX()) + abs(coordonnesChunk1.getZ() - coordonnesChunk2.getZ());
}

void ChunkManager::AddChunk(Chunk* chunk)
{
	if (!chunks.count(chunk->getPosition())) //test de non existence du chunk
	{
		chunks.insert(make_pair(chunk->getPosition(),chunk));
		activeChunks.insert(chunk);
	}
}

unordered_set<Chunk*>* ChunkManager::GetActiveChunks()
{
	return &activeChunks;
}

/*
unordered_map<Vector2I, Chunk*,Vector2I::HashFoncteur>* ChunkManager::GetActiveChunks()
{
	return &chunks;
}*/

void ChunkManager::LoadChunks(const glm::vec3& coordonneesJoueur)
{
	//on va tenter de charger tout les chunks à 3/4 chunks de distance
	Vector2I chunkjoueur(coordonneesJoueur);

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

void ChunkManager::UnloadChunks(const glm::vec3& coordonneesJoueur)
{
	Vector2I chunkjoueurPosition(coordonneesJoueur);
	int maxDistance = 2;

	auto it = activeChunks.begin();

	while (it != activeChunks.end()) {
		if (this->DistanceChunks(chunkjoueurPosition, (*it)->getPosition()) > maxDistance)
			it = activeChunks.erase(it);
		else
			++it;
	}
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
	else {  //Si le chunk est deja généré mais n'est pas chargé, on le charge
		if (!activeChunks.count(chunks.at(coordonneesChunk)))
			activeChunks.insert(chunks.at(coordonneesChunk));
	}
}

bool ChunkManager::isPositionAllowed(const glm::vec3& coordonneesJoueur)
{
	Vector2I chunkjoueur(coordonneesJoueur);

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
