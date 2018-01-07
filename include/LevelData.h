#pragma once

#include <vector>
#include <map>
#include "Entity.h"

class Level;

struct LevelData
{
    LevelData();

    void init(int lvl_id, const std::vector<GLTexture>& textures, const std::vector<Level>& levels,
              const glm::vec3& cam_pos, std::map<std::string, GLProgram>& programs);
    void update_and_render(const glm::vec3& cam_pos);

private:
    std::vector<Entity> m_entities;
    std::map<std::string, GLProgram> m_programs;
};
