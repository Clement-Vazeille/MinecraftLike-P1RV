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

MaFenetre::MaFenetre()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MineCraft-Like", NULL, NULL);
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
}

MaFenetre::~MaFenetre()
{
    glfwDestroyWindow(mWindow);
}

void MaFenetre::framebuffer_size_callback(int width, int height)
{
    //On s'assure que le viewport corresponde aux dimensions de la fenêtre
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
    float yoffset = lastY - ypos; // inversé car les coordonnées y vont de bas en haut
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // sensibilité du déplacement
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // on s'assure que le pitch ne dépasse pas la limite possible
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
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void MaFenetre::processInput()
{
    //traitement sortie de l'application
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);

    //Traitement sprint ou marche
    float cameraSpeed = static_cast<float>(10 * deltaTime);
    if ((glfwGetKey(mWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS))
        cameraSpeed *= 2.5;

    //Traitement déplacements
    if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(mWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)) * cameraSpeed;
    if (glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f)) * cameraSpeed;
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
    return SCR_WIDTH;
}

unsigned int MaFenetre::getSCR_HEIGHT(void) const
{
    return SCR_HEIGHT;
}
