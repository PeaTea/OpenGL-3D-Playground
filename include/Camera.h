#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "Level.h"

const float YAW = 112.5f;
const float PITCH = 0.0f;
const float SPEED = 100.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 80.0f;

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 0), float yaw = YAW, float pitch = PITCH);
    ~Camera();

    void process_keyboard(CameraMovement direction, float dt, bool& collision, const float& v = 8);
    void process_mouse_movement(float xoffset, float yoffset,
                                const bool& constrain_pitch = true);
    void process_mouse_scrolling(double xoffset, double yoffset);
    void fall(float dt, int velocity = SPEED);
    
    glm::vec2 get_2D_pixel_pos(const Vec2<float>& tex_size, const glm::vec3& position);

    glm::mat4 get_view_matrix();

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float fov;

    Level current_level;

    bool y_movement;

private:
    void update_camera_vectors();
};

#endif