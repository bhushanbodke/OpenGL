#include "texture.h"

Texture::Texture(const std::string filepath)
    :m_filepath(filepath), m_height(0),m_width(0),textureData(nullptr)
{
    stbi_set_flip_vertically_on_load(1);
    textureData = stbi_load(filepath.c_str(),&m_width, &m_height,&m_BPP , 4);

    
    GLCALL(glGenTextures(1 , &m_TextureID));
    GLCALL(glBindTexture(GL_TEXTURE_2D , m_TextureID));


    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER , GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER , GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));   
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,textureData));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

    if(textureData)
    {
        stbi_image_free(textureData);
    };
}

void Texture::bind(unsigned int slot)
{
    GLCALL(glActiveTexture(GL_TEXTURE0 +slot));
    GLCALL(glBindTexture(GL_TEXTURE_2D,m_TextureID));
}

void Texture::unbind()
{
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::Delete()
{
    GLCALL(glDeleteTextures(1, &m_TextureID));
}
