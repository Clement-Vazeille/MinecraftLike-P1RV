#pragma once
#include "Block/ChunkManager.h"

class BlockSelector
{
private:
	//Regarde si il y a une collision avec un block en particulier, renvoie la distance entre la caméra et le point de collision
	//renvoie 0 si il n'y a pas de collision
	float CheckCollision(Block** selectedBlock, Vector2I* selectedBlockChunkPosition,
		const glm::vec3& cameraPos, const glm::vec3& cameraFront);

public: 
	//Trouve le block actuel pointé par le joueur avec sa souris et renvoie ses coordonnées dans selectedBlock et selectedBlockChunkPosition
	void SelectBlock(Block** selectedBlock, Vector2I* selectedBlockChunkPosition, ChunkManager* chunkManager,
		const glm::vec3& cameraPos, const glm::vec3& cameraFront);

	
};

