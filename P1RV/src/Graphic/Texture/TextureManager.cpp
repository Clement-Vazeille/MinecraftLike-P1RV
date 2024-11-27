#include "TextureManager.h"

void TextureManager::LoadTexture(string fileName, Shader shader)
{
    unsigned int currentTex;
    // ---------
    glGenTextures(1, &currentTex);
    glBindTexture(GL_TEXTURE_2D, currentTex);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
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
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
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
