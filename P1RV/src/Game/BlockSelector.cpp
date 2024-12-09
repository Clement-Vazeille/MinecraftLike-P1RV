#include "BlockSelector.h"

void BlockSelector::SelectBlock(Block** selectedBlock, Vector2I* selectedBlockChunkPosition, ChunkManager* chunkManager, const glm::vec3& cameraPos, const glm::vec3& cameraFront)
{
	//L'idée actuelle est de prendre 3/4 blocs à une certaine distance de la position de la caméra vers là où regarder la souris
	//pour chachun de ses blocs on va faire un check de si il y a un block ou non à cet emplacement et dans les blocs voisins (3x3)
	//puis si il y a un block on va faire un check de collisions entre la demidroite lancée dans la direction du regard et le bloc
	//on check avec chacun des plans du block
	//on trouvera ainsi un certain nombre de collisions et on gardera celle qui a lieu à la distance la plus faible du joueur
	
	int nbZonesTestes = 5;
	float pas = 0.8f;
	float currentBestDitance = FLT_MAX;

	//TODO : utiliser un set pour vérifier qu'on check pas plusieurs fois les collisions d'un même block
	for (int i = 0; i < nbZonesTestes; i++)
	{
		glm::vec3 centreZone = cameraPos + glm::vec3(cameraFront.x*i, cameraFront.y*i, cameraFront.z*i);
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
		}
		if (currentBestDitance != FLT_MAX)
		{
			//faut rajouter un assignement des coordonnées du block sélectionné ici
			return;
		}
	}
}

//TODO : aussi renvoyer la face où il y a la collision
float BlockSelector::CheckCollision(Block** selectedBlock, Vector2I* selectedBlockChunkPosition, const glm::vec3& cameraPos, const glm::vec3& cameraFront)
{
	return 0.0f;
}
