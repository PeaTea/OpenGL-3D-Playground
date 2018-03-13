#include "RenderGame.h"
#include "Camera.h"
#include "Types.h"
#include "OutUtils.h"
#include "ObjLoader.h"
#include "ObjRenderer.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "../Data/Colors.data"

RenderGame::RenderGame(const uint& width, const uint& height, const int& current_lvl, Camera& camera)
    :   m_screen_w      {width}
    ,   m_screen_h      {height}
    ,   m_current_lvl   {current_lvl}
{
    output::print("Loading shaders...");
    load_shaders();

    output::print("Loading textures...");
    load_textures();

    output::print("Loading levels...");
    load_levels();

    output::print("Loading entities...");
    load_entities();

    output::print("Loading objects...");
    load_objects();

    camera.position = m_levels[current_lvl].start();
    update_camera_pos(camera.position);

    BasicRenderer::enable_cube();
}

void RenderGame::load_shaders()
{
    shaderfile::Data darken_src = shaderfile::parse("Data/Shaders/Darken.glsl");
    shaderfile::Data normal_src = shaderfile::parse("Data/Shaders/Normal.glsl");
    shaderfile::Data point_src = shaderfile::parse("Data/Shaders/Point.glsl");
    shaderfile::Data test_model_src = shaderfile::parse("Data/Shaders/TestModel.glsl");
    shaderfile::Data draw_normals_src = shaderfile::parse("Data/Shaders/DrawNormals.glsl");

    GLProgram darken, normal, point, test_model, draw_normals;

    darken.auto_gen(darken_src);
    normal.auto_gen(normal_src);
    point.auto_gen(point_src);
    test_model.auto_gen(test_model_src);
    draw_normals.auto_gen(draw_normals_src);

    m_programs["darken"] = darken;
    m_programs["normal"] = normal;
    m_programs["point"] = point;
    m_programs["test_model"] = test_model;
    m_programs["draw_normals"] = draw_normals;

    BasicRenderer::set_program(m_programs["point"]);
}

void RenderGame::load_levels()
{
    m_levels.emplace_back(m_levels.size(), "Data/Levels/tutorial.png", glm::vec3(-2000.0f, Settings::player_size() * 0.5f, 44.0f), 10.0f, 50.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral.png", glm::vec3(2000.0f, 0, Settings::player_size() * 2.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral_extended_test.png",
                          glm::vec3(2000.0f, 0.0f, Settings::player_size() * 20.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/window_test.png", glm::vec3(500, 500, 500), 1.0f, 2.0f);

    m_image_drawer.set_lvl(m_levels[m_current_lvl]);
}

void RenderGame::load_textures()
{
    m_textures.emplace(METAL_CUBE, GLTexture{"MetalCube.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(ACID, GLTexture{"Acid.png", REPEAT, REPEAT, NEAREST, NEAREST});
    m_textures.emplace(STONE, GLTexture{"Stone.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(LAVA, GLTexture{"Lava.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(MARBLE, GLTexture{"Marble.png", REPEAT, REPEAT, NEAREST, NEAREST});
    m_textures.emplace(WOOD, GLTexture{"Wood.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(QUAD_TEMPLATE, GLTexture{"QuadTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(DIAGONAL_TEMPLATE, GLTexture{"DiagonalTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR});
    m_textures.emplace(MYSTERIOUS_ROBOT, GLTexture{"MysteriousRobot.png", CLAMP, CLAMP, NEAREST, NEAREST});
    m_textures.emplace(TRANSPARENCY_TEST, GLTexture{"TransparencyTest.png", CLAMP, CLAMP, LINEAR, LINEAR});
    m_textures.emplace(GLASS_LIGHT, GLTexture{"Glass_Light.png", CLAMP, CLAMP, LINEAR, LINEAR});
    m_textures.emplace(BASIC_CIRCLE, GLTexture{"BasicCircle.png", CLAMP, CLAMP, LINEAR, LINEAR});
    m_textures.emplace(SUN, GLTexture{"Sun.png", CLAMP, CLAMP, NEAREST, NEAREST});
}

void RenderGame::load_entities()
{
    for(unsigned int i = 0; i < m_levels.size(); i++)
    {
        m_levels[i].init(m_textures, m_levels, m_cam_pos, m_programs);
    }
    load_light_sources();
}

void RenderGame::load_light_sources()
{
    int curr_lvl_w = (m_levels[m_current_lvl].width() - 1) * (int)m_levels[m_current_lvl].scaled_tex_size().x;
    int curr_lvl_h = (m_levels[m_current_lvl].height() - 1) * (int)m_levels[m_current_lvl].scaled_tex_size().x;

    switch(m_current_lvl)
    {
    case 2:
        /*m_light_sources.emplace_back(m_textures.at(SUN),
                                     glm::vec3(curr_lvl_w / 2, 3000, curr_lvl_h / 2),
                                     glm::vec2(Settings::tex_size() * 12, Settings::tex_size() * 12),
                                     ORANGE_YELLOW, 1000000, 10000, m_levels[m_current_lvl]);*/
        m_light_sources.emplace_back(m_levels[m_current_lvl].data.m_entities[3].get_position(),
                                     1500.0f, 1500.0f, BLUE, m_levels[m_current_lvl]);
        m_light_sources.emplace_back(m_levels[m_current_lvl].data.m_entities[4].get_position(),
                                     1500.0f, 1500.0f, BLUE, m_levels[m_current_lvl]);
        m_light_sources.emplace_back(glm::vec3(2000.0f, m_levels[m_current_lvl].height() / 2, 5500.0f),
                                     3000.0f, 3000.0f, ICY_COLD, m_levels[m_current_lvl]);
        m_light_sources.emplace_back(glm::vec3(2000.0f, m_levels[m_current_lvl].height(), 500.0f),
                                     1000.0f, 1000.0f, GREEN, m_levels[m_current_lvl]);
        m_light_sources.emplace_back(glm::vec3{512, 512, 512}, 3000.0f, 3000.0f, ICY_COLD, m_levels[m_current_lvl]);

        m_programs["point"].use();
        m_programs["point"].set_int("num_lights", m_light_sources.size());

        for(uint i = 0; i < m_light_sources.size(); i++)
        {
            std::string variable = "point_lights[" + std::to_string(i) + "]";
            m_programs["point"].set_vec3(std::string(variable + ".position").c_str(), m_light_sources[i].position());
            m_programs["point"].set_vec4(std::string(variable + ".color").c_str(), m_light_sources[i].color());
            m_programs["point"].set_float(std::string(variable + ".radius").c_str(), m_light_sources[i].radius());
        }
        m_programs["point"].unuse();
        break;
    }
}

void RenderGame::load_objects()
{
    std::array<std::string, 6> textures;
    std::fill(textures.begin(), textures.end(), "Data/Textures/Skybox.png");
    m_skybox_cube_map.gen_cube_map(textures, CLAMP_TO_EDGE, CLAMP_TO_EDGE, CLAMP_TO_EDGE, LINEAR, LINEAR);

    m_skybox.init(m_skybox_cube_map, m_levels[m_current_lvl].center(), 30000,
                  "Data/Shaders/Skybox.glsl");

    obj_loader.store_obj_file(File{"Data/Models/cube.obj"}, "cube");
    obj_loader.store_obj_file(File{"Data/Models/test.obj"}, "test");

    Model cube {obj_loader.objects["cube"]};
    Model test {obj_loader.objects["test"]};

    m_models["cube"] = cube;
    m_models["test"] = test;
}


void RenderGame::update(const glm::mat4& view_mat, const glm::mat4& projection_mat, const glm::vec3& cam_pos)
{
    ObjRenderer::update(view_mat, projection_mat, cam_pos);
    BasicRenderer::view = view_mat;
    BasicRenderer::proj = projection_mat;
}

void RenderGame::render(Camera& camera)
{
    BasicRenderer::view = camera.get_view_matrix();
    BasicRenderer::proj = glm::perspective(glm::radians(camera.fov), (float)(m_screen_w / m_screen_h), 0.1f, 80000.0f);   // Interesting "horror" effect: 0.0f (epileptic!)
    update(BasicRenderer::view, BasicRenderer::proj, camera.position);

    glDisable(GL_CULL_FACE);
    m_skybox.render(camera.get_view_matrix(), BasicRenderer::proj, m_deltatime);
    //glEnable(GL_CULL_FACE);
    //m_image_drawer.render_cubes(m_textures, m_levels[m_current_lvl], m_programs["point"]);
    ObjRenderer::set_program(m_programs["test_model"]);
    ObjRenderer::render(m_models["test"], m_textures[METAL_CUBE].id(), {512, 0, 512}, {1, 1});
    ObjRenderer::set_program(m_programs["draw_normals"]);
    ObjRenderer::render(m_models["test"], m_textures[METAL_CUBE].id(), {512, 0, 512}, {1, 1});
}

void RenderGame::render_transparent()
{
    //BasicRenderer::set_program(m_programs["normal"]);
    //m_light_sources[0].rotate_around_center(0.1f);
    //m_programs["point"].set_vec3("point_lights[0].position", m_light_sources[0].position());
    //m_light_sources[0].render();
     
    //BasicRenderer::set_program(m_programs["point"]);

    //m_levels[m_current_lvl].data.update_and_render(m_cam_pos, m_image_drawer.get_cf_height() / 2);
}

void RenderGame::update_camera_pos(const glm::vec3& cam_pos)
{
    m_cam_pos = cam_pos;
}

void RenderGame::set_deltatime(float dt)
{
    m_deltatime = dt;
}

glm::vec3 RenderGame::get_cam_pos()
{
    return m_cam_pos;
}
