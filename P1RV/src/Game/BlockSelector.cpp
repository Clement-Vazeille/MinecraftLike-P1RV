#include "BlockSelector.h"

void BlockSelector::FindCollisionFace(Vector3I* faceDirection, Block* selectedBlock, Vector2I selectedBlockChunkPosition, const glm::vec3& cameraPos, const glm::vec3& cameraFront)
{
	//l'idée est de projeter la droite qui par de cameraPos orientée dans cameraFront dans le plan de chacune des faces puis de regarder si le point est ou nn sur la face
	//on va ensuite prendre la face ou le point est le plus proche de la caméra
	float distanceMin = FLT_MAX;
	for (int numeroFace = 0; numeroFace < 6; numeroFace++)
	{
		float distanceFaceActuelle = CollisionFaceDroite(selectedBlock, selectedBlockChunkPosition, cameraPos, cameraFront, numeroFace);
		if (distanceFaceActuelle != 0.f && distanceFaceActuelle < distanceMin)
		{
			distanceMin = distanceFaceActuelle;

			//on assigne la bonne valeur à face direction
			if (numeroFace == 0)
				*faceDirection = Vector3I(-1, 0, 0);
			if (numeroFace == 1)
				*faceDirection = Vector3I(1, 0, 0);
			if (numeroFace == 2)
				*faceDirection = Vector3I(0, 0, -1);
			if (numeroFace == 3)
				*faceDirection = Vector3I(0, 0, 1); 
			if (numeroFace == 4)
				*faceDirection = Vector3I(0, -1, 0);
			if (numeroFace == 5)
				*faceDirection = Vector3I(0, 1, 0);
		}
	}
	if (distanceMin == FLT_MAX)
		*faceDirection = Vector3I(0, 1, 0);
}

float BlockSelector::CollisionFaceDroite(Block* selectedBlock, Vector2I selectedBlockChunkPosition, const glm::vec3& cameraPos, const glm::vec3& cameraFront, int numeroFace)
{
	glm::vec3 pointSurLePlan;
	if (numeroFace == 0) //face arriere
	{
		//on fixe la coordonnée x du point de la projection
		pointSurLePlan.x = selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16;
		if (cameraFront.x == 0)
			return 0.f;
		float distance = (pointSurLePlan.x - cameraPos.x) / cameraFront.x; //positive ou négative
		pointSurLePlan.y = distance * cameraFront.y + cameraPos.y;
		pointSurLePlan.z = distance * cameraFront.z + cameraPos.z;
		
		//check de si le point est dans la face
		if (
			pointSurLePlan.y <= selectedBlock->getPosition().getY() + 1 &&
			pointSurLePlan.y >= selectedBlock->getPosition().getY() &&
			pointSurLePlan.z <= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 + 1 &&
			pointSurLePlan.z >= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16
			)
			return abs(distance);
	}
	if (numeroFace == 1) //face avant
	{
		//on fixe la coordonnée x du point de la projection
		pointSurLePlan.x = selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16 + 1;
		if (cameraFront.x == 0)
			return 0.f;
		float distance = (pointSurLePlan.x - cameraPos.x) / cameraFront.x; //positive ou négative
		pointSurLePlan.y = distance * cameraFront.y + cameraPos.y;
		pointSurLePlan.z = distance * cameraFront.z + cameraPos.z;

		//check de si le point est dans la face
		if (
			pointSurLePlan.y <= selectedBlock->getPosition().getY() + 1 &&
			pointSurLePlan.y >= selectedBlock->getPosition().getY() &&
			pointSurLePlan.z <= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 + 1 &&
			pointSurLePlan.z >= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16
			)
			return abs(distance);
	}
	if (numeroFace == 2) //face gauche
	{
		//on fixe la coordonnée z du point de la projection
		pointSurLePlan.z = selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 ;
		if (cameraFront.z == 0)
			return 0.f;
		float distance = (pointSurLePlan.z - cameraPos.z) / cameraFront.z; //positive ou négative
		pointSurLePlan.y = distance * cameraFront.y + cameraPos.y;
		pointSurLePlan.x = distance * cameraFront.x + cameraPos.x;

		//check de si le point est dans la face
		if (
			pointSurLePlan.y <= selectedBlock->getPosition().getY() + 1 &&
			pointSurLePlan.y >= selectedBlock->getPosition().getY() &&
			pointSurLePlan.x <= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16 + 1 &&
			pointSurLePlan.x >= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16
			)
			return abs(distance);
	}
	if (numeroFace == 3) //face droite
	{
		//on fixe la coordonnée z du point de la projection
		pointSurLePlan.z = selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 + 1;
		if (cameraFront.z == 0)
			return 0.f;
		float distance = (pointSurLePlan.z - cameraPos.z) / cameraFront.z; //positive ou négative
		pointSurLePlan.y = distance * cameraFront.y + cameraPos.y;
		pointSurLePlan.x = distance * cameraFront.x + cameraPos.x;

		//check de si le point est dans la face
		if (
			pointSurLePlan.y <= selectedBlock->getPosition().getY() + 1 &&
			pointSurLePlan.y >= selectedBlock->getPosition().getY() &&
			pointSurLePlan.x <= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16 + 1 &&
			pointSurLePlan.x >= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16
			)
			return abs(distance);
	}
	if (numeroFace == 4) //face dessous 
	{
		//on fixe la coordonnée y du point de la projection
		pointSurLePlan.y = selectedBlock->getPosition().getY();
		if (cameraFront.y == 0)
			return 0.f;
		float distance = (pointSurLePlan.y - cameraPos.y) / cameraFront.y; //positive ou négative
		pointSurLePlan.z = distance * cameraFront.z + cameraPos.z;
		pointSurLePlan.x = distance * cameraFront.x + cameraPos.x;

		//check de si le point est dans la face
		if (
			pointSurLePlan.z <= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 + 1 &&
			pointSurLePlan.z >= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 &&
			pointSurLePlan.x <= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16 + 1 &&
			pointSurLePlan.x >= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16
			)
			return abs(distance);
	}
	if (numeroFace == 5) //face dessus
	{
		//on fixe la coordonnée y du point de la projection
		pointSurLePlan.y = selectedBlock->getPosition().getY() + 1;
		if (cameraFront.y == 0)
			return 0.f;
		float distance = (pointSurLePlan.y - cameraPos.y) / cameraFront.y; //positive ou négative
		pointSurLePlan.z = distance * cameraFront.z + cameraPos.z;
		pointSurLePlan.x = distance * cameraFront.x + cameraPos.x;

		//check de si le point est dans la face
		if (
			pointSurLePlan.z <= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 + 1 &&
			pointSurLePlan.z >= selectedBlock->getPosition().getZ() + selectedBlockChunkPosition.getZ() * 16 &&
			pointSurLePlan.x <= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16 + 1 &&
			pointSurLePlan.x >= selectedBlock->getPosition().getX() + selectedBlockChunkPosition.getX() * 16
			)
			return abs(distance);
	}
	return 0.0f;
}

void BlockSelector::SelectBlock(Block** selectedBlock, Vector2I* selectedBlockChunkPosition, Vector3I* faceDirection, ChunkManager* chunkManager, const glm::vec3& cameraPos, const glm::vec3& cameraFront)
{
	//L'idée actuelle est de prendre 3/4 blocs à une certaine distance de la position de la caméra vers là où regarder la souris
	//pour chachun de ses blocs on va faire un check de si il y a un block ou non à cet emplacement et dans les blocs voisins (3x3)
	//puis si il y a un block on va faire un check de collisions entre la demidroite lancée dans la direction du regard et le bloc
	//on check avec chacun des plans du block
	//on trouvera ainsi un certain nombre de collisions et on gardera celle qui a lieu à la distance la plus faible du joueur
	
	float porteSelection = 10.f;
	float pas = 0.2f;
	int nbZonesTestes = porteSelection/pas; //la valeur numérique
	
	//float currentBestDitance = FLT_MAX;

	//TODO : utiliser un set pour vérifier qu'on check pas plusieurs fois les collisions d'un même block
	for (int i = 0; i < nbZonesTestes; i++)
	{
		glm::vec3 zoneTestActuelle = cameraPos + glm::vec3(cameraFront.x*i*pas, cameraFront.y*i*pas, cameraFront.z*i*pas);

		Vector2I blockChunk;
		Vector3I blockPosition;
		Block* block;

		if (chunkManager->findBlock(zoneTestActuelle, &blockChunk, &blockPosition, &block))
		{
			*selectedBlock = block;
			*selectedBlockChunkPosition = blockChunk;
			this->FindCollisionFace(faceDirection,block,blockChunk,cameraPos,cameraFront);
			return;
		}

		/* version plus complexe d'un test
		
		for (int xDelta = -1; xDelta <= 1; xDelta++)
		{
			for (int yDelta = -1; yDelta <= 1; yDelta++)
			{
				for (int zDelta = -1; zDelta <= 1; zDelta++)
				{
					//test de si il y a un block où nn //pour le moment on pourrait s'arréter là pour un petit test intermédiare
					//check de collision avec le bloc centré + le delta
					Vector2I blockChunk;
					Vector3I blockPosition;
					Block* block;
					if (chunkManager->findBlock(centreZone + glm::vec3(xDelta, yDelta, zDelta), &blockChunk, &blockPosition, &block))
					{

					}
				}
			}
		}*/

	}
	*selectedBlock = nullptr;
	*selectedBlockChunkPosition = Vector2I();
}
