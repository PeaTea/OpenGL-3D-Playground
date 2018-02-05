#include "RenderGame.h"
#include "Camera.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../Data/Colors.data"

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

    Renderer::enable_test();
}

void RenderGame::load_shaders()
{
    GLShader darken_vertex_shader({"Data/Shaders/DarkenVS.glsl"}, Shadertype::VERTEX);
    GLShader darken_fragment_shader({"Data/Shaders/DarkenFS.glsl"}, Shadertype::FRAGMENT);

    GLShader normal_vertex_shader({"Data/Shaders/NormalVS.glsl"}, Shadertype::VERTEX);
    GLShader normal_fragment_shader({"Data/Shaders/NormalFS.glsl"}, Shadertype::FRAGMENT);

    GLShader diffuse_vertex_shader({"Data/Shaders/DiffuseVS.glsl"}, Shadertype::VERTEX);
    GLShader diffuse_fragment_shader({"Data/Shaders/DiffuseFS.glsl"}, Shadertype::FRAGMENT);

    GLShader point_vertex_shader({"Data/Shaders/PointVS.glsl"}, Shadertype::VERTEX);
    GLShader point_fragment_shader({"Data/Shaders/PointFS.glsl"}, Shadertype::FRAGMENT);

    GLProgram darken;
    GLProgram normal;
    GLProgram diffuse;
    GLProgram point;

    darken.create();
    darken.attach_shader(darken_vertex_shader);
    darken.attach_shader(darken_fragment_shader);
    darken.link();

    normal.create();
    normal.attach_shader(normal_vertex_shader);
    normal.attach_shader(normal_fragment_shader);
    normal.link();

    diffuse.create();
    diffuse.attach_shader(diffuse_vertex_shader);
    diffuse.attach_shader(diffuse_fragment_shader);
    diffuse.link();

    point.create();
    point.attach_shader(point_vertex_shader);
    point.attach_shader(point_fragment_shader);
    point.link();

    m_programs["darken"] = darken;
    m_programs["normal"] = normal;
    m_programs["diffuse"] = diffuse;
    m_programs["point"] = point;

    Renderer::set_program(m_programs["diffuse"]);
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
    m_textures.emplace_back("BasicCircle.png", CLAMP, CLAMP, LINEAR, LINEAR);
}

void RenderGame::load_entities()
{
    for(unsigned int i = 0; i < m_levels.size(); i++)
    {
        m_levels[i].init(m_textures, m_levels, m_cam_pos, m_programs);
    }
    int curr_lvl_w = (m_levels[m_current_lvl].width() - 1) * m_levels[m_current_lvl].scaled_tex_size().x;
    int curr_lvl_h = (m_levels[m_current_lvl].height() - 1) * m_levels[m_current_lvl].scaled_tex_size().x;
    /*m_light_sources.emplace_back(m_textures[BASIC_CIRCLE], 
                                 glm::vec3(curr_lvl_w / 2, 3000, curr_lvl_h / 2),
                                 glm::vec2(Settings::tex_size() * 5, Settings::tex_size() * 5),
                                 glm::vec4(0.5, 1, 1, 1), 100000, m_levels[m_current_lvl]);*/
    m_light_sources.emplace_back(m_levels[m_current_lvl].data.m_entities[3].get_position(),
                                 1500, BLUE, m_levels[m_current_lvl]);
    m_light_sources.emplace_back(m_levels[m_current_lvl].data.m_entities[4].get_position(),
                                 1500, BLUE, m_levels[m_current_lvl]);
    m_light_sources.emplace_back(glm::vec3(2000, m_levels[m_current_lvl].height() / 2, 5500),
                                 3000, ICY_COLD, m_levels[m_current_lvl]);
    m_light_sources.emplace_back(glm::vec3(2000, m_levels[m_current_lvl].height(), 500),
                                 1000, GREEN, m_levels[m_current_lvl]);

    m_programs["point"].use();
    m_programs["point"].set_int("num_lights", m_light_sources.size());

    for(int i = 1; i < m_light_sources.size(); i++)
    {
        std::string variable = "point_lights[" + std::to_string(i) + "]";
        m_programs["point"].set_vec3(std::string(variable + ".position").c_str(), m_light_sources[i].position());
        m_programs["point"].set_vec4(std::string(variable + ".color").c_str(), m_light_sources[i].color());
        m_programs["point"].set_float(std::string(variable + ".radius").c_str(), m_light_sources[i].radius());
    }
    m_programs["point"].unuse();
}

void RenderGame::set_uniforms()
{
    m_programs["darken"].use();
    m_programs["darken"].set_int("image", 0);
    m_programs["normal"].use();
    m_programs["normal"].set_int("image", 0);
    m_programs["diffuse"].use();
    m_programs["diffuse"].set_int("image", 0);
    m_programs["diffuse"].unuse();
}

void RenderGame::update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat)
{
    m_programs["darken"].use();
    m_programs["darken"].set_mat4("view", view_mat);
    m_programs["darken"].set_mat4("projection", projection_mat);
    m_programs["normal"].use();
    m_programs["normal"].set_mat4("view", view_mat);
    m_programs["normal"].set_mat4("projection", projection_mat);
    m_programs["diffuse"].use();
    m_programs["diffuse"].set_mat4("view", view_mat);
    m_programs["diffuse"].set_mat4("projection", projection_mat);
    //m_programs["diffuse"].set_vec3("light_pos", {2000, 2000, 2000});
    m_programs["point"].use();
    m_programs["point"].set_mat4("view", view_mat);
    m_programs["point"].set_mat4("projection", projection_mat);
    m_programs["point"].unuse();

}

void RenderGame::render(Camera& camera)
{
    update_matrices(camera.get_view_matrix(),
                    glm::perspective(glm::radians(FOV), (float)(m_screen_w / m_screen_h), 0.1f, 50000.0f));

    m_ld.render_cubes(m_textures, m_levels[m_current_lvl], m_programs["point"]);
}

void RenderGame::render_transparent()
{
    //m_light_sources[0].rotate_around_center(0.1f);
    //m_light_sources[0].render();

    //m_programs["point"].set_vec3("point_lights[0].position", m_light_sources[0].position());

    m_levels[m_current_lvl].data.update_and_render(m_cam_pos, m_ld.get_cf_height() / 2);
}

void RenderGame::update_camera_pos(const glm::vec3& cam_pos)
{
    m_cam_pos = cam_pos;
}

