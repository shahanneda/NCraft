#ifndef NCRAFT_CAMERA
#define NCRAFT_CAMERA
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos);
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    float getYaw()
    {
        return yaw;
    };
    void setYaw(float yaw);

    float getPitch()
    {
        return pitch;
    };
    void setPitch(float pitch);

    void SetPosition(glm::vec3 pos);
    void TranslateCameraBy(glm::vec3 translation);
    glm::mat4 GetViewMatrix();

private:
    void CalculateRotation();
    float yaw = 0;
    float pitch = 0;
};
#endif