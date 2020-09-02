#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos)
{
    position = pos;

    target = glm::vec3(0.0f, 0.0f, -1.0f);
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
void Camera::setPitch(float pitch)
{
    this->pitch = pitch;
    CalculateRotation();
}
void Camera::setYaw(float yaw)
{
    this->yaw = yaw;
    CalculateRotation();
}

void Camera::CalculateRotation()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    target = glm::normalize(direction);
}

void Camera::TranslateCameraBy(glm::vec3 translation)
{
    this->position = glm::vec3(position.x + translation.x, position.y + translation.y, position.z + translation.z);
}
