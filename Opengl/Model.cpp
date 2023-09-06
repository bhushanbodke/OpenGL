#include "Model.h"

Model::Model(std::string path)
{
    LoadModel(path);
}

void Model::Draw(Shader& shader)
{
    for (unsigned int i = 0; i < Meshes.size(); i++)
    {
        Meshes[i].DrawMesh(shader);
    }
}

int Model::GetMeshNo()
{
    return Meshes.size();
}

void Model::LoadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals| aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // check if scene is null or rootnode is null  
    {
        std::cout << "ERROR[-] : error loading model" << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    //std::cout << "mesh array size" << Meshes.size()<<std::endl;
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        Meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    vertices.resize(mesh->mNumVertices);
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        
        vertices[i].Position.x = mesh->mVertices[i].x;
        vertices[i].Position.y= mesh->mVertices[i].y;
        vertices[i].Position.z= mesh->mVertices[i].z;

        vertices[i].Normal.x = mesh->mNormals[i].x;
        vertices[i].Normal.y = mesh->mNormals[i].y;
        vertices[i].Normal.z = mesh->mNormals[i].z;

        if (mesh->mTextureCoords[0])
        {
            vertices[i].TexCoord.x = mesh->mTextureCoords[0][i].x;
            vertices[i].TexCoord.y = mesh->mTextureCoords[0][i].y;
        }
        else
            vertices[i].TexCoord = { 0.0,0.0 };
    }

    NoTriangles += mesh->mNumFaces;
    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> DiffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

        std::vector<Texture> SpecularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), SpecularMaps.begin(), SpecularMaps.end());
    }

    return Mesh(vertices,indices,textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string TypeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;
        for (unsigned int j = 0; j < loaded_textures.size(); j++)
        {
            if (std::strcmp(loaded_textures[j].path.data(),str.C_Str())==0)
            {
                textures.push_back(loaded_textures[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = GetTextureID(str.C_Str(), directory);
            texture.type = TypeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            loaded_textures.push_back(texture);
        }
    }
    return textures;
}

unsigned int Model::GetTextureID(std::string path, std::string directory)
{

    std::string filename = directory + '/' + path;
    int width, height, nrComponents;
    unsigned int TextureID;

    glGenTextures(1, &TextureID);
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "ERROR[-] : Failed to load texture at -" << filename << std::endl;
    }

    return TextureID;
}
