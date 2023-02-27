#pragma once
#include<string>
#include "glad.h"
#include "errorhandle.h"
#include "stb_Image.h"
class Texture
{
    private:
        unsigned int  m_TextureID;
        std::string m_filepath;

        unsigned char* textureData;

        int m_width , m_height , m_BPP;

    public:
        Texture(const std::string filepath);

        void bind(unsigned int slot = 0 );
        void unbind();
        void Delete();

        inline int getWidth() {return m_width;};
        inline int getHeight() {return m_height;};
};