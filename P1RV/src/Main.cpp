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
    // Cr�ation de notre fen�tre et initialisation de GLFW
    MaFenetre* maFenetre = new MaFenetre();
    
    // Chargement de GLAD: �a charge les OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // Chargement du Graphic Manager
    GraphicManager graphicManager;
    graphicManager.Load(maFenetre);

    // On demande � GLFW de capturer notre souris
    glfwSetInputMode(maFenetre->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Boucle de rendu infinie
    while (!glfwWindowShouldClose(maFenetre->getWindow()))
    {
        // Calcul de l'�cart de temps entre la frame actuelle et la frame pr�c�dente
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

    
    //lib�re l'enti�ret� des ressources GLFW allou�es
    glfwTerminate();
    return 0;
}