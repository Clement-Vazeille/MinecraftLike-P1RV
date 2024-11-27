#pragma once
#include "../Include.h"
#include "Shader/shader_s.h"
#include "Texture/TextureManager.h"

#include "../Game/Block/Chunk.h"
#include "../Game/Block/ChunkManager.h"

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

	void Load(GLFWwindow* window, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
	void Draw(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT, float fov, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, GLFWwindow* window,ChunkManager& chunkManager);
};

