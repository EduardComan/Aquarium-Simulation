#pragma once
#include <GL/glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{
private:
    // Perspective properties
    float m_z_near, m_z_far, m_FOV;
    int m_width, m_height;

    // Euler angles
    float m_yaw, m_pitch;

    // Input factors
    float m_camera_speed_factor, m_mouse_sensitivity;

    // Camera spatial properties
    glm::vec3 m_position,
        m_camera_front,
        m_camera_right,
        m_camera_up;

    // world vector, hard coded to be (0, 1, 0)
    static const glm::vec3 world_up;

public:
    // Constructor
    Camera(const int width, const int height, const glm::vec3& position);

    // Getters
    const glm::mat4 GetViewMatrix() const;
    const glm::mat4 GetProjectionMatrix() const;
    const glm::vec3 GetPosition() const;
    float GetPitch() const;
    float GetNear() const;
    float GetFar() const;

    // Setters
    void SetPitch(float new_pitch);
    void SetPosition(const glm::vec3& position);

    // Input processing
    void ProcessInput(GLFWwindow* window, float delta_time);
private:
    void KeyboardControl(GLFWwindow* window, float delta_time);
    void MouseControl(GLFWwindow* window);

    // Updates vectors according to user input
    void UpdateCameraVectors();
};

