#include "IncludeLibrairies.h"

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
    // Création de notre fenêtre et initialisation de GLFW
    MaFenetre* maFenetre = new MaFenetre();
    
    // Chargement de GLAD: ça charge les OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Chargement du Graphic Manager
    GraphicManager graphicManager;
    graphicManager.Load(maFenetre);

    // On demande à GLFW de capturer notre souris
    glfwSetInputMode(maFenetre->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Boucle de rendu infinie
    while (!glfwWindowShouldClose(maFenetre->getWindow()))
    {
        // Calcul de l'écart de temps entre la frame actuelle et la frame précédente
        float currentFrame = static_cast<float>(glfwGetTime());
        maFenetre->setDeltaTime(currentFrame - maFenetre->getLastFrame());
        maFenetre->setLastFrame(currentFrame);

        // Upadate du jeu
        maFenetre->upadateChunks();
        maFenetre->processMovements();
        maFenetre->selectBlock();
        maFenetre->processClicks();

        // Render
        graphicManager.Draw(maFenetre);
    }

    
    //libère l'entièreté des ressources GLFW allouées
    glfwTerminate();
    return 0;
}