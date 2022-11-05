#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace Renderer{

class Camera {
    static constexpr glm::vec3 defaultCameraPos = {0.0f, 0.0f, 1.0f};
    static constexpr glm::vec3 defaultCameraUp = {0.0f, 1.0f, 0.0f};
    static constexpr glm::vec3 defaultCameraFront = {0.0f, 0.0f, -1.0f};

public:
    Camera(const glm::vec3 &cameraPos   =   defaultCameraPos,
           const glm::vec3 &cameraUp    =   defaultCameraUp,
           const glm::vec3 &cameraFront =   defaultCameraFront,
           float speed = 0.1f);
public:
    glm::mat4 LookAt() const;

    void MoveLeft();
    void MoveRight();
    void MoveForward();
    void MoveBackward();

    void Rotate(float x, float y);
private:
    glm::vec3   m_CameraPos;
    glm::vec3   m_CameraUp;
    glm::vec3   m_CameraFront;

    float m_Sens;
    float m_Speed;
    float m_Yaw;
    float m_Pitch;

    float m_PrevX;
    float m_PrevY;

    bool m_IsFirstMove;
};

};

#endif
