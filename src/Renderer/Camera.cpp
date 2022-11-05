#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include "Camera.h"


namespace Renderer {

Camera::Camera(const glm::vec3 &cameraPos, const glm::vec3 &cameraUp,
               const glm::vec3 &cameraFront, float speed) :
    m_CameraPos(cameraPos), m_CameraUp(cameraUp), m_CameraFront(cameraFront),
    m_Sens(0.07f), m_Speed(speed), m_Yaw(-90.0f), m_Pitch(0.0), m_IsFirstMove(true) {}

glm::mat4 Camera::LookAt() const
{
    return glm::lookAt(m_CameraPos, m_CameraPos + m_CameraFront, m_CameraUp);
}

void Camera::MoveLeft()
{
    m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_Speed;
}

void Camera::MoveRight()
{
    m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * m_Speed;
}

void Camera::MoveForward()
{
    m_CameraPos += m_CameraFront * m_Speed;
}

void Camera::MoveBackward()
{
    m_CameraPos -= m_CameraFront * m_Speed;
}

void Camera::Rotate(float x, float y)
{

    if (m_IsFirstMove) {
        m_PrevX = x;
        m_PrevY = y;

        m_IsFirstMove = false;
    }

    float xOffset = x - m_PrevX;
    float yOffset = m_PrevY - y;

    m_PrevX = x;
    m_PrevY = y;

    m_Yaw += xOffset * m_Sens;
    m_Pitch += yOffset * m_Sens;


    // validate pitch
    m_Pitch = (m_Pitch > 89.0f)? 89.0f : (m_Pitch < -89.0f)? -89.0f : m_Pitch;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    direction.y = sin(glm::radians(m_Pitch));
    direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_CameraFront = glm::normalize(direction);
}


} //namespace
