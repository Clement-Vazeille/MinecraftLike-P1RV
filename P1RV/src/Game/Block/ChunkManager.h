#pragma once
#include "Chunk.h"
#include <unordered_map>
#include "../Maths/Vector2I.h"

//Class stockant l'ensemble des chunks du jeu
class ChunkManager
{
private:
	//On stock les chunks dans une unordered map car ça nous garantit un accès et un ajout rapide des chunks et qu'avec un tableau si la carte n'est pas un carré on aurait bcp de trous dans le tableau
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur> chunks;
public:
	void AddChunk(Chunk* chunk);
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	
	void LoadChunks(const glm::vec3& coordonneesJoueur); //fonction qui va charger les chunks à proximité du joueur

	void GenerateChunk(const Vector2I& coordonnesChunk); //fonction qui prend en entrée une coordonnée dans le repère chunk et qui va placer un chunk à cet emplacement si il n'y en a pas déjà un
};
