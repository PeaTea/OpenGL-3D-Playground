#include "Camera.h"
#include "Collision.h"
#include "RenderGame.h"
#include "Maths.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static bool y_movement = false;

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    :	front{glm::vec3(0, 0, -1)}
    ,	movement_speed{SPEED}
    ,	mouse_sensitivity{SENSITIVITY}
    ,	zoom{ZOOM}
{
    position = pos;
    world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();
}


void Camera::update_camera_vectors()
{
    glm::vec3 front_vec;
    front_vec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front_vec.y = sin(glm::radians(pitch));								//Player can't look up or down if disabled
    front_vec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front_vec);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}


void Camera::process_keyboard(CameraMovement direction, float dt, const Level& lvl, const int& num_level,
                              bool& collision, const int& v, const bool& output)
{
    float vel = movement_speed * dt;

    //To avoid "stuttering" when colliding - only change position, when it's viable
    glm::vec3 new_pos = position;
    switch(direction)
    {
    case FORWARD:
        new_pos += front * (vel + v);
        break;
    case BACKWARD:
        new_pos -= front * (vel + v);
        break;
    case RIGHT:
        new_pos += right * (vel + v);
        break;
    case LEFT:
        new_pos -= right * (vel + v);
        break;
    case UP:
        new_pos.y += (SPEED / 3 * v) * vel;
        break;
    case DOWN:
        new_pos.y -= (SPEED / 3 * v) * vel;
        break;
    }

    if(collision) {
        if(Collision::in_level(lvl, new_pos, position))
            position = new_pos;
    } else {
        position = new_pos;
    }


    if(!y_movement)	position.y = 0.0f;

    if(output)
        std::cout << position.x << " | " << position.z << std::endl;
}


void Camera::fall(float dt, int velocity)
{
    position.y -= dt * velocity;
}


void Camera::restrain_y_mov(bool& y_mov)
{
    y_movement = !y_mov;
}


void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(constrain_pitch)
    {
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
    }

    update_camera_vectors();
}


glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}


glm::vec2 Camera::get_2D_pixel_pos(int lvlw, int lvlh)
{
    return {maths::roundf(position.x) % lvlh, maths::roundf(position.z) % lvlw};
}


Camera::~Camera()
{
}
