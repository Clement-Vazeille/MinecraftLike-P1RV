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

public:
	void AddChunk(Chunk* chunk);
	//unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	unordered_set<Chunk*>* GetActiveChunks();

	//fonction qui va charger et généré si besoin les chunks à proximité du joueur
	void LoadChunks(const glm::vec3& coordonneesJoueur); 
	
	//décharge les chunks éloignés du joueur, ils n'auront pas à être généré de nouveau
	void UnloadChunks(const glm::vec3& coordonneesJoueur);

	//fonction qui prend en entrée une coordonnée dans le repère chunk et qui va placer un chunk à cet emplacement si il n'y en a pas déjà un
	void GenerateChunk(const Vector2I& coordonnesChunk); 

	//Prend la position d'un joueur et renvoie si elle est legit ou pas
	bool isPositionAllowed(const glm::vec3& coordonneesJoueur);
};
