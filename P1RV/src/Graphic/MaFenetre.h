#pragma once
#include "../Include.h"
class MaFenetre
{
private:
    GLFWwindow* mWindow;

    // settings
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    // camera
    glm::vec3 cameraPos = glm::vec3(8.0f, 2.0f, 8.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float fov = 45.0f;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    MaFenetre();

    ~MaFenetre();

    void framebuffer_size_callback(int width, int height);
    void mouse_callback(double xpos, double ypos);
    void scroll_callback(double xoffset, double yoffset);
    void processInput();

    void setDeltaTime(float delta);
    void setLastFrame(float lf);
    
    GLFWwindow* getWindow(void) const;
    float getLastFrame(void) const;
    glm::vec3 getcameraPos(void) const;
    glm::vec3 getcameraFront(void) const;
    glm::vec3 getcameraUp(void) const;
    float getfov(void) const;
    unsigned int getSCR_WIDTH(void) const;
    unsigned int getSCR_HEIGHT(void) const;

};

