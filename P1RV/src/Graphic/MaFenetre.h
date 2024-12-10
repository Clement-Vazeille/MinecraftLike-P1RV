#pragma once
#include "../IncludeLibrairies.h"
#include "../Game/Block/ChunkManager.h"
#include "../Game/BlockSelector.h"
//Class qui contient la fenÍtre de l'application ainsi que l'ensemble des variables dÈcrivants les Ètats gÈnÈraux de l'application
//Elle contient aussi les fonctions de callback de l'application

//!!!! Il ne peux y avoir qu'un objet de type MaFenetre!!!!!!!
//On pourrait changer Áa mais on n'y voit pas trop d'intÈrets
class MaFenetre
{
private:
    GLFWwindow* mWindow;

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // camera
    glm::vec3 cameraPos = glm::vec3(8.0f, 6.0f, 8.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;	// yaw est initialisÅEÅE-90.0 degrÈs car un yaw ÅE0.0 pointerait vers la gauche
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;

    // timing
    float deltaTime = 0.0f;	// temps ÈcoulÅEentre la derniËre frame et la frame actuelle
    float lastFrame = 0.0f; //timestamp de la derniËre frame

    ChunkManager* chunkManager;
    BlockSelector* blockSelector;

    bool movementModeVol = false; //true si on se dÈplace en volant false si on marche
    bool toucheLeSol = false;
    float yUpForce = 0;
    //on utilise la touche m pour changer le mode de dÈplacement

    Block* highlightedBlock = nullptr;
    Vector2I highlightedBlockChunkPosition;
    Vector3I highlightedFace;

    //Fonctions de callback statics donnÈes ÅEOpenGL, leur rÙle est d'appeler les fonctions de callback de la classe dÈfinies plus bas 
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    MaFenetre();
    ~MaFenetre();

    //Fonctions de callbacks
    void framebuffer_size_callback(int width, int height);
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void key_callback(int key, int scancode, int action, int mods);

    //Process des inputs de mouvement
    void processMovements();

    //Process des inputs de la souris
    void processClicks();

    //Charge et gÈnËre les chunks proches, puis dÈcharge les chunks ÈloignÈs
    void upadateChunks();

    //SÈlectionne le block pointÈ par le joueur
    void selectBlock();

    //setters
    void setDeltaTime(float delta);
    void setLastFrame(float lf);
    
    //getters
    GLFWwindow* getWindow(void) const;
    float getLastFrame(void) const;
    glm::vec3 getcameraPos(void) const;
    glm::vec3 getcameraFront(void) const;
    glm::vec3 getcameraUp(void) const;
    float getfov(void) const;
    unsigned int getSCR_WIDTH(void) const;
    unsigned int getSCR_HEIGHT(void) const;
    ChunkManager* getChunkManager(void);
    Block* getHighlightedBlock(void) const;
    Vector2I getHighlightedBlockChunkPosition(void) const;
};

