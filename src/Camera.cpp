#include "Camera.h"
#include "Collision.h"
#include "RenderGame.h"
#include "Maths.h"
#include "OutUtils.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static bool y_movement = false;

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
    :	front               {glm::vec3(0, 0, -1)}
    ,	movement_speed      {SPEED}
    ,	mouse_sensitivity   {SENSITIVITY}
    ,	fov                 {FOV}
    ,   position            {pos}
    ,   world_up            {up}
    ,   yaw                 {yaw}
    ,   pitch               {pitch}
    ,   current_level       {0, "Data/Levels/tutorial.png",
                             {-2000.0f, Settings::player_size() * 0.5f, 44.0f},
                             1, 1}
    ,   y_movement          {false}
{
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


void Camera::process_keyboard(CameraMovement direction, float dt, bool& collision, const float& v)
{
    float final_velocity = (movement_speed * v) * (dt * 0.5f);

    //To avoid "stuttering" when colliding - only change position, when it's viable
    glm::vec3 new_pos = position;
    switch(direction)
    {
    case FORWARD:
        new_pos += front * final_velocity;
        break;    
    case BACKWARD:
        new_pos -= front * final_velocity;
        break;
    case RIGHT:
        new_pos += right * final_velocity;
        break;
    case LEFT:
        new_pos -= right * final_velocity;
        break;
    case UP:
        new_pos.y += (SPEED) * final_velocity;
        break;                 
    case DOWN:                 
        new_pos.y -= (SPEED) * final_velocity;
        break;
    }

    if(collision)
        position = Collision::in_level(current_level, new_pos, *this);
    else
        position = new_pos;
    
    if(!y_movement)	position.y = 0.0f;
}


void Camera::fall(float dt, int velocity)
{
    position.y -= dt * velocity;
}


void Camera::process_mouse_movement(float xoffset, float yoffset, const bool& constrain_pitch)
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

void Camera::process_mouse_scrolling(double xoffset, double yoffset)
{
    if(fov >= 1.0f && fov <= 100.0f)
        fov -= yoffset;
    if(fov < 1.0f)
        fov = 1.0f;
    else if(FOV > 100.0f)
        fov = 100.0f;
}


glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}


glm::vec2 Camera::get_2D_pixel_pos(const Vec2<float>& tex_size, const glm::vec3& position)
{
    int x = maths::roundf(position.x) / maths::roundf(tex_size.x);
    int y = maths::roundf(position.z) / maths::roundf(tex_size.x);

    return {x, y};
}


Camera::~Camera()
{
}
