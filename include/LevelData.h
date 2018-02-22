#pragma once

#include <vector>
#include <unordered_map>
#include "Entity.h"

class Level;

struct LevelData
{
    LevelData();

    void init(const int& lvl_id, const std::unordered_map<int, GLTexture>& textures, const std::vector<Level>& levels,
              const glm::vec3& cam_pos, std::unordered_map<std::string, GLProgram>& programs);
    void update_and_render(const glm::vec3& cam_pos, const int& cf_height);

    std::vector<Entity> m_entities;

private:
    std::unordered_map<std::string, GLProgram> m_programs;

    uint m_entity_size;
};
