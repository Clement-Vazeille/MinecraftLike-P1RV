#pragma once
#include "../Include.h"
#include "Shader/shader_s.h"
#include "Texture/TextureManager.h"

#include "../Game/Block/Chunk.h"
#include "../Game/Block/ChunkManager.h"
#include "MaFenetre.h"

class GraphicManager
{
private:
	TextureManager textureManager;
	Shader ourShader;
	unsigned int VBO, VAO;

	void DrawBlock(Block* block, const Vector2I& chunkPosition);
	void DrawChunk(Chunk* chunk);
	void DrawChunkManager(ChunkManager& chunkManager);
public:
	GraphicManager();
	~GraphicManager();

	void Load(MaFenetre* fenetre);
	void Draw(MaFenetre*,ChunkManager& chunkManager);
};

