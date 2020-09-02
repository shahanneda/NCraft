#ifndef NCRAFT_TEXTURE
#define NCRAFT_TEXTURE

#include <string>
#include <utils/std_image.h>
#include <glad/glad.h>

class Texture{
    public:
        uint32_t id;
        Texture(std::string path);
        void BindTexture();
};
#endif