#include "LightManager.h"

LightManager::LightManager()
{
}

void LightManager::Update(Shader& shader,float time)
{
    //paramétrage lumière directionnelle
    shader.setVec3("dirlight.direction", -0.2f, -1.0f, -0.3f);

    shader.setVec3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
    shader.setVec3("dirlight.diffuse", 0.8f, 0.8f, 0.8f);
    shader.setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);

    //paramétrage lumière ponctuelle
    glm::vec3 pointLightsColor;
    pointLightsColor.x = sin(time * 2.0f);
    pointLightsColor.y = sin(time * 0.7f);
    pointLightsColor.z = sin(time * 1.3f);

    glm::vec3 diffuseColor = pointLightsColor * glm::vec3(0.8f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    shader.setVec3("pointLights[0].ambient", ambientColor);
    shader.setVec3("pointLights[0].diffuse", diffuseColor);
    shader.setVec3("pointLights[0].specular", 0.5f, 0.5f, 0.5f);

    //valeurs changeant l'attenuation de la lumière
    //augmenter les termes lineaires et quadratiques pour réduire la puissance
    shader.setFloat("pointLights[0].constant", 1.0f);
    shader.setFloat("pointLights[0].linear", 0.045f);
    shader.setFloat("pointLights[0].quadratic", 0.0075f);

    glm::vec3 lightPos(8.0f, 8.0f, 8.0f);
    shader.setVec3("pointLights[0].position", lightPos);

    //lumiere 2
    shader.setVec3("pointLights[1].ambient", ambientColor);
    shader.setVec3("pointLights[1].diffuse", diffuseColor);
    shader.setVec3("pointLights[1].specular", 0.5f, 0.5f, 0.5f);

    //valeurs changeant l'attenuation de la lumière
    //augmenter les termes lineaires et quadratiques pour réduire la puissance
    shader.setFloat("pointLights[1].constant", 1.0f);
    shader.setFloat("pointLights[1].linear", 0.045f);
    shader.setFloat("pointLights[1].quadratic", 0.0075f);

    glm::vec3 lightPos2(20.0f, 8.0f, 20.0f);
    shader.setVec3("pointLights[1].position", lightPos2);
}
