#pragma once
#include "../IncludeLibrairies.h"
#include "Shader/shader_s.h"
#include "Texture/TextureManager.h"

#include "../Game/Block/Chunk.h"
#include "../Game/Block/ChunkManager.h"
#include "MaFenetre.h"


//Classe qui manage la partie Graphique de l'application
//Elle prend en entrée une fenetre ainsi que l'ensemble des blocks et va dessiner les blocks sur la fenetre

// !!!!!Il n'est supposé avoir qu'une seule instance de cette classe!!!!!
class GraphicManager
{
private:
	TextureManager textureManager;
	Shader ourShader;
	unsigned int VBO, VAO;

	//Fonctions utilitaires qui permettent de dessiner nos éléments
	void DrawBlock(Block* block, const Vector2I& chunkPosition);
	void DrawChunk(Chunk* chunk);
	void DrawChunkManager(ChunkManager* chunkManager);
public:
	GraphicManager();
	~GraphicManager();

	//Charge les données géométriques d'un cube (VAO/VBO)
	void Load(MaFenetre* fenetre);
	//Dessine l'ensemble des blocks contenus dans le chunkManager dans la fenetre
	void Draw(MaFenetre* fenetre);
};

