#include "LightManager.h"

void LightManager::AddPointLight(glm::vec3& position,int id,const glm::vec3& color ,Shader& shader)
{
    

    glm::vec3 diffuseColor = color * glm::vec3(0.8f);
    glm::vec3 ambientColor = color * glm::vec3(0.13f);
    glm::vec3 specularColor = color * glm::vec3(0.4);

    shader.setVec3("pointLights[" + std::to_string(id) + "].ambient", ambientColor);
    shader.setVec3("pointLights[" + std::to_string(id) + "].diffuse", diffuseColor);
    shader.setVec3("pointLights[" + std::to_string(id) + "].specular", specularColor);

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
        shader.setVec3("dirlight.direction", -0.5f, -1.0f, -0.7f);

        shader.setVec3("dirlight.ambient", 0.3f, 0.3f, 0.3f);
        shader.setVec3("dirlight.diffuse", 0.95f, 0.95f, 0.95f);
        shader.setVec3("dirlight.specular", 0.5f, 0.5f, 0.5f);
    }

    //paramétrage lumières ponctuelles
    int maxLightsNumber = 100;
    const unordered_set<LightData*>* lights = fenetre->getLights();
    int lightsNumber = min(maxLightsNumber, static_cast<int>(lights->size()));
    shader.setInt("nbrPointLights",lightsNumber);
    int i = 0;
    for (const auto& light : *lights)
    {
        if (i < maxLightsNumber)
        {
            glm::vec3 position(light->sourcePosition.getX() + 16.f * light->chunkPosition.getX() + 0.5f,
                light->sourcePosition.getY() + 0.5f,
                light->sourcePosition.getZ() + 16.f * light->chunkPosition.getZ()+ 0.5f);
            this->AddPointLight(position, i++, light->lightColor, shader);
        }
        Vector2I chunkPosition;
        Vector3I sourcePosition; 
    }
}
