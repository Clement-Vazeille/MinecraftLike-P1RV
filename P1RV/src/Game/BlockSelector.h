#pragma once
#include "Block/ChunkManager.h"

class BlockSelector
{
private:
	//trouve la face dans laquelle il y a la collision et la renvoie dans le vector faceDirection
	void FindCollisionFace(Vector3I* faceDirection, Block* selectedBlock, Vector2I selectedBlockChunkPosition,
		const glm::vec3& cameraPos, const glm::vec3& cameraFront);
	//renvoie si il y a ou nn une collision entre une face et la droite de vision de la caméra et si il y en a une renvoie la distance entre la camera et la collision
	float CollisionFaceDroite(Block* selectedBlock, Vector2I selectedBlockChunkPosition,
		const glm::vec3& cameraPos, const glm::vec3& cameraFront,int numeroFace); 

public: 
	//Trouve le block actuel pointé par le joueur avec sa souris et renvoie ses coordonnées dans selectedBlock et selectedBlockChunkPosition et sa face dans faceDirection
	void SelectBlock(Block** selectedBlock, Vector2I* selectedBlockChunkPosition, Vector3I* faceDirection, 
		ChunkManager* chunkManager,const glm::vec3& cameraPos, const glm::vec3& cameraFront);

	
};

