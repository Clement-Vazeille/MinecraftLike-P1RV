﻿#include "GraphicManager.h"

void GraphicManager::DrawBlock(Block* block, const Vector2I& chunkPosition)
{
    //Calcul de la matrice model pour l'objet actuel qui est ensuite envoyé au shader
    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::translate(model, glm::vec3(block->getPosition().getX() + chunkPosition.getX(), block->getPosition().getY(), block->getPosition().getZ() + chunkPosition.getZ()));
    ourShader.setMat4("model", model);
    
    //On assigne à chaque face sa texture correspondante
    for (int j = 0; j < 6; j++)
    {
        textureManager.BindTexture(block->getTexturei(j));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(j*6*sizeof(int)));
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

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glLineWidth(1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GraphicManager::DrawViseur(float windowRatio)
{
    float centreDelta = 0.02f;
   
    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation,glm::vec3(-centreDelta,0,0));
    viseurShader.setMat4("transformation", transformation);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(centreDelta, 0, 0));
    viseurShader.setMat4("transformation", transformation);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0, centreDelta *windowRatio, 0));
    transformation = glm::rotate(transformation, glm::radians(90.0f), glm::vec3(0, 0, 1));
    transformation = glm::scale(transformation, glm::vec3(windowRatio,1/windowRatio,1));
    viseurShader.setMat4("transformation", transformation);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0, -centreDelta * windowRatio, 0));
    transformation = glm::rotate(transformation, glm::radians(90.0f), glm::vec3(0, 0, 1));
    transformation = glm::scale(transformation, glm::vec3(windowRatio, 1 / windowRatio, 1));
    viseurShader.setMat4("transformation", transformation);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GraphicManager::DrawHotbar()
{
    textureManager.BindTexture("Assets/HUD/hotbar.png");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void GraphicManager::DrawHotbarSelection()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(5);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glLineWidth(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GraphicManager::DrawHotbarBlocks(HotBar* hotbar)
{

    glm::mat4 transformation = glm::mat4(1.0f);
    transformation = glm::translate(transformation, glm::vec3(0,0,-3.f));
    transformation = glm::scale(transformation, glm::vec3(0.09f, 0.09f, 0.09f));
    transformation = glm::rotate(transformation, glm::radians(45.0f), glm::vec3(1, 0, 0));
    transformation = glm::rotate(transformation, glm::radians(35.264f), glm::vec3(0, 1, 0)); //rotation correspond a repere classique -> repere isometrique
    hotbarBlockShader.setMat4("transformation", transformation);
    
    array<Block*, 10>* blocks = hotbar->getBlocks();
    for (int i = 0; i < blocks->size(); i++)
    {
        if (blocks->at(i) != nullptr)
        {
            glm::mat4 translation = glm::mat4(1.0f);
            translation = glm::translate(translation, glm::vec3(-0.475f +(i*0.1056f), -0.92f, 0));
            hotbarBlockShader.setMat4("translation", translation);

            Block* block = new Block;
            //On assigne à chaque face sa texture correspondante
            for (int j = 0; j < 6; j++)
            {
                textureManager.BindTexture(blocks->at(i)->getTexturei(j));
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(j * 6 * sizeof(int)));
            }
        }
    }
}

GraphicManager::GraphicManager() : ourShader("src/Graphic/Shader/shader.vs", "src/Graphic/Shader/shader.fs"),
    selectionShader("src/Graphic/Shader/shaderSelection.vs","src/Graphic/Shader/shaderSelection.fs"),
    viseurShader("src/Graphic/Shader/shaderViseur.vs", "src/Graphic/Shader/shaderViseur.fs"),
    hotbarShader("src/Graphic/Shader/shaderHotbar.vs", "src/Graphic/Shader/shaderHotbar.fs"),
    hotbarSelectionShader("src/Graphic/Shader/shaderHotbarSelection.vs", "src/Graphic/Shader/shaderHotbarSelection.fs"),
    hotbarBlockShader("src/Graphic/Shader/shaderHotbarBlock.vs", "src/Graphic/Shader/shaderHotbarBlock.fs"),
    skyboxShader("src/Graphic/Shader/shaderSkybox.vs", "src/Graphic/Shader/shaderSkybox.fs"),
    VAOblock(0),VBOblock(0),EBOblock(0),VAOviseur(0),VBOviseur(0),EBOviseur(0),
    VAOhotbar(0), VBOhotbar(0), EBOhotbar(0), VAOhotbarSelector(0), VBOhotbarSelector(0), EBOhotbarSelector(0),
    VAOskybox(0),VBOskybox(0),
    lightManager(new LightManager)
{
}

GraphicManager::~GraphicManager()
{
    glDeleteVertexArrays(1, &VAOblock);
    glDeleteBuffers(1, &VBOblock);
    glDeleteBuffers(1, &EBOviseur);
    glDeleteVertexArrays(1, &VAOviseur);
    glDeleteBuffers(1, &VBOviseur);
    glDeleteBuffers(1, &EBOviseur);
    glDeleteVertexArrays(1, &VAOhotbar);
    glDeleteBuffers(1, &VBOhotbar);
    glDeleteBuffers(1, &EBOhotbar);
    glDeleteVertexArrays(1, &VAOhotbarSelector);
    glDeleteBuffers(1, &VBOhotbarSelector); 
    glDeleteBuffers(1, &EBOhotbarSelector);
    glDeleteBuffers(1, &VAOskybox);
    glDeleteBuffers(1, &VBOskybox);
}

void GraphicManager::Load(MaFenetre* fenetre)
{
    
    // configuration globale des états d'openGL
    // -----------------------------
    

    // initialisation des sommets d'un cube
    // ------------------------------------------------------------------
    float verticesCube[] = { //position vis à vis du spawn
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,//face arriere
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, //face avant
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f, //face gauche
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f, //face droite
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f, //face dessous
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, //face dessus
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f 
    };

    unsigned int indicesCube[] = {
    0, 1, 2, 
    1, 0, 3,  

    4, 5, 6, 
    6, 7, 4, 

    8, 9, 10, 
    10, 11, 8,  

    12, 13, 14, 
    13, 12, 15,   

    16, 17, 18,
    18, 19, 16,

    20, 21, 22,
    21, 20, 23
    };

    glGenVertexArrays(1, &VAOblock);
    glGenBuffers(1, &VBOblock);
    glGenBuffers(1, &EBOblock);

    glBindVertexArray(VAOblock);

    glBindBuffer(GL_ARRAY_BUFFER, VBOblock);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOblock);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesCube), indicesCube, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    textureManager.Load(ourShader);
    
    // initialisation des sommets du viseur
    // ------------------------------------------------------------------
    float verticesViseur[] = { //position vis à vis du spawn
        //Format : 
        //-,-
        //+,-
        //+,+
        //-,+

         -0.01f, -0.005f,   
         0.01f, -0.005f,
         0.01f, 0.005f,
         -0.01f,  0.005f
    };
    
    unsigned int indicesViseur[] = {
    0, 1, 2, // bottom triangle
    2, 3, 0,  // top triangle
    };

    glGenVertexArrays(1, &VAOviseur);
    glGenBuffers(1, &VBOviseur);

    glGenBuffers(1, &EBOviseur);

    glBindVertexArray(VAOviseur);

    glBindBuffer(GL_ARRAY_BUFFER, VBOviseur);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOviseur);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesViseur), verticesViseur, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesViseur), indicesViseur, GL_STATIC_DRAW);
    

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // initialisation des sommets de la hotbar
    // ------------------------------------------------------------------
    float verticesHotbar[] = { //position vis à vis du spawn
        //Format : 
        //-,-
        //+,-
        //+,+
        //-,+
        0.225f, 0.f, 0.0f, 0.0f,
        0.775f, 0.f, 1.0f, 0.0f,
        0.775f, 0.082f, 1.0f, 1.0f,
        0.225f, 0.082f, 0.0f, 1.0f
    };

    unsigned int indicesHotbar[] = {
    0, 1, 2, // bottom triangle
    2, 3, 0,  // top triangle
    };

    glGenVertexArrays(1, &VAOhotbar);
    glGenBuffers(1, &VBOhotbar);
    glGenBuffers(1, &EBOhotbar);

    glBindVertexArray(VAOhotbar);

    glBindBuffer(GL_ARRAY_BUFFER, VBOhotbar);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOhotbar);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHotbar), verticesHotbar, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesHotbar), indicesHotbar, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // initialisation des sommets de la selection hotbar
    // ------------------------------------------------------------------
    float verticesHotbarSelection[] = { //position vis à vis du spawn
        //Format : 
        //-,-
        //+,-
        //+,+
        //-,+

        -0.106f, -0.992f,
         0.0f, -0.992f,
         0.0f, -0.85f,
         -0.106f,  -0.85f
    };

    unsigned int indicesHotbarSelection[] = {
    0, 1, 2, // bottom triangle
    2, 3, 0,  // top triangle
    };

    glGenVertexArrays(1, &VAOhotbarSelector);
    glGenBuffers(1, &VBOhotbarSelector);
    glGenBuffers(1, &EBOhotbarSelector);

    glBindVertexArray(VAOhotbarSelector);

    glBindBuffer(GL_ARRAY_BUFFER, VBOhotbarSelector);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOhotbarSelector);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesHotbarSelection), verticesHotbarSelection, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesHotbarSelection), indicesHotbarSelection, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //SkyBox
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &VAOskybox);
    glGenBuffers(1, &VBOskybox);

    glBindVertexArray(VAOskybox);

    glBindBuffer(GL_ARRAY_BUFFER, VBOskybox);

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
}

void GraphicManager::Draw(MaFenetre* fenetre)
{
    glEnable(GL_DEPTH_TEST);
    //clear du rendu précédent
    glClearColor(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(fenetre->getfov()), (float)fenetre->getSCR_WIDTH() / (float)fenetre->getSCR_HEIGHT(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(fenetre->getcameraPos(), fenetre->getcameraPos() + fenetre->getcameraFront(), fenetre->getcameraUp());
    
    
    glDepthMask(GL_FALSE);
    skyboxShader.use();
    skyboxShader.setMat4("projection", projection);
    skyboxShader.setMat4("view", glm::mat4(glm::mat3(view)));
    glBindVertexArray(VAOskybox);
    if (fenetre->getIsItNight())
        textureManager.BindSkyNightCubemap();
    else
        textureManager.BindSkyDayCubemap();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    
    //On assigne le VAO des cubes
    glBindVertexArray(VAOblock);
    
    //activation des shaders
    ourShader.use();

    //Transmission de la matrice de projection du monde aux shaders
    ourShader.setMat4("projection", projection);
    //Transmission de la matrice de vue de la caméra aux shaders
    ourShader.setMat4("view", view);

    lightManager->Update(ourShader, glfwGetTime(),fenetre);

    ourShader.setVec3("viewPos", fenetre->getcameraPos());

   
    //On dessine le monde
    this->DrawChunkManager(fenetre->getChunkManager());

    selectionShader.use();
    selectionShader.setMat4("projection", projection);
    selectionShader.setMat4("view", view);

    this->HighlightBlock(fenetre->getHighlightedBlock(), fenetre->getHighlightedBlockChunkPosition());

    glDisable(GL_DEPTH_TEST);
    //On dessine le viseur
    glBindVertexArray(VAOviseur);
    viseurShader.use();
    projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f);
    viseurShader.setMat4("projection", projection);
    this->DrawViseur((float)fenetre->getSCR_WIDTH() / (float)fenetre->getSCR_HEIGHT());

    
    //On dessine la hotbar
    glBindVertexArray(VAOhotbar);
    hotbarShader.use();
    projection = glm::ortho(0, 1, 0, 1);
    hotbarShader.setMat4("projection", projection);
    this->DrawHotbar();

    //On dessine la selection de la hotbar
    glBindVertexArray(VAOhotbarSelector);
    hotbarSelectionShader.use();
    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, glm::vec3(0.106f * (-4 + fenetre->getHotbarActiveSlot()), 0, 0));
    hotbarSelectionShader.setMat4("translation", translation);
    this->DrawHotbarSelection();

    //On dessine les blocks de la hotbar
    glBindVertexArray(VAOblock);
    hotbarBlockShader.use();
    projection = glm::perspective(glm::radians(45.0f), (float)fenetre->getSCR_WIDTH() / (float)fenetre->getSCR_HEIGHT(), 0.1f, 100.0f);
    hotbarBlockShader.setMat4("projection", projection);
    this->DrawHotbarBlocks(fenetre->getHotBar());

    //On swap les buffers glfw et on poll les events d'input output
    glfwSwapBuffers(fenetre->getWindow());
    glfwPollEvents();
}
