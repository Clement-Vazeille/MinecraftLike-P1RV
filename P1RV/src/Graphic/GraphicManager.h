#pragma once
#include "../IncludeLibrairies.h"
#include "Shader/shader_s.h"
#include "Texture/TextureManager.h"

#include "../Game/Block/Chunk.h"
#include "../Game/Block/ChunkManager.h"
#include "MaFenetre.h"


//Classe qui manage la partie Graphique de l'application
//Elle prend en entrée une fenetre ainsi que l'ensemble des blocks et va dessiner les blocks sur la fenetre

// !!!!!Il n'est supposEavoir qu'une seule instance de cette classe!!!!!
class GraphicManager
{
private:
	TextureManager textureManager;
	Shader ourShader;
	Shader selectionShader;
	Shader viseurShader;
	unsigned int VBOblock, VAOblock, EBOblock;
	unsigned int VBOviseur, VAOviseur, EBOviseur;

	//Fonctions utilitaires qui permettent de dessiner nos éléments
	void DrawBlock(Block* block, const Vector2I& chunkPosition);
	void DrawChunk(Chunk* chunk);
	void DrawChunkManager(ChunkManager* chunkManager);

	void HighlightBlock(Block* block, const Vector2I& chunkPosition);

	void DrawViseur();
public:
	GraphicManager();
	~GraphicManager();

	//Charge les données géométriques d'un cube (VAO/VBO)
	void Load(MaFenetre* fenetre);
	//Dessine l'ensemble des blocks contenus dans le chunkManager dans la fenetre
	void Draw(MaFenetre* fenetre);
};

