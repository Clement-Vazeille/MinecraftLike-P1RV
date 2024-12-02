#include "TextureManager.h"

void TextureManager::LoadTexture(string fileName, Shader shader)
{
    unsigned int currentTex;
    //On récupère l'id de la texture
    glGenTextures(1, &currentTex);
    glBindTexture(GL_TEXTURE_2D, currentTex);
    //Paramétrage du wrapper de textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Paramétrage du filtrage de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture : " << fileName.c_str() << std::endl;
        cout << "Error Reason : " << stbi_failure_reason() << endl;
    }
    stbi_image_free(data);
    
    //On enregistre l'ID de la texture dans nos shaders et on l'associe à la texture correspondante
    shader.use();
    shader.setInt(fileName, currentTex);

    texIDMap.insert(make_pair(fileName, currentTex));
}

void TextureManager::Load(Shader shader)
{
	LoadTexture("Assets/Block/crafting_Table_side.png",shader);
	LoadTexture("Assets/Block/crafting_Table_front.png",shader);
    LoadTexture("Assets/Block/crafting_Table_top.png", shader);
    LoadTexture("Assets/Block/birch_log.png", shader);
    LoadTexture("Assets/Block/birch_log_top.png", shader);
    LoadTexture("Assets/Block/grass_block_side.png", shader);
    LoadTexture("Assets/Block/grass_block_top.png", shader);
    LoadTexture("Assets/Block/dirt.png", shader);
    LoadTexture("Assets/Block/grass_block_snow_side.png", shader);
    LoadTexture("Assets/Block/grass_block_snow_top.png", shader);
}

void TextureManager::BindTexture(string fileName) const
{
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texIDMap.at(fileName));
}
