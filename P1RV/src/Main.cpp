#define STB_IMAGE_IMPLEMENTATION
#include "IncludeLibrairies.h"

#include "Graphic/GraphicManager.h"
#include "Game/Block/Block.h"
#include "Game/Block/SpecificBlocks/CraftingTable.h"
#include "Game/Block/SpecificBlocks/BirchWood.h"
#include "Game/Block/SpecificBlocks/GrassBlock.h"
#include "Game/Block/SpecificBlocks/GrassBlockSnow.h"

#include "Graphic/MaFenetre.h"


int main()
{
    // Creation de notre fenetre et initialisation de GLFW
    MaFenetre* maFenetre = new MaFenetre();
    
    // Chargement de GLAD: ca charge les OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Chargement du Graphic Manager
    GraphicManager graphicManager;
    graphicManager.Load(maFenetre);

    // On demande a GLFW de capturer notre souris
    glfwSetInputMode(maFenetre->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Boucle de rendu infinie
    while (!glfwWindowShouldClose(maFenetre->getWindow()))
    {
        // Calcul de l'ecart de temps entre la frame actuelle et la frame precedente
        float currentFrame = static_cast<float>(glfwGetTime());
        maFenetre->setDeltaTime(currentFrame - maFenetre->getLastFrame());
        maFenetre->setLastFrame(currentFrame);

        // Upadate du jeu
        maFenetre->upadateChunks();
        maFenetre->processHotbarSelection();
        maFenetre->processMovements();
        maFenetre->selectBlock();
        maFenetre->processClicks();

        // Render
        graphicManager.Draw(maFenetre);
    }

    
    //libere l'entierete des ressources GLFW allouees
    glfwTerminate();
    return 0;
}