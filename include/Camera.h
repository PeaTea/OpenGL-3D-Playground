#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Level;

const float YAW = 112.5f;
const float PITCH = 0.0f;
const float SPEED = 0.4f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 80.0f;

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

    void process_keyboard(CameraMovement direction, float dt, const Level& lvl, const int& num_level,
                          bool& collision, const int& v = 8, const bool& output = false);
    void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true);
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
    float zoom;

    void restrain_y_mov(bool& y_mov);

private:
    void update_camera_vectors();

};

#endif