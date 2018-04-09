#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include "Image.h"
#include "Camera.h"

struct Collision
{
    static bool in_level(const Image& level, const glm::vec3& new_pos, const glm::vec3& old_pos);
    static glm::vec3 in_level(const Image& level, glm::vec3& new_pos, Camera& camera);
};

#endif