
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos);
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;

    void SetPosition(glm::vec3 pos);
    void TranslateCameraBy(glm::vec3 translation);
    glm::mat4 GetViewMatrix();
};