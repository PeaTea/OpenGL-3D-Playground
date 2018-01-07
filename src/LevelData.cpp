#include "LevelData.h"
#include "RenderGame.h"

#include "../Data/Colors.data"

LevelData::LevelData()
    :   m_entities {}
{
}

void LevelData::init(int lvl_id, const std::vector<GLTexture>& textures, const std::vector<Level>& levels, const glm::vec3& cam_pos,
                     std::map<std::string, GLProgram>& programs)
{
    m_programs = programs;
    switch(lvl_id)
    {
    case 0:
        break;
    case 1:
        m_entities.emplace_back(textures[MYSTERIOUS_ROBOT].id(),
                                glm::vec3(Settings::tex_size() * 15.5f, Settings::entity_size().y / 2.0f, Settings::tex_size() * 20 - 200.0f),
                                cam_pos, Settings::entity_size() * 2);
        m_entities.emplace_back(textures[MYSTERIOUS_ROBOT].id(),
                                glm::vec3(Settings::tex_size() * 10.5f, Settings::entity_size().y / 0.6f, Settings::tex_size() * 5 + 200.0f),
                                cam_pos, Settings::entity_size() * 5);
        break;
    case 2:
        m_entities.emplace_back(textures[MYSTERIOUS_ROBOT].id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 15.5f, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 6),
                                cam_pos, Vec2(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures[MYSTERIOUS_ROBOT].id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 25, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 20),
                                cam_pos, Vec2(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures[MYSTERIOUS_ROBOT].id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 6, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 20),
                                cam_pos, Vec2(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures[GLASS_LIGHT].id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 15.5f, levels[2].scaled_tex_size().y * 0.465f, levels[2].scaled_tex_size().x * 9.5f),
                                Vec2(levels[2].scaled_tex_size().x * 14, levels[2].scaled_tex_size().y),
                                180.0f, glm::vec3(1, 0, 0), BLUE);
        m_entities.emplace_back(textures[GLASS_LIGHT].id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 15.5f, levels[2].scaled_tex_size().y * 0.465f, levels[2].scaled_tex_size().x * 15.5f),
                                Vec2(levels[2].scaled_tex_size().x * 14, levels[2].scaled_tex_size().y),
                                180.0f, glm::vec3(1, 0, 0), BLUE);
        break;
    }
}


void LevelData::update_and_render(const glm::vec3& cam_pos)
{
    for(unsigned int i = 0; i < m_entities.size(); i++)
    {
        m_entities[i].render(m_programs);
        m_entities[i].set_cam_pos(cam_pos);
    }
}