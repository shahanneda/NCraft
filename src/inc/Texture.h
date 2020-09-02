#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <utils/std_image.h>
#include <glad/glad.h>

class Texture{
    public:
        uint32_t id;
        Texture(std::string path);
        void BindTexture();
};