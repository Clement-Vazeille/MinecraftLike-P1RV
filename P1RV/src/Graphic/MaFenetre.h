#pragma once
#include "../IncludeLibrairies.h"
#include "../Game/Block/ChunkManager.h"
//Class qui contient la fen�tre de l'application ainsi que l'ensemble des variables d�crivants les �tats g�n�raux de l'application
//Elle contient aussi les fonctions de callback de l'application

//!!!! Il ne peux y avoir qu'un objet de type MaFenetre!!!!!!!
//On pourrait changer �a mais on n'y voit pas trop d'int�rets
class MaFenetre
{
private:
    GLFWwindow* mWindow;

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // camera
    glm::vec3 cameraPos = glm::vec3(8.0f, 2.0f, 8.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;	// yaw est initialis� � -90.0 degr�s car un yaw � 0.0 pointerait vers la gauche
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;

    // timing
    float deltaTime = 0.0f;	// temps �coul� entre la derni�re frame et la frame actuelle
    float lastFrame = 0.0f; //timestamp de la derni�re frame

    ChunkManager* chunkManager;

    //Fonctions de callback statics donn�es � OpenGL, leur r�le est d'appeler les fonctions de callback de la classe d�finies plus bas 
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    MaFenetre();
    ~MaFenetre();

    //Fonctions de callbacks
    void framebuffer_size_callback(int width, int height);
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);

    //Process des inputs
    void processInput();

    //Charge et g�n�re les chunks proches, puis d�charge les chunks �loign�s
    void upadateChunks();

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

};

