#include "ImageData.h"
#include "RenderGame.h"

#include "../Data/Colors.data"

ImageData::ImageData()
    :   m_entities {}
{
}

void ImageData::init(const int& lvl_id, const std::unordered_map<int, GLTexture>& textures, const std::vector<Image>& levels, const glm::vec3& cam_pos,
                     std::unordered_map<std::string, GLProgram>& programs)
{
    m_programs = programs;
    switch(lvl_id)
    {
    case 0:
        break;
    case 1:
        m_entities.emplace_back(textures.at(MYSTERIOUS_ROBOT).id(),
                                glm::vec3(Settings::tex_size() * 15.5f, Settings::entity_size().y * 0.5f, Settings::tex_size() * 20 - 200.0f),
                                cam_pos, Settings::entity_size() * 2.0f);
        m_entities.emplace_back(textures.at(MYSTERIOUS_ROBOT).id(),
                                glm::vec3(Settings::tex_size() * 10.5f, Settings::entity_size().y / 0.6f, Settings::tex_size() * 5 + 200.0f),
                                cam_pos, Settings::entity_size() * 5.0f);
        break;
    case 2:
        m_entities.emplace_back(textures.at(MYSTERIOUS_ROBOT).id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 16.0f, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 6.5f),
                                cam_pos, Vec2<float>(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures.at(MYSTERIOUS_ROBOT).id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 25.5f, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 20.5f),
                                cam_pos, Vec2<float>(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures.at(MYSTERIOUS_ROBOT).id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 6.5f, Settings::entity_size().y * 0.5f, levels[2].scaled_tex_size().x * 20.5f),
                                cam_pos, Vec2<float>(levels[2].scaled_tex_size().x * 1.5f, levels[2].scaled_tex_size().y * 0.15f));
        m_entities.emplace_back(textures.at(GLASS_LIGHT).id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 16.0f, levels[2].scaled_tex_size().y * 0.465f, levels[2].scaled_tex_size().x * 10.0f),
                                Vec2<float>(levels[2].scaled_tex_size().x * 14.0f, levels[2].scaled_tex_size().y),
                                180.0f, glm::vec3(1, 0, 0), BLUE);
        m_entities.emplace_back(textures.at(GLASS_LIGHT).id(),
                                glm::vec3(levels[2].scaled_tex_size().x * 16.0f, levels[2].scaled_tex_size().y * 0.465f, levels[2].scaled_tex_size().x * 16.0f),
                                Vec2<float>(levels[2].scaled_tex_size().x * 14.0f, levels[2].scaled_tex_size().y),
                                180.0f, glm::vec3(1, 0, 0), BLUE);
        break;
    }

    m_entity_size = m_entities.size();
}


void ImageData::update_and_render(const glm::vec3& cam_pos, const int& cf_height)
{
    for(uint i {}; i < m_entity_size; i++)
    {
        m_entities[i].set_cam_pos(cam_pos);
        m_entities[i].render(m_programs, cf_height);
    }
}