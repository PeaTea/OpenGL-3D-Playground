#include "RenderGame.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "LevelDrawer.h"

using namespace RG_GB;

const glm::vec2 ENTITY_TEX_SIZE(62, 96);
const float PLAYER_SIZE = 128.0f;

RenderGame::RenderGame(int width, int height)
{
    screen_w = width;
    screen_h = height;

    GLShader basic_vertex_shader({"Data/Shaders/BasicVertexShader.glsl"}, Shadertype::VERTEX);
    GLShader basic_fragment_shader({"Data/Shaders/BasicFragmentShader.glsl"}, Shadertype::FRAGMENT);

    gl_program.create();
    gl_program.attach_shader(basic_vertex_shader);
    gl_program.attach_shader(basic_fragment_shader);
    gl_program.link();

    Renderer::set_program(gl_program);

    std::cout << "Loading textures..." << std::endl;
    load_textures();
    set_uniforms();

    std::cout << "Loading levels..." << std::endl;
    load_levels();
}

void RenderGame::load_levels()
{
    levels.emplace_back("Data/Levels/tutorial.png", glm::vec3(-2000.0f, PLAYER_SIZE / 2, 44.0f), 10, 50);
    levels.emplace_back("Data/Levels/cathedral.png", glm::vec3(0, 0, 0), 2, 30);
}

void RenderGame::set_uniforms()
{
    gl_program.use();

    gl_program.set_int("image", 0);

    gl_program.unuse();
}

void RenderGame::load_textures()
{
    textures.emplace_back("MetalCube.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("Acid.png", REPEAT, REPEAT, NEAREST, NEAREST);
    textures.emplace_back("Stone.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("Lava.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("Marble.png", REPEAT, REPEAT, NEAREST, NEAREST);
    textures.emplace_back("Wood.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("QuadTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("DiagonalTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    textures.emplace_back("MysteriousRobot.png", CLAMP, CLAMP, NEAREST, NEAREST);
    textures.emplace_back("TransparencyTest.png", CLAMP, CLAMP, LINEAR, LINEAR);
}

void RenderGame::update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat)
{
    gl_program.use();
    gl_program.set_mat4("view", view_mat);
    gl_program.set_mat4("projection", projection_mat);
    gl_program.unuse();
}

void RenderGame::render(Camera& camera, int& curr_lvl)
{
    update_matrices(camera.get_view_matrix(),
                    glm::perspective(glm::radians(FOV), (float)(screen_w / screen_h), 0.1f, 1000000.0f));

    LevelDrawer::render(textures, levels[curr_lvl]);
}


void RenderGame::render_transparent()
{
    
    for(int i = 40; i > 0; i--)
    {
        Renderer::draw_sprite(textures[TRANSPARENCY_TEST].id(),
                              glm::vec3(RG_GB::TEX_SIZE.x * 15.5f, 0.0f, RG_GB::TEX_SIZE.y * i - 200.0f),
                              ENTITY_TEX_SIZE, 180.0f, glm::vec3(1, 0, 0), glm::vec4(0, 1, 1, 1));
    }
    
    Renderer::draw_sprite(textures[MYSTERIOUS_ROBOT].id(),
                          glm::vec3(TEX_SIZE.x * 15.5f, ENTITY_TEX_SIZE.y / 2.0f, TEX_SIZE.y * 20 - 200.0f),
                          ENTITY_TEX_SIZE * glm::vec2(2.0f, 2.0f), 180.0f, glm::vec3(1, 0, 0));
}