#include "RenderGame.h"
#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace RG_GB;

RenderGame::RenderGame(int width, int height, int current_lvl, Camera& camera)
    :   m_screen_w      {width}
    ,   m_screen_h      {height}
    ,   m_current_lvl   {current_lvl}
{
    std::cout << "Loading shaders..." << std::endl;
    load_shaders();

    std::cout << "Loading textures..." << std::endl;
    load_textures();
    set_uniforms();

    std::cout << "Loading levels..." << std::endl;
    load_levels();

    camera.position = m_levels[current_lvl].start();
    update_camera_pos(camera.position);

    std::cout << "Loading entities..." << std::endl;
    load_entities();
}

void RenderGame::load_shaders()
{
    GLShader darken_vertex_shader({"Data/Shaders/DarkenVS.glsl"}, Shadertype::VERTEX);
    GLShader darken_fragment_shader({"Data/Shaders/DarkenFS.glsl"}, Shadertype::FRAGMENT);

    GLShader normal_vertex_shader({"Data/Shaders/NormalVS.glsl"}, Shadertype::VERTEX);
    GLShader normal_fragment_shader({"Data/Shaders/NormalFS.glsl"}, Shadertype::FRAGMENT);

    GLProgram darken;
    GLProgram normal;

    darken.create();
    darken.attach_shader(darken_vertex_shader);
    darken.attach_shader(darken_fragment_shader);
    darken.link();

    normal.create();
    normal.attach_shader(normal_vertex_shader);
    normal.attach_shader(normal_fragment_shader);
    normal.link();

    m_programs["darken"] = darken;
    m_programs["normal"] = normal;

    //Renderer::set_program(m_gl_program_darken);
}

void RenderGame::load_levels()
{
    m_levels.emplace_back(m_levels.size(), "Data/Levels/tutorial.png", glm::vec3(-2000.0f, Settings::player_size() * 0.5f, 44.0f), 10.0f, 50.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral.png", glm::vec3(2000.0f, 0, Settings::player_size() * 2.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral_extended_test.png",
                          glm::vec3(2000.0f, 0.0f, Settings::player_size() * 20.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/window_test.png", glm::vec3(500, 500, 500), 1.0f, 2.0f);
    //m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral_extended.png", glm::vec3(0, 0, 0), 1.0f, 15.0f);
}

void RenderGame::load_textures()
{
    m_textures.emplace_back("MetalCube.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("Acid.png", REPEAT, REPEAT, NEAREST, NEAREST);
    m_textures.emplace_back("Stone.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("Lava.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("Marble.png", REPEAT, REPEAT, NEAREST, NEAREST);
    m_textures.emplace_back("Wood.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("QuadTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("DiagonalTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    m_textures.emplace_back("MysteriousRobot.png", CLAMP, CLAMP, NEAREST, NEAREST);
    m_textures.emplace_back("TransparencyTest.png", CLAMP, CLAMP, LINEAR, LINEAR);
    m_textures.emplace_back("Glass_Light.png", CLAMP, CLAMP, LINEAR, LINEAR);
}

void RenderGame::load_entities()
{
    for(unsigned int i = 0; i < m_levels.size(); i++)
    {
        m_levels[i].init(m_textures, m_levels, m_cam_pos, m_programs);
    }
}

void RenderGame::set_uniforms()
{
    m_programs["darken"].use();
    m_programs["darken"].set_int("image", 0);
    m_programs["normal"].use();
    m_programs["normal"].set_int("image", 0);
    m_programs["normal"].unuse();
}

void RenderGame::update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat)
{
    m_programs["darken"].use();
    m_programs["darken"].set_mat4("view", view_mat);
    m_programs["darken"].set_mat4("projection", projection_mat);
    m_programs["normal"].use();
    m_programs["normal"].set_mat4("view", view_mat);
    m_programs["normal"].set_mat4("projection", projection_mat);
    m_programs["normal"].unuse();
}

void RenderGame::render(Camera& camera)
{
    update_matrices(camera.get_view_matrix(),
                    glm::perspective(glm::radians(FOV), (float)(m_screen_w / m_screen_h), 0.1f, 10000.0f));

    m_ld.render(m_textures, m_levels[m_current_lvl], m_programs["darken"]);
}

void RenderGame::render_transparent()
{
    m_levels[m_current_lvl].data.update_and_render(m_cam_pos);
}

void RenderGame::update_camera_pos(const glm::vec3& cam_pos)
{
    m_cam_pos = cam_pos;
}

