#include "GraphicManager.h"

void GraphicManager::DrawBlock(Block* block, const Vector2I& chunkPosition)
{
    //Calcul de la matrice model pour l'objet actuel qui est ensuite envoyé au shader
    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::translate(model, glm::vec3(block->getPosition().getX() + chunkPosition.getX(), block->getPosition().getY(), block->getPosition().getZ() + chunkPosition.getZ()));
    ourShader.setMat4("model", model);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glLineWidth(10);
    //On assigne à chaque face sa texture correspondante
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
            this->DrawBlock(block.second,Vector2I(chunk->getPosition().getX()*chunk->getSizeX(), chunk->getPosition().getZ() * chunk->getSizeZ()));
    }
}

void GraphicManager::DrawChunkManager(ChunkManager* chunkManager)
{
    //unordered_map<Vector2I, Chunk*, Vector2I::HashFoncteur>* chunks = chunkManager->GetActiveChunks();
    unordered_set<Chunk*>* chunks = chunkManager->GetActiveChunks();

    for (Chunk* chunk : *chunks)
    {
        if (chunk != nullptr)
            this->DrawChunk(chunk);
    }
}

void GraphicManager::HighlightBlock(Block* block, const Vector2I& chunkPosition)
{
    if (block != nullptr)
    {
        //Calcul de la matrice model pour l'objet actuel qui est ensuite envoyé au shader
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(block->getPosition().getX() + (chunkPosition.getX()*16), block->getPosition().getY(), block->getPosition().getZ() + (chunkPosition.getZ() * 16)));
        selectionShader.setMat4("model", model);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(10);
        //On assigne à chaque face sa texture correspondante
        for (int j = 0; j < 6; j++)
        {
            textureManager.BindTexture(block->getTexturei(j));
            glDrawArrays(GL_TRIANGLES, j * 6, 6);
        }
        glLineWidth(1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

GraphicManager::GraphicManager() : ourShader("src/Graphic/Shader/shader.vs", "src/Graphic/Shader/shader.fs"),
    selectionShader("src/Graphic/Shader/shaderSelection.vs","src/Graphic/Shader/shaderSelection.fs"),
    VAO(0),VBO(0)
{
}

GraphicManager::~GraphicManager()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void GraphicManager::Load(MaFenetre* fenetre)
{
    // configuration globale des états d'openGL
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // initialisation des sommets d'un cube
    // ------------------------------------------------------------------
    float vertices[] = { //position vis à vis du spawn
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, //face arriere
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,

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
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //face dessous
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //face dessus
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  
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

    glEnable(GL_CULL_FACE);
}

void GraphicManager::Draw(MaFenetre* fenetre)
{
    //clear du rendu précédent
    glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //activation des shaders
    ourShader.use();

    //Transmission de la matrice de projection du monde aux shaders
    glm::mat4 projection = glm::perspective(glm::radians(fenetre->getfov()), (float)fenetre->getSCR_WIDTH() / (float)fenetre->getSCR_HEIGHT(), 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    //Transmission de la matrice de vue de la caméra aux shaders
    glm::mat4 view = glm::lookAt(fenetre->getcameraPos(), fenetre->getcameraPos() + fenetre->getcameraFront(), fenetre->getcameraUp());
    ourShader.setMat4("view", view);

    //On assigne le VAO des cubes
    glBindVertexArray(VAO);
   
    //On dessine le monde
    this->DrawChunkManager(fenetre->getChunkManager());

    selectionShader.use();
    selectionShader.setMat4("projection", projection);
    selectionShader.setMat4("view", view);

    this->HighlightBlock(fenetre->getHighlightedBlock(), fenetre->getHighlightedBlockChunkPosition());

    //On swap les buffers glfw et on poll les events d'input output
    glfwSwapBuffers(fenetre->getWindow());
    glfwPollEvents();
}
