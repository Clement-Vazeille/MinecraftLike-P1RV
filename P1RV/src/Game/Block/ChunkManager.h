#pragma once
#include "Chunk.h"
#include <unordered_map>
#include <unordered_set>
#include "../Maths/Vector2I.h"
#include "../LightData.h"

//Class stockant l'ensemble des chunks du jeu
class ChunkManager
{
private:
	//On stock les chunks dans une unordered map car ca nous garantit un acces et un ajout rapide des chunks et qu'avec un tableau si la carte n'est pas un carreon aurait bcp de trous dans le tableau
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur> chunks;

	unordered_set<Chunk*> activeChunks;

	unordered_set<LightData*> lights;

	int DistanceChunks(const Vector2I& coordonnesChunk1, const Vector2I& coordonnesChunk2);
	int renderDistance = 2;

	//Modifie une coordonne de chunk et une coordonne de block pour qu'elles devient valident, si la coordonne du bloc dans le repere du chunk depasse la limite du chunk alors on change le chunk du block
	void RecentrerChunkPosition(Vector2I& coordChunk, Vector3I& coordBlock);
public:
	void AddChunk(Chunk* chunk);
	//unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	unordered_set<Chunk*>* GetActiveChunks();

	//Fonction de creation/destruction de blocks appelees lors d'un click de l'utilisateur
	//La fonction addBlock prend en entree les coordonnees du joueur pour verifier que le joueur n'est pas positionne sur le bloc qui est place
	void AddBlock(const Vector2I& coordChunk, const Vector3I& coordBlock, const glm::vec3& coordonneesJoueur,int idBlock);
	void DestroyBlock(const Vector2I& coordChunk, const Vector3I& coordBlock);

	//fonction qui va charger et genere si besoin les chunks a proximite du joueur
	void LoadChunks(const glm::vec3& coordonneesJoueur); 
	
	//decharge les chunks eloignes du joueur, ils n'auront pas a etre genere de nouveau
	void UnloadChunks(const glm::vec3& coordonneesJoueur);

	//fonction qui prend en entree une coordonnee dans le repere chunk et qui va placer un chunk a cet emplacement si il n'y en a pas deja un
	void GenerateChunk(const Vector2I& coordonnesChunk); 

	//Prend la position d'un joueur et renvoie si elle est legit ou pas
	bool isPositionAllowed(const glm::vec3& coordonneesJoueur);

	//Renvoie true si il y a une collision entre les a et b
	bool collisionAABB(const glm::vec3& aMins,const glm::vec3& aMaxs, const glm::vec3& bMins, const glm::vec3& bMaxs);

	//Prend en entree une coordonnee et renvoie si il y a un bloc ou non a cet emplacement
	//Si les pointeurs sont non nuls les valeurs ou ils pointent sont remplacee par les valeurs du bloc correspondant si il existe
	bool findBlock(const glm::vec3& coordonnees, Vector2I* sortieCoordChunk, Vector3I* sortieCoordBloc, Block** block);

	const unordered_set<LightData*>* getLights() const;
};
