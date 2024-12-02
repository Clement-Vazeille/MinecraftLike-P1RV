#pragma once
#include "Chunk.h"
#include <unordered_map>
#include "../Maths/Vector2I.h"

//Class stockant l'ensemble des chunks du jeu
class ChunkManager
{
private:
	//On stock les chunks dans une unordered map car �a nous garantit un acc�s et un ajout rapide des chunks et qu'avec un tableau si la carte n'est pas un carr� on aurait bcp de trous dans le tableau
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur> chunks;
public:
	void AddChunk(Chunk* chunk);
	unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* GetActiveChunks();
	
	void LoadChunks(const glm::vec3& coordonneesJoueur); //fonction qui va charger les chunks � proximit� du joueur

	void GenerateChunk(const Vector2I& coordonnesChunk); //fonction qui prend en entr�e une coordonn�e dans le rep�re chunk et qui va placer un chunk � cet emplacement si il n'y en a pas d�j� un
};
