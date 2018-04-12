#include "RenderGame.h"
#include "Camera.h"
#include "Types.h"
#include "OutUtils.h"
#include "ObjLoader.h"
#include "ObjRenderer.h"
#include "GlobalMacros.h"
#include "Timer.h"

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

    //camera.position = m_levels[current_lvl].start();
    camera.position = {0, 0, 0};
    update_camera_pos(camera.position);

    BasicRenderer::enable_cube();
}

void RenderGame::load_shaders()
{
#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer{"Shader loading"};
#endif
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
#ifdef PERFORMANCE_TESTS
    }
#endif
}

void RenderGame::load_levels()
{
#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer {"Level loading"};
#endif
    m_levels.emplace_back(m_levels.size(), "Data/Levels/tutorial.png", glm::vec3(-2000.0f, Settings::player_size() * 0.5f, 44.0f), 10.0f, 50.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral.png", glm::vec3(2000.0f, 0, Settings::player_size() * 2.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/cathedral_extended_test.png",
                          glm::vec3(2000.0f, 0.0f, Settings::player_size() * 20.0f), 1.0f, 15.0f);
    m_levels.emplace_back(m_levels.size(), "Data/Levels/window_test.png", glm::vec3(500, 500, 500), 1.0f, 2.0f);

    m_image_drawer.set_lvl(m_levels[m_current_lvl]);
#ifdef PERFORMANCE_TESTS
    }
#endif
}

void RenderGame::load_textures()
{
#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer{"Texture loading"};
#endif
    m_textures[METAL_CUBE] = {"MetalCube.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[ACID] = {"Acid.png", true, REPEAT, REPEAT, NEAREST, NEAREST};
    m_textures[STONE] = {"Stone.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[LAVA] = {"Lava.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[MARBLE] = {"Marble.png", true, REPEAT, REPEAT, NEAREST, NEAREST};
    m_textures[WOOD] = {"Wood.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[QUAD_TEMPLATE] = {"QuadTemplate.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[DIAGONAL_TEMPLATE] = {"DiagonalTemplate.png", true, REPEAT, REPEAT, LINEAR, LINEAR};
    m_textures[MYSTERIOUS_ROBOT] = {"MysteriousRobot.png", true, CLAMP, CLAMP, NEAREST, NEAREST};
    m_textures[TRANSPARENCY_TEST] = {"TransparencyTest.png", true, CLAMP, CLAMP, LINEAR, LINEAR};
    m_textures[GLASS_LIGHT] = {"Glass_Light.png", true, CLAMP, CLAMP, LINEAR, LINEAR};
    m_textures[BASIC_CIRCLE] = {"BasicCircle.png", true, CLAMP, CLAMP, LINEAR, LINEAR};
#ifdef PERFORMANCE_TESTS
    }
#endif

#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer{"Font loading"};
#endif
    font_renderer.load_numbers("Data/Fonts/Simple/Numbers");
    font_renderer.load_upper_letters("Data/Fonts/Simple/Letters");
    font_renderer.load_other("Data/Fonts/Simple/Other");
#ifdef PERFORMANCE_TESTS
    }
#endif
}

void RenderGame::load_entities()
{
#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer {"Loading entities"};
#endif
    for(unsigned int i = 0; i < m_levels.size(); i++)
    {
        m_levels[i].init(m_textures, m_levels, m_cam_pos, m_programs);
    }
#ifdef PERFORMANCE_TESTS
    }
    {
    RAIITimer timer {"Loading light sources"};
#endif
    load_light_sources();
#ifdef PERFORMANCE_TESTS
    }
#endif
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
#ifdef PERFORMANCE_TESTS
    {
    RAIITimer timer {"Object loading"};
#endif
    std::array<std::string, 6> textures;
    std::fill(textures.begin(), textures.end(), "Data/Textures/Skybox.png");
    m_skybox_cube_map.gen_cube_map(textures, CLAMP_TO_EDGE, CLAMP_TO_EDGE, CLAMP_TO_EDGE, LINEAR, LINEAR);

    m_skybox.init(m_skybox_cube_map, m_levels[m_current_lvl].center(), 30000,
                  "Data/Shaders/Skybox.glsl");

    obj_loader.store_obj_file(File{"Data/Models/cube.obj"}, "cube");
    obj_loader.store_obj_file(File{"Data/Models/test.obj"}, "test");

    obj_loader.store_obj_file(File{"HugeModelsTest/sponza_crytek.obj"}, "sponza");

    Model cube {obj_loader.objects["cube"]};
    Model test {obj_loader.objects["test"]};

    Model sponza {obj_loader.objects["sponza"]};

    m_models["cube"] = cube;
    m_models["test"] = test;
    m_models["sponza"] = sponza;
#ifdef PERFORMANCE_TESTS
    }
#endif
}


void RenderGame::update(const glm::mat4& view_mat, const glm::mat4& projection_mat, const glm::vec3& cam_pos)
{
    ObjRenderer::update(view_mat, projection_mat, cam_pos);
    BasicRenderer::view = view_mat;
    BasicRenderer::proj = projection_mat;
}

void RenderGame::render(Camera& camera, const bool& draw_normals)
{
    BasicRenderer::view = camera.get_view_matrix();
    BasicRenderer::proj = glm::perspective(glm::radians(camera.fov), (float)(m_screen_w / m_screen_h), 0.1f, 80000.0f);   // Interesting "horror" effect: 0.0f (epileptic!)
    update(BasicRenderer::view, BasicRenderer::proj, camera.position);

    glDisable(GL_CULL_FACE);
    m_skybox.render(camera.get_view_matrix(), BasicRenderer::proj, m_deltatime);
    glEnable(GL_CULL_FACE);
    //m_image_drawer.render_cubes(m_textures, m_levels[m_current_lvl], m_programs["point"]);
    ObjRenderer::set_program(m_programs["test_model"]);
    ObjRenderer::render(m_models["sponza"], m_textures[METAL_CUBE].id(), {10, 0, 10}, {1, 1});

    //BasicRenderer::draw_texture(m_textures[METAL_CUBE].id());

    if(draw_normals)
    {
        ObjRenderer::set_program(m_programs["draw_normals"]);
        ObjRenderer::render(m_models["sponza"], m_textures[METAL_CUBE].id(), {10, 0, 10}, {1, 1});
    }
}

void RenderGame::render_transparent(const bool& draw_fps, const int& fps, const glm::vec3& pos)
{
    glDisable(GL_CULL_FACE);
    BasicRenderer::set_program(m_programs["normal"]);
    font_renderer.draw("12345\n67890", {0, 0, 1}, {1, 1}, 1, {1, 1, 0, 1});
    if(draw_fps)
        render_fps(fps, pos);
    //BasicRenderer::set_program(m_programs["normal"]);
    //m_light_sources[0].rotate_around_center(0.1f);
    //m_programs["point"].set_vec3("point_lights[0].position", m_light_sources[0].position());
    //m_light_sources[0].render();
     
    //BasicRenderer::set_program(m_programs["point"]);

    //m_levels[m_current_lvl].data.update_and_render(m_cam_pos, m_image_drawer.get_cf_height() / 2);
}

void RenderGame::render_fps(const int& fps, const glm::vec3& pos)
{
    BasicRenderer::set_program(m_programs["normal"]);
    font_renderer.draw(std::to_string(fps) + " FPS", pos, {1, 1}, 1, {0, 1, 0, 1});
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
