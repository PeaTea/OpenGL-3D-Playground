#include "Camera.h"
#include "Collision.h"
#include "RenderGame.h"

#include <glm/gtc/matrix_transform.hpp>

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
	front_vec.y = sin(glm::radians(pitch));
	front_vec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front_vec);

	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}


void Camera::process_keyboard(CameraMovement direction, float dt, const RenderGame& render_game)
{
	float vel = movement_speed * dt;
	switch(direction)
	{
	case FORWARD:
		position += front * vel * Collision::in_level(render_game.levels[0], RG_GB::TEX_SIZE, position);
		break;
	case BACKWARD:
		position -= front * vel * Collision::in_level(render_game.levels[0], RG_GB::TEX_SIZE, position);
		break;
	case RIGHT:
		position += right * (vel * 0.5f) * Collision::in_level(render_game.levels[0], RG_GB::TEX_SIZE, position);
		break;
	case LEFT:
		position -= right * (vel * 0.5f) * Collision::in_level(render_game.levels[0], RG_GB::TEX_SIZE, position);
		break;
	case UP:
		position.y += (SPEED * 5) * vel;
		break;
	case DOWN:
		position.y -= (SPEED * 5) * vel;
		break;
	}

	if(!y_movement)	position.y = 0.0f;
}


void Camera::restrain_y_mov(bool& y_mov)
{
	if(y_movement)	y_movement = false;
	else			y_movement = true;
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


Camera::~Camera()
{
}
