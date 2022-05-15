#include "Camera.h"

// Initialize global world vector
const glm::vec3 Camera::world_up = glm::vec3(0.0f, 1.0f, 0.0f);

// Constructor
Camera::Camera(const int width, const int height, const glm::vec3& position)
    :m_width(width), m_height(height), m_position(position)
{
    m_z_near = 0.1f;
    m_z_far = 500.0f;
    m_FOV = 45.0f;
    m_yaw = -90.0f;
    m_pitch = 0.0f;

    m_camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    m_camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camera_right = glm::vec3(1.0f, 0.0f, 0.0f);

    m_camera_speed_factor = 4.5f;
    m_mouse_sensitivity = 0.1f;
}

// Getters
const glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_camera_front, m_camera_up);
}
const glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(m_FOV), ((float)(m_width)) / m_height, m_z_near, m_z_far);
}
const glm::vec3 Camera::GetPosition() const
{
    return m_position;
}
float Camera::GetPitch() const
{
    return m_pitch;
}

float Camera::GetNear() const
{
    return m_z_near;
}

float Camera::GetFar() const
{
    return m_z_far;
}

// Setters
void Camera::SetPitch(float new_pitch)
{
    m_pitch = new_pitch;
    UpdateCameraVectors();
}
void Camera::SetPosition(const glm::vec3& position)
{
    m_position = position;
    UpdateCameraVectors();
}

// Input processing
void Camera::ProcessInput(GLFWwindow* window, float delta_time)
{
    KeyboardControl(window, delta_time);
    MouseControl(window);

    // update the vectors to match new camera orientation
    UpdateCameraVectors();
}
void Camera::KeyboardControl(GLFWwindow* window, float delta_time)
{
    float camera_speed = m_camera_speed_factor * delta_time;

    // Handles keyboard inputs
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += m_camera_front * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= m_camera_right * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= m_camera_front * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += m_camera_right * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += m_camera_up * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        m_position -= m_camera_up * camera_speed;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}
void Camera::MouseControl(GLFWwindow* window)
{
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y);

    float x_change = static_cast<float>(mouse_x - (m_width / 2));
    float y_change = static_cast<float>((m_height / 2) - mouse_y);

    x_change *= m_mouse_sensitivity;
    y_change *= m_mouse_sensitivity;

    m_yaw += x_change;
    m_pitch += y_change;

    // checking pitch to avoid rolling over
    if (m_pitch > 89.0f)
        m_pitch = 89.0f;
    if (m_pitch < -89.0f)
        m_pitch = -89.0f;

    //locking cursor to the middle of the screen
    glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
}

// Updates vectors according to user input 
void Camera::UpdateCameraVectors()
{
    // Calculate the new front vector
    m_camera_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera_front.y = sin(glm::radians(m_pitch));
    m_camera_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera_front = glm::normalize(m_camera_front);

    // Based on the new front vector, calculate right and up
    m_camera_right = glm::normalize(glm::cross(m_camera_front, world_up));
    m_camera_up = glm::normalize(glm::cross(m_camera_right, m_camera_front));
}