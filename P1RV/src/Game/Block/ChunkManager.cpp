#include "ChunkManager.h"
#include <iostream>
#include <algorithm>
#include "SpecificBlocks/GrassBlock.h"

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

void ChunkManager::AddBlock(const Vector2I& coordChunk, const Vector3I& coordBlock)
{
	if (chunks.count(coordChunk)) //test d' existence du chunk
	{
		GrassBlock* grassBlock = new GrassBlock(coordBlock);
		chunks.at(coordChunk)->AddBlock(grassBlock);
	}
}

void ChunkManager::DestroyBlock(const Vector2I& coordChunk, const Vector3I& coordBlock)
{
	if (chunks.count(coordChunk)) //test d' existence du chunk
	{
		chunks.at(coordChunk)->DestroyBlock(coordBlock);
	}
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

	int distanceChargement = renderDistance;
	
	//On se déplace sur l'ensemble des blocs qui sont au plus à une distance "distanceChargement" du joueur
	for(int i = -distanceChargement;i<=distanceChargement;i++)
	{
		for (int j = -distanceChargement + abs(i); j <= distanceChargement - abs(i); j++)
		{
			this->GenerateChunk(chunkjoueur + Vector2I(i, j));
		}
	}
}

void ChunkManager::UnloadChunks(const glm::vec3& coordonneesJoueur)
{
	Vector2I chunkjoueurPosition(coordonneesJoueur);
	int maxDistance = renderDistance;

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
	//Paramétrage de la taille du joueur ainsi que de la hauteur de ses yeux
	float joueurTailleX = 0.8f;
	float joueurTailleY = 2.5f;
	float joueurTailleZ = 0.8f;
	float ratioHauteurYeux = 0.95f;
	glm::vec3 playerMins(coordonneesJoueur.x - (joueurTailleX/2.f), coordonneesJoueur.y - (joueurTailleX * ratioHauteurYeux), coordonneesJoueur.z - (joueurTailleZ / 2.f));
	glm::vec3 playerMaxs(coordonneesJoueur.x + (joueurTailleX / 2.f), coordonneesJoueur.y + (joueurTailleX * (1-ratioHauteurYeux)), coordonneesJoueur.z + (joueurTailleZ / 2.f));

	//boucle for qui va parcourir les blocs proches du joueur (en 3*4*3 pour le moment) puis qui va check si il y a collision entre le joueur et chacun des blocs en mode aabb
	for (int deltaX = -1; deltaX <= 1; deltaX++)
	{
		for (int deltaY = -2; deltaY <= 1; deltaY++)
		{
			for (int deltaZ = -1; deltaZ <= 1; deltaZ++)
			{
				Vector2I cooChunkActuel;
				Vector3I cooBlockActuel;
				if (findBlock(coordonneesJoueur + glm::vec3(deltaX, deltaY, deltaZ), &cooChunkActuel, &cooBlockActuel, nullptr))
				{
					glm::vec3 blockMins(cooBlockActuel.getX()+cooChunkActuel.getX()*16, cooBlockActuel.getY(), cooBlockActuel.getZ() + (cooChunkActuel.getZ() * 16));
					glm::vec3 blockMaxs(blockMins.x+1,blockMins.y+1,blockMins.z+1);

					if(collisionAABB(playerMins,playerMaxs,blockMins,blockMaxs))
						return false;
				}
			}
		}
	}
	return true;
	
}

bool ChunkManager::collisionAABB(const glm::vec3& aMins, const glm::vec3& aMaxs, const glm::vec3& bMins, const glm::vec3& bMaxs)
{
	return (
		aMins.x <= bMaxs.x &&
		aMaxs.x >= bMins.x &&
		aMins.y <= bMaxs.y &&
		aMaxs.y >= bMins.y &&
		aMins.z <= bMaxs.z &&
		aMaxs.z >= bMins.z
		);
}

bool ChunkManager::findBlock(const glm::vec3& coordonnees, Vector2I* sortieCoordChunk, Vector3I* sortieCoordBloc, Block** block)
{
	Vector2I chunktrouve(coordonnees);

	Vector3I blocktrouve(static_cast<int>(coordonnees.x) % 16, static_cast<int>(coordonnees.y), static_cast<int>(coordonnees.z) % 16);
	if (coordonnees.x < 0)
		blocktrouve.setX(blocktrouve.getX() + 15);
	if (coordonnees.z < 0)
		blocktrouve.setZ(blocktrouve.getZ() + 15);

	if (chunks.count(chunktrouve)) //Test de si il y a un chunk ou non à l'emplacement
	{
		if (chunks[chunktrouve]->GetBlocks()->count(blocktrouve)) //Test de si il y a un bloc ou non à l'emplacement
		{
			if(sortieCoordChunk!=nullptr)
				*sortieCoordChunk = chunktrouve;
			if(sortieCoordBloc!=nullptr)
				*sortieCoordBloc = blocktrouve;
			if (block != nullptr)
				*block = chunks[chunktrouve]->GetBlocks()->at(blocktrouve);
			return true;
		}
	}

	return false;
}
