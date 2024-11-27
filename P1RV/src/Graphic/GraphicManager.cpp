#include "GraphicManager.h"

void GraphicManager::DrawBlock(Block* block, const Vector2I& chunkPosition)
{
    // calculate the model matrix for each object and pass it to shader before drawing
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    model = glm::translate(model, glm::vec3(block->getPosition().getX() + chunkPosition.getX(), block->getPosition().getY(), block->getPosition().getZ() + chunkPosition.getZ()));
    ourShader.setMat4("model", model);

    // bind textures on corresponding texture units

    for (int j = 0; j < 6; j++)
    {
        textureManager.BindTexture(block->getTexturei(j));
        glDrawArrays(GL_TRIANGLES, j * 6, 6);
    }
}

void GraphicManager::DrawChunk(Chunk* chunk)
{
    unordered_map<Vector3I, Block*, Vector3I::HashFoncteur>* blocks = chunk->GetBlocks();

    for (pair<const Vector3I,Block*>& block : *blocks)
    {
        if (block.second != nullptr)
            this->DrawBlock(block.second,Vector2I(chunk->getPosition().getX()*chunk->getSizeX(), chunk->getPosition().getZ() * chunk->getSizeY()));
    }
}

void GraphicManager::DrawChunkManager(ChunkManager& chunkManager)
{
    unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* chunks = chunkManager.GetActiveChunks();

    for (pair<const Vector2I,Chunk*>& chunk : *chunks)
    {
        if (chunk.second != nullptr)
            this->DrawChunk(chunk.second);
    }
}

GraphicManager::GraphicManager() : ourShader("src/Graphic/Shader/shader.vs", "src/Graphic/Shader/shader.fs"),
    VAO(0),VBO(0)
{
}

GraphicManager::~GraphicManager()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GraphicManager::Load(GLFWwindow* window, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
    

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ///Shader ourShader("src/Shader/shader.vs", "src/Shader/shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = { //position vis à vis du spawn
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, //face arrière
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, //face avant
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //face gauche
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, //face droite
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //face dessous
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, //face dessus
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    textureManager.Load(ourShader);
}

void GraphicManager::Draw(unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT,float fov, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, GLFWwindow* window, ChunkManager& chunkManager)
{
    // render
        // ------
    glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // activate shader
    ourShader.use();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    // camera/view transformation
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    ourShader.setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);
   
    this->DrawChunkManager(chunkManager);
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
}
