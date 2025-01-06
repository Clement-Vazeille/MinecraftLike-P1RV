#include "ChunkManager.h"
#include <iostream>
#include <algorithm>
#include "SpecificBlocks/GrassBlock.h"
#include "SpecificBlocks/GrassBlockSnow.h"
#include "SpecificBlocks/CraftingTable.h"
#include "SpecificBlocks/BirchWood.h"
#include "SpecificBlocks/Stone.h"
#include "SpecificBlocks/Dirt.h"
#include "SpecificBlocks/Leaves.h"
#include "SpecificBlocks/OakPlank.h"
#include "SpecificBlocks/OakWood.h"
#include "SpecificBlocks/Water.h"
#include "SpecificBlocks/Light/PurpleLight.h"
#include "SpecificBlocks/Light/RedLight.h"

int ChunkManager::DistanceChunks(const Vector2I& coordonnesChunk1, const Vector2I& coordonnesChunk2)
{
	return abs(coordonnesChunk1.getX()-coordonnesChunk2.getX()) + abs(coordonnesChunk1.getZ() - coordonnesChunk2.getZ());
}

void ChunkManager::RecentrerChunkPosition(Vector2I& coordChunk, Vector3I& coordBlock)
{
	if (coordBlock.getX() < 0)
	{
		coordChunk+=Vector2I((-coordBlock.getX()/16)-1,0);
		coordBlock.setX((coordBlock.getX() % 16) + 16);
	}
	if (coordBlock.getZ() < 0)
	{
		coordChunk += Vector2I(0,(-coordBlock.getZ() / 16) - 1);
		coordBlock.setZ((coordBlock.getZ() % 16) + 16);
	}
	if (coordBlock.getX() >= 16)
	{
		coordChunk += Vector2I((coordBlock.getX() / 16), 0);
		coordBlock.setX((coordBlock.getX() % 16));
	}
	if (coordBlock.getZ() >= 16)
	{
		coordChunk += Vector2I(0,(coordBlock.getZ() / 16));
		coordBlock.setZ((coordBlock.getZ() % 16));
	}
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

void ChunkManager::AddBlock(const Vector2I& coordChunk, const Vector3I& coordBlock, const glm::vec3& coordonneesJoueur,int IDblock)
{
	Vector2I coordChunkCopie(coordChunk);
	Vector3I coordBlockCopie(coordBlock);
	RecentrerChunkPosition(coordChunkCopie, coordBlockCopie);
	if (chunks.count(coordChunkCopie)) //test d' existence du chunk
	{
		Block* blockCree = nullptr;
		if(IDblock == 0)
			blockCree = new GrassBlock(coordBlockCopie);
		if (IDblock == 1)
			blockCree = new GrassBlockSnow(coordBlockCopie);
		if (IDblock == 2)
			blockCree = new CraftingTable(coordBlockCopie);
		if (IDblock == 3)
			blockCree = new BirchWood(coordBlockCopie);
		if (IDblock == 4)
			blockCree = new PurpleLight(coordBlockCopie);
		if (IDblock == 5)
			blockCree = new RedLight(coordBlockCopie);
		if (IDblock == 6)
			blockCree = new Leaves(coordBlockCopie);
		if (IDblock == 7)
			blockCree = new Dirt(coordBlockCopie);
		if (IDblock == 8)
			blockCree = new Stone(coordBlockCopie);
		if (IDblock == 9)
			blockCree = new Water(coordBlockCopie);

		chunks.at(coordChunkCopie)->AddBlock(blockCree);
		if (!this->isPositionAllowed(coordonneesJoueur))
		{
			this->DestroyBlock(coordChunkCopie, coordBlockCopie);
			return;
		}

		if (blockCree != nullptr)
		{
			if (blockCree->isLight())
			{
				LightData* lightData = new LightData;
				lightData->chunkPosition = coordChunkCopie;
				lightData->sourcePosition = coordBlockCopie;
				lightData->lightColor = static_cast<LightBlock*>(blockCree)->getColor();

				lights.insert(lightData);
			}
		}
	}
}

void ChunkManager::DestroyBlock(const Vector2I& coordChunk, const Vector3I& coordBlock)
{
	if (chunks.count(coordChunk)) //test d' existence du chunk
	{
		if (chunks[coordChunk]->GetBlocks()->at(coordBlock))
		{
			for (auto light : lights)
			{
				if(light->chunkPosition==coordChunk && light->sourcePosition == coordBlock)
				{
					lights.erase(light);
					break;
				}
			}
			
		}
		chunks.at(coordChunk)->DestroyBlock(coordBlock);
	}
}

void ChunkManager::LoadChunks(const glm::vec3& coordonneesJoueur)
{
	//on va tenter de charger tout les chunks a 3/4 chunks de distance
	Vector2I chunkjoueur(coordonneesJoueur);

	int distanceChargement = renderDistance;
	
	//On se deplace sur l'ensemble des blocs qui sont au plus a une distance "distanceChargement" du joueur
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
	else {  //Si le chunk est deja genere mais n'est pas charge on le charge
		if (!activeChunks.count(chunks.at(coordonneesChunk)))
			activeChunks.insert(chunks.at(coordonneesChunk));
	}
}

bool ChunkManager::isPositionAllowed(const glm::vec3& coordonneesJoueur)
{
	glm::vec3 coordonneesReel = coordonneesJoueur + glm::vec3(0.5f, 0.5f, 0.5f);
	//Parametrage de la taille du joueur ainsi que de la hauteur de ses yeux
	float joueurTailleX = 0.25f;
	float joueurTailleY = 1.6f;
	float joueurTailleZ = 0.25f;
	float ratioHauteurYeux = 0.80f;
	glm::vec3 playerMins(coordonneesReel.x - (joueurTailleX/2.f), coordonneesReel.y - (joueurTailleY * ratioHauteurYeux), coordonneesReel.z - (joueurTailleZ / 2.f));
	glm::vec3 playerMaxs(coordonneesReel.x + (joueurTailleX / 2.f), coordonneesReel.y + (joueurTailleY * (1-ratioHauteurYeux)), coordonneesReel.z + (joueurTailleZ / 2.f));

	//boucle for qui va parcourir les blocs proches du joueur (en 3*4*3 pour le moment) puis qui va check si il y a collision entre le joueur et chacun des blocs en mode aabb
	for (int deltaX = -1; deltaX <= 1; deltaX++)
	{
		for (int deltaY = -2; deltaY <= 1; deltaY++)
		{
			for (int deltaZ = -1; deltaZ <= 1; deltaZ++)
			{
				Vector2I cooChunkActuel;
				Vector3I cooBlockActuel;
				Block* block = nullptr;
				if (findBlock(coordonneesReel + glm::vec3(deltaX, deltaY, deltaZ), &cooChunkActuel, &cooBlockActuel, &block))
				{
					if (block->hasCollisions())
					{
						glm::vec3 blockMins(cooBlockActuel.getX() + cooChunkActuel.getX() * 16, cooBlockActuel.getY(), cooBlockActuel.getZ() + (cooChunkActuel.getZ() * 16));
						glm::vec3 blockMaxs(blockMins.x + 1, blockMins.y + 1, blockMins.z + 1);

						if (collisionAABB(playerMins, playerMaxs, blockMins, blockMaxs))
							return false;
					}
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

	if (chunks.count(chunktrouve)) //Test de si il y a un chunk ou non a l'emplacement
	{
		if (chunks[chunktrouve]->GetBlocks()->count(blocktrouve)) //Test de si il y a un bloc ou non a l'emplacement
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

const unordered_set<LightData*>* ChunkManager::getLights() const
{
	return &lights;
}
