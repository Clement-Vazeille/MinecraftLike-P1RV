#include "MaFenetre.h"

void MaFenetre::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    MaFenetre* obj = static_cast<MaFenetre*>(glfwGetWindowUserPointer(window));
    obj->framebuffer_size_callback(width, height);
}

void MaFenetre::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    MaFenetre* obj = static_cast<MaFenetre*>(glfwGetWindowUserPointer(window));
    obj->mouse_callback(xpos,ypos);
}

void MaFenetre::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    MaFenetre* obj = static_cast<MaFenetre*>(glfwGetWindowUserPointer(window));
    obj->scroll_callback(xoffset,yoffset);
}

void MaFenetre::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    MaFenetre* obj = static_cast<MaFenetre*>(glfwGetWindowUserPointer(window));
    obj->key_callback(key,scancode,action,mods);
}

MaFenetre::MaFenetre()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    mWindow = glfwCreateWindow(scrWidth, scrHeight, "MineCraft-Like", NULL, NULL);
    glfwSetWindowUserPointer(mWindow, this);

    if (mWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(mWindow);

    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);
    glfwSetKeyCallback(mWindow, key_callback);

    chunkManager = new ChunkManager();
    blockSelector = new BlockSelector();
    hotbar = new HotBar;
    hotbar->initialise();
}

MaFenetre::~MaFenetre()
{
    //delete chunkManager;
    glfwDestroyWindow(mWindow);
}

void MaFenetre::framebuffer_size_callback(int width, int height)
{
    //On s'assure que le viewport corresponde aux dimensions de la fenetre
    scrWidth = width;
    scrHeight = height;
    glViewport(0, 0, width, height);
}

void MaFenetre::mouse_callback(double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // inverse car les coordonnees y vont de bas en haut
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // sensibilite du deplacement
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // on s'assure que le pitch ne depasse pas la limite possible
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void MaFenetre::scroll_callback(double xoffset, double yoffset)
{
    float scrollSensitivity = 1.0f;
    hotbarActiveSlot += (float)yoffset * scrollSensitivity;
    if (hotbarActiveSlot < 0.0f)
        hotbarActiveSlot = 0.0f;
    if (hotbarActiveSlot > 9.9f)
        hotbarActiveSlot = 9.9f;
    /*
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
        */
}

void MaFenetre::key_callback(int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SEMICOLON && action == GLFW_PRESS)
    {
        movementModeVol = !movementModeVol;
        yUpForce = 0.f;
    }

    //traitement sortie de l'application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
}

void MaFenetre::processMovements()
{

    //Traitement sprint ou marche
    float cameraSpeed = static_cast<float>(10 * deltaTime);
    if ((glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
        cameraSpeed *= 2.5;


    //Traitement deplacements
    glm::vec3 movement = glm::vec3(0,0,0);
    if (movementModeVol) //deplacement en mode vol
    {
        if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
            movement += cameraSpeed * cameraFront;
        if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
            movement -= cameraSpeed * cameraFront;
        if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
            movement -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
            movement += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
            movement += glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            movement += glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)) * cameraSpeed;

        cameraPos += movement;
    }
    
    if (!movementModeVol)
    {
        //deplacement en mode au sol
        glm::vec3 frontMove = glm::vec3(cameraFront.x, 0.f, cameraFront.z);
        glm::vec3 rightMove = glm::vec3(glm::cross(cameraFront, cameraUp).x, 0.f, glm::cross(cameraFront, cameraUp).z);
        if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
            movement += glm::normalize(frontMove) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
            movement -= glm::normalize(frontMove) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
            movement -= glm::normalize(rightMove) * cameraSpeed;
        if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
            movement += glm::normalize(rightMove) * cameraSpeed;

        //saut
        if (glfwGetKey(mWindow, GLFW_KEY_SPACE) == GLFW_PRESS && toucheLeSol)
            yUpForce = 1.6f;

        if(toucheLeSol==false)
            movement.y = (-1.f + yUpForce) * static_cast<float>(10 * deltaTime);
        yUpForce = max(yUpForce - 1.f*deltaTime,0.f);

        //Gestion des collisions au sol
        glm::vec3 movX = glm::vec3(movement.x, 0, 0);
        glm::vec3 movY = glm::vec3(0, movement.y, 0);
        glm::vec3 movZ = glm::vec3(0, 0, movement.z);
        
        if (chunkManager->isPositionAllowed(cameraPos + movX))
            cameraPos += movX;
            
        toucheLeSol = true;
        if (chunkManager->isPositionAllowed(cameraPos + movY))
        {
            cameraPos += movY;
            toucheLeSol = false;
        }
        
        if (chunkManager->isPositionAllowed(cameraPos + movZ))
            cameraPos += movZ;
            
    }
    
}

void MaFenetre::processOtherInputs()
{
    if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        fov = 10.f;
    else 
        fov = 45.f;
}

void MaFenetre::processClicks()
{
    blockInteractionTimer += deltaTime;
    
    if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && highlightedBlock!=nullptr &&
        blockInteractionTimer >= blockInteractionCooldown)
    {
        blockInteractionTimer = 0.f;
        chunkManager->AddBlock(highlightedBlockChunkPosition, highlightedBlock->getPosition() + highlightedFace, cameraPos, hotbarActiveSlot);
    }
    if (glfwGetMouseButton(mWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && highlightedBlock != nullptr &&
        blockInteractionTimer >= blockInteractionCooldown)
    {
        blockInteractionTimer = 0.f;
        chunkManager->DestroyBlock(highlightedBlockChunkPosition, highlightedBlock->getPosition());
        this->selectBlock(); //On selectionne un nouveau block pour toujours avoir un block affiche comme selectionne en pratique on pourra rien faire sur ce block lors de cette frame
        //Permet aussi de faire que le pointeur vers le block selectionne ne pointe plus sur le block supprime
    }
}

void MaFenetre::processHotbarSelection()
{
    if (glfwGetKey(mWindow, GLFW_KEY_1) == GLFW_PRESS)
        hotbarActiveSlot=0.f;
    if (glfwGetKey(mWindow, GLFW_KEY_2) == GLFW_PRESS)
        hotbarActiveSlot = 1.f;
    if (glfwGetKey(mWindow, GLFW_KEY_3) == GLFW_PRESS)
        hotbarActiveSlot = 2.f;
    if (glfwGetKey(mWindow, GLFW_KEY_4) == GLFW_PRESS)
        hotbarActiveSlot = 3.f;
    if (glfwGetKey(mWindow, GLFW_KEY_5) == GLFW_PRESS)
        hotbarActiveSlot = 4.f;
    if (glfwGetKey(mWindow, GLFW_KEY_6) == GLFW_PRESS)
        hotbarActiveSlot = 5.f;
    if (glfwGetKey(mWindow, GLFW_KEY_7) == GLFW_PRESS)
        hotbarActiveSlot = 6.f;
    if (glfwGetKey(mWindow, GLFW_KEY_8) == GLFW_PRESS)
        hotbarActiveSlot = 7.f;
    if (glfwGetKey(mWindow, GLFW_KEY_9) == GLFW_PRESS)
        hotbarActiveSlot = 8.f;
    if (glfwGetKey(mWindow, GLFW_KEY_0) == GLFW_PRESS)
        hotbarActiveSlot = 9.f;
}

void MaFenetre::upadateChunks()
{
    chunkManager->LoadChunks(cameraPos);
    chunkManager->UnloadChunks(cameraPos);
}

void MaFenetre::selectBlock()
{
    blockSelector->SelectBlock(&highlightedBlock, &highlightedBlockChunkPosition, &highlightedFace, chunkManager, cameraPos , cameraFront);
}

void MaFenetre::setDeltaTime(float delta)
{
    deltaTime = delta;
}

void MaFenetre::setLastFrame(float lf)
{
    lastFrame = lf;
}

GLFWwindow* MaFenetre::getWindow(void) const
{
    return mWindow;
}

float MaFenetre::getLastFrame(void) const
{
    return lastFrame;
}

glm::vec3 MaFenetre::getcameraPos(void) const
{
    return cameraPos;
}

glm::vec3 MaFenetre::getcameraFront(void) const
{
    return cameraFront;
}

glm::vec3 MaFenetre::getcameraUp(void) const
{
    return cameraUp;
}

float MaFenetre::getfov(void) const
{
    return fov;
}

unsigned int MaFenetre::getSCR_WIDTH(void) const
{
    return scrWidth;
}

unsigned int MaFenetre::getSCR_HEIGHT(void) const
{
    return scrHeight;
}

ChunkManager* MaFenetre::getChunkManager(void)
{
    return chunkManager;
}

Block* MaFenetre::getHighlightedBlock(void) const
{
    return highlightedBlock;
}

Vector2I MaFenetre::getHighlightedBlockChunkPosition(void) const
{
    return highlightedBlockChunkPosition;
}

int MaFenetre::getHotbarActiveSlot(void) const
{
    return static_cast<int>(hotbarActiveSlot);
}

HotBar* MaFenetre::getHotBar(void) const
{
    return hotbar;
}
