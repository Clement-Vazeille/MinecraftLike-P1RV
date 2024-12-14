#include "GraphicManager.h"

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

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

        glLineWidth(1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GraphicManager::DrawViseur()
{
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, nullptr);
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

GraphicManager::GraphicManager() : ourShader("src/Graphic/Shader/shader.vs", "src/Graphic/Shader/shader.fs"),
    selectionShader("src/Graphic/Shader/shaderSelection.vs","src/Graphic/Shader/shaderSelection.fs"),
    viseurShader("src/Graphic/Shader/shaderViseur.vs", "src/Graphic/Shader/shaderViseur.fs"),
    hotbarShader("src/Graphic/Shader/shaderHotbar.vs", "src/Graphic/Shader/shaderHotbar.fs"),
    hotbarSelectionShader("src/Graphic/Shader/shaderHotbarSelection.vs", "src/Graphic/Shader/shaderHotbarSelection.fs"),
    hotbarBlockShader("src/Graphic/Shader/shaderHotbarBlock.vs", "src/Graphic/Shader/shaderHotbarBlock.fs"),
    VAOblock(0),VBOblock(0),EBOblock(0),VAOviseur(0),VBOviseur(0),EBOviseur(0),
    VAOhotbar(0), VBOhotbar(0), EBOhotbar(0), VAOhotbarSelector(0), VBOhotbarSelector(0), EBOhotbarSelector(0)
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
    glDeleteBuffers(1, &VAOhotbarSelector);
    glDeleteBuffers(1, &VAOhotbarSelector);
}

void GraphicManager::Load(MaFenetre* fenetre)
{
    
    // configuration globale des états d'openGL
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // initialisation des sommets d'un cube
    // ------------------------------------------------------------------
    float verticesCube[] = { //position vis à vis du spawn
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, //face arriere
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, //face avant
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //face gauche
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, //face droite
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //face dessous
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //face dessus
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    textureManager.Load(ourShader);
    
    // initialisation des sommets du viseur
    // ------------------------------------------------------------------
    float verticesViseur[] = { //position vis à vis du spawn
        //Format : 
        //-,-
        //+,-
        //+,+
        //-,+

         -0.115f, -0.01f,   //rectangle gauche
         -0.04f, -0.01f,
         -0.04f, 0.01f,
         -0.115f,  0.01f,

         -0.008f, -0.14f,   //rectangle bas
         0.008f, -0.14f,
         0.008f, -0.05f,
         -0.008f, -0.05f,

         0.04f, -0.01f, //rectangle droit
         0.115f,  -0.01f,
         0.115f,  0.01f,
         0.04f, 0.01f,

         -0.008f, 0.05f, //rectangle haut
         0.008f,  0.05f,
         0.008f,  0.14f,
         -0.008f,  0.14f
    };
    
    unsigned int indicesViseur[] = {
    0, 1, 2, // bottom triangle
    2, 3, 0,  // top triangle

    4, 5, 6, // bottom triangle
    6, 7, 4,  // top triangle

    8, 9, 10, // bottom triangle
    10, 11, 8,  // top triangle

    12, 13, 14, // bottom triangle
    14, 15, 12  // top triangle
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

         -0.55f, -1.0f, 0.0f, 0.0f,    
         0.55f, -1.0f, 1.0f, 0.0f,
         0.55f, -0.84f, 1.0f, 1.0f, 
         -0.55f,  -0.84f, 0.0f, 1.0f
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

        -0.105f, -0.99f,
         0.0f, -0.99f,
         0.0f, -0.85f,
         -0.105f,  -0.85f
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

    glEnable(GL_CULL_FACE);
}

void GraphicManager::Draw(MaFenetre* fenetre)
{
    //clear du rendu précédent
    glClearColor(135.f / 255.f, 206.f / 255.f, 235.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(fenetre->getfov()), (float)fenetre->getSCR_WIDTH() / (float)fenetre->getSCR_HEIGHT(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(fenetre->getcameraPos(), fenetre->getcameraPos() + fenetre->getcameraFront(), fenetre->getcameraUp());
    //On assigne le VAO des cubes
    glBindVertexArray(VAOblock);
    
    //activation des shaders
    ourShader.use();

    //Transmission de la matrice de projection du monde aux shaders
    ourShader.setMat4("projection", projection);
    //Transmission de la matrice de vue de la caméra aux shaders
    ourShader.setMat4("view", view);

   
    //On dessine le monde
    this->DrawChunkManager(fenetre->getChunkManager());

    selectionShader.use();
    selectionShader.setMat4("projection", projection);
    selectionShader.setMat4("view", view);

    this->HighlightBlock(fenetre->getHighlightedBlock(), fenetre->getHighlightedBlockChunkPosition());

    
    //On dessine le viseur
    glBindVertexArray(VAOviseur);
    viseurShader.use();
    this->DrawViseur();

    //On dessine la selection de la hotbar
    glBindVertexArray(VAOhotbarSelector);
    hotbarSelectionShader.use();
    this->DrawHotbarSelection();

    //On dessine la hotbar
    glBindVertexArray(VAOhotbar);
    hotbarShader.use();
    this->DrawHotbar();


    //On swap les buffers glfw et on poll les events d'input output
    glfwSwapBuffers(fenetre->getWindow());
    glfwPollEvents();
}
