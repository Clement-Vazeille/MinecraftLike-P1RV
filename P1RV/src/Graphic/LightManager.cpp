#include "LightManager.h"

void LightManager::AddPointLight(glm::vec3& position,int id, glm::vec3& color ,Shader& shader)
{
    

    glm::vec3 diffuseColor = color * glm::vec3(0.8f);
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

    shader.setVec3("pointLights[" + std::to_string(id) + "].ambient", ambientColor);
    shader.setVec3("pointLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    shader.setVec3("pointLights[" + std::to_string(id) + "].specular", 0.4f, 0.4f, 0.4f);

    //valeurs changeant l'attenuation de la lumière
    //augmenter les termes lineaires et quadratiques pour réduire la puissance
    shader.setFloat("pointLights[" + std::to_string(id) + "].constant", 1.0f);
    shader.setFloat("pointLights[" + std::to_string(id) + "].linear", 0.045f);
    shader.setFloat("pointLights[" + std::to_string(id) + "].quadratic", 0.0075f);

    shader.setVec3("pointLights[" + std::to_string(id) + "].position", position);
}

LightManager::LightManager()
{
}

void LightManager::Update(Shader& shader,float time, MaFenetre* fenetre)
{
    //paramétrage lumière directionnelle
    if (fenetre->getIsItNight())
    {
        shader.setVec3("dirlight.direction", -0.2f, -1.0f, -0.3f);

        shader.setVec3("dirlight.ambient", 0.18f, 0.18f, 0.18f);
        shader.setVec3("dirlight.diffuse", 0.05f, 0.05f, 0.05f);
        shader.setVec3("dirlight.specular", 0.03f, 0.03f, 0.03f);
    }
    else
    {
        shader.setVec3("dirlight.direction", -0.2f, -1.0f, -0.3f);

        shader.setVec3("dirlight.ambient", 0.2f, 0.2f, 0.2f);
        shader.setVec3("dirlight.diffuse", 0.8f, 0.8f, 0.8f);
        shader.setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);
    }

    //paramétrage lumières ponctuelles
    int nb = 2;
    shader.setInt("nbrPointLights",nb);

    glm::vec3 pointLightsColor;
    pointLightsColor.x = sin(time * 2.0f);
    pointLightsColor.y = sin(time * 0.7f);
    pointLightsColor.z = sin(time * 1.3f);

    for (int i = 0; i < nb; i++)
    {
        glm::vec3 position(8.0f + 16.f * i, 8.0f, 8.0f+16.f*i);
        this->AddPointLight(position, i, pointLightsColor, shader);
    }
}
