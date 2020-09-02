#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos)
{
    position = pos;

    target = glm::vec3(0.0f, 0.0f, 0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + target, up);
}

void Camera::SetPosition(glm::vec3 pos)
{
    this->position = pos;
}

void Camera::TranslateCameraBy(glm::vec3 translation)
{
    this->position = glm::vec3(position.x + translation.x, position.y + translation.y, position.z + translation.z);
}
