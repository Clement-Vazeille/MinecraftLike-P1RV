#include "Include.h"

#include "Graphic/GraphicManager.h"
#include "Game/Block/Block.h"
#include "Game/Block/SpecificBlocks/CraftingTable.h"
#include "Game/Block/SpecificBlocks/BirchWood.h"
#include "Game/Block/SpecificBlocks/GrassBlock.h"
#include "Game/Block/SpecificBlocks/GrassBlockSnow.h"

#include "Graphic/MaFenetre.h"

#define STB_IMAGE_IMPLEMENTATION

int main()
{
    glfwInit();
    // glfw: initialize and configure
    // ------------------------------

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    MaFenetre* maFenetre = new MaFenetre();
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    GraphicManager graphicManager;
    graphicManager.Load(maFenetre);

    // tell GLFW to capture our mouse
    glfwSetInputMode(maFenetre->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    
    BirchWood arbre1(0, 1, 0);
    BirchWood arbre2(0, 2, 0);
    BirchWood arbre3(0, 3, 0);
    BirchWood arbre4(0, 4, 0);

    CraftingTable table(3, 1, 0);
 
    ChunkManager chunkManager;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(maFenetre->getWindow()))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        maFenetre->setDeltaTime(currentFrame - maFenetre->getLastFrame());
        maFenetre->setLastFrame(currentFrame);

        // Upadate du monde
        chunkManager.LoadChunks(maFenetre->getcameraPos());
        // input
        // -----
        maFenetre->processInput();

        //render
        graphicManager.Draw(maFenetre,chunkManager);
    }

    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}