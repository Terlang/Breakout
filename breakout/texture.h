#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D {
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels

    // constructor (sets default texture modes)
    Texture2D(int internal_format=GL_RGB, int image_format=GL_RGB, int wrap_s=GL_REPEAT, int wrap_t=GL_REPEAT, 
        int filter_min=GL_LINEAR, int filter_max=GL_LINEAR) :
        Width(0), Height(0), Internal_Format(internal_format), Image_Format(image_format), Wrap_S(wrap_s),
        Wrap_T(wrap_t), Filter_Min(filter_min), Filter_Max(filter_max)
    {
        glGenTextures(1, &this->ID);
    }

    // generates texture from image data
    int Generate(const char* path) {
        // create Texture
        glBindTexture(GL_TEXTURE_2D, this->ID);

        // set Texture wrap and filter modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
        if (!data) {
            std::cout << "Failed to load texture from " << path << std::endl;
            return 1;
        }
        this->Width = width;
        this->Height = height;
        glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);					// free data
        glBindTexture(GL_TEXTURE_2D, 0);		// unbind texture
        return 0;
    }

    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const {
        glBindTexture(GL_TEXTURE_2D, this->ID);
    }
};
#endif