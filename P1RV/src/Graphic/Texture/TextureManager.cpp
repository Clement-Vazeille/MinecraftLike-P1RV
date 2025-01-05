#include "TextureManager.h"

void TextureManager::LoadTexture(string fileName, Shader& shader)
{
    unsigned int currentTex;
    //On recupere l'id de la texture
    glGenTextures(1, &currentTex);
    glBindTexture(GL_TEXTURE_2D, currentTex);
    //Parametrage du wrapper de textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Parametrage du filtrage de la texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture : " << fileName.c_str() << std::endl;
        cout << "Error Reason : " << stbi_failure_reason() << endl;
    }
    stbi_image_free(data);
    
    //On enregistre l'ID de la texture dans nos shaders et on l'associe a la texture correspondante
    shader.use();
    shader.setInt(fileName, currentTex);

    texIDMap.insert(make_pair(fileName, currentTex));
}

void TextureManager::LoadCubemaps()
{
    /*vector<std::string> faces
    {
        "Assets/skybox/right.jpg",
        "Assets/skybox/left.jpg",
        "Assets/skybox/top.jpg",
        "Assets/skybox/bottom.jpg",
        "Assets/skybox/day/front.png", //le soleil doit être sur front en haut à droite
        "Assets/skybox/back.jpg"
    };*/
    vector<std::string> facesday
    {
        "Assets/skybox/day/right.png",
        "Assets/skybox/day/left.png",
        "Assets/skybox/day/top.png",
        "Assets/skybox/day/bottom.png",
        "Assets/skybox/day/front.png", //le soleil doit être sur front en haut à droite
        "Assets/skybox/day/back.png"
    };
    glGenTextures(1, &skyDayCubemapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyDayCubemapID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < facesday.size(); i++)
    {
        unsigned char* data = stbi_load(facesday[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << facesday[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    vector<std::string> facesnight
    {
        "Assets/skybox/night/right.png",
        "Assets/skybox/night/left.png",
        "Assets/skybox/night/top.png",
        "Assets/skybox/night/bottom.png",
        "Assets/skybox/night/front.png", 
        "Assets/skybox/night/back.png"
    };
    glGenTextures(1, &skyNightCubemapID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyNightCubemapID);

    for (unsigned int i = 0; i < facesnight.size(); i++)
    {
        unsigned char* data = stbi_load(facesnight[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << facesnight[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


void TextureManager::Load(Shader shader)
{
	LoadTexture("Assets/Block/crafting_Table_side.png",shader);
	LoadTexture("Assets/Block/crafting_Table_front.png",shader);
    LoadTexture("Assets/Block/crafting_Table_top.png", shader);
    LoadTexture("Assets/Block/crafting_Table_bottom.png", shader);
    LoadTexture("Assets/Block/birch_log.png", shader);
    LoadTexture("Assets/Block/birch_log_top.png", shader);
    LoadTexture("Assets/Block/grass_block_side.png", shader);
    LoadTexture("Assets/Block/grass_block_top.png", shader);
    LoadTexture("Assets/Block/dirt.png", shader);
    LoadTexture("Assets/Block/oak_Side.png", shader);
    LoadTexture("Assets/Block/oak_Top.png", shader);
    LoadTexture("Assets/Block/stone.png", shader);
    LoadTexture("Assets/Block/water.png", shader);
    LoadTexture("Assets/Block/leaves.png", shader);
    LoadTexture("Assets/Block/oak_Plank.png", shader);
    LoadTexture("Assets/Block/grass_block_snow_side.png", shader);
    LoadTexture("Assets/Block/grass_block_snow_top.png", shader);
    LoadTexture("Assets/Block/purple_light.png", shader);
    LoadTexture("Assets/Block/red_light.png", shader);
    LoadTexture("Assets/HUD/hotbar.png", shader);
    
    this->LoadCubemaps();
}

void TextureManager::BindTexture(string fileName) const
{
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texIDMap.at(fileName));
}

void TextureManager::BindSkyNightCubemap() const
{
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyNightCubemapID);
}

void TextureManager::BindSkyDayCubemap() const
{
    glActiveTexture(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyDayCubemapID);
}
