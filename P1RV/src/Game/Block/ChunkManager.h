#pragma once
#include "Chunk.h"
#include <unordered_map>
#include <unordered_set>
#include "../Maths/Vector2I.h"

//Class stockant l'ensemble des chunks du jeu
class ChunkManager
{
private:
	//On stock les chunks dans une unordered map car ça nous garantit un accès et un ajout rapide des chunks et qu'avec un tableau si la carte n'est pas un carré on aurait bcp de trous dans le tableau
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur> chunks;

	unordered_set<Chunk*> activeChunks;

	int DistanceChunks(const Vector2I& coordonnesChunk1, const Vector2I& coordonnesChunk2);
	int renderDistance = 2;

public:
	void AddChunk(Chunk* chunk);
	//unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	unordered_set<Chunk*>* GetActiveChunks();

	//Fonction de création/destruction de blocks appelées lors d'un click de l'utilisateur
	void AddBlock(const Vector2I& coordChunk, const Vector3I& coordBlock);
	void DestroyBlock(const Vector2I& coordChunk, const Vector3I& coordBlock);

	//fonction qui va charger et généré si besoin les chunks à proximité du joueur
	void LoadChunks(const glm::vec3& coordonneesJoueur); 
	
	//décharge les chunks éloignés du joueur, ils n'auront pas à être généré de nouveau
	void UnloadChunks(const glm::vec3& coordonneesJoueur);

	//fonction qui prend en entrée une coordonnée dans le repère chunk et qui va placer un chunk à cet emplacement si il n'y en a pas déjà un
	void GenerateChunk(const Vector2I& coordonnesChunk); 

	//Prend la position d'un joueur et renvoie si elle est legit ou pas
	bool isPositionAllowed(const glm::vec3& coordonneesJoueur);

	//Renvoie true si il y a une collision entre les a et b
	bool collisionAABB(const glm::vec3& aMins,const glm::vec3& aMaxs, const glm::vec3& bMins, const glm::vec3& bMaxs);

	//Prend en entrée une coordonnée et renvoie si il y a un bloc ou non à cet emplacement
	//Si les pointeurs sont non nuls les valeurs où ils pointent sont remplacés par les valeurs du bloc correspondant si il existe
	bool findBlock(const glm::vec3& coordonnees, Vector2I* sortieCoordChunk, Vector3I* sortieCoordBloc, Block** block);
};
