#pragma once
#include "../IncludeLibrairies.h"
#include "Shader/shader_s.h"
#include "Texture/TextureManager.h"

#include "../Game/Block/Chunk.h"
#include "../Game/Block/ChunkManager.h"
#include "../Game/HotBar.h"
#include "MaFenetre.h"


//Classe qui manage la partie Graphique de l'application
//Elle prend en entree une fenetre ainsi que l'ensemble des blocks et va dessiner les blocks sur la fenetre

// !!!!!Il n'est suppose avoir qu'une seule instance de cette classe!!!!!
class GraphicManager
{
private:
	TextureManager textureManager;
	Shader ourShader;
	Shader selectionShader;
	Shader viseurShader;
	
	Shader hotbarShader;
	Shader hotbarSelectionShader;
	Shader hotbarBlockShader;

	unsigned int VBOblock, VAOblock, EBOblock; //used by blocks, block selection and will be used for hotbarBlocks
	unsigned int VBOviseur, VAOviseur, EBOviseur;
	unsigned int VBOhotbar, VAOhotbar, EBOhotbar;
	unsigned int VBOhotbarSelector, VAOhotbarSelector, EBOhotbarSelector;

	//Fonctions utilitaires qui permettent de dessiner nos éléments
	void DrawBlock(Block* block, const Vector2I& chunkPosition);
	void DrawChunk(Chunk* chunk);
	void DrawChunkManager(ChunkManager* chunkManager);

	void HighlightBlock(Block* block, const Vector2I& chunkPosition);

	void DrawViseur(float windowRatio);

	void DrawHotbar();
	void DrawHotbarSelection();
	void DrawHotbarBlocks(HotBar* hotbar);

public:
	GraphicManager();
	~GraphicManager();

	//Charge les donnees geometriques d'un cube (VAO/VBO)
	void Load(MaFenetre* fenetre);
	//Dessine l'ensemble des blocks contenus dans le chunkManager dans la fenetre
	void Draw(MaFenetre* fenetre);
};

