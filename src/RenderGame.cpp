#include "RenderGame.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"


using namespace RG_GB;

const glm::vec2 ENTITY_TEX_SIZE(62, 96);


RenderGame::RenderGame(int width, int height)
{
    screen_w = width;
    screen_h = height;

    File vsfile("Data/Shaders/VertexShader.glsl");
    File fsfile("Data/Shaders/FragmentShader.glsl");
    GLShader vertex_shader(vsfile, Shadertype::VERTEX);
    GLShader fragment_shader(fsfile, Shadertype::FRAGMENT);
    gl_program.create();
    gl_program.attach_shader(vertex_shader);
    gl_program.attach_shader(fragment_shader);
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
    Level tutorial("./Data/Levels/tutorial.png");

    levels.push_back(tutorial);
}

void RenderGame::set_uniforms()
{
    gl_program.use();

    gl_program.set_int("image", 0);

    gl_program.unuse();
}

void RenderGame::load_textures()
{
    GLTexture metal_cube("Data/Textures/MetalCube.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture acid("Data/Textures/Acid.png", REPEAT, REPEAT, NEAREST, NEAREST);
    GLTexture stone("Data/Textures/Stone.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture lava("Data/Textures/Lava.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture marble("Data/Textures/Marble.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture wood("Data/Textures/Wood.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture q_template("Data/Textures/QuadTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture d_template("Data/Textures/DiagonalTemplate.png", REPEAT, REPEAT, LINEAR, LINEAR);
    GLTexture myst_robot("Data/Textures/MysteriousRobot.png", CLAMP, CLAMP, NEAREST, NEAREST);
    GLTexture transparency_test("Data/Textures/TransparencyTest.png", CLAMP, CLAMP, LINEAR, LINEAR);

    textures.push_back(metal_cube);
    textures.push_back(acid);
    textures.push_back(stone);
    textures.push_back(lava);
    textures.push_back(marble);
    textures.push_back(wood);
    textures.push_back(q_template);
    textures.push_back(d_template);
    textures.push_back(myst_robot);
    textures.push_back(transparency_test);
}

void RenderGame::update_matrices(glm::mat4 view_mat, glm::mat4 projection_mat)
{
    glm::mat4 view;
    view = view_mat;
    glm::mat4 projection;
    projection = projection_mat;

    gl_program.use();

    gl_program.set_mat4("view", view);
    gl_program.set_mat4("projection", projection);
}

void RenderGame::render(Camera& camera)
{
    update_matrices(camera.get_view_matrix(),
                    glm::perspective(glm::radians(FOV), (float)(screen_w / screen_h), 0.1f, 100000.0f));

    /*
    for(uint8_t i = 0; i < 10; i++)
        renderer.draw_sprite(textures[METAL_CUBE].id(), positions[i], GB_rg::TEX_SIZE, i * 20.0f, glm::vec3(1, 0.3f, 0.5f));*/

    //Renderer::draw_sprite(textures[ACID].id(), glm::vec3(0, -100.0f, 0), glm::vec2(1000, 1000), 90.0f, glm::vec3(1, 0, 0));
    levels[0].draw(textures);
    //Renderer::draw_sprite(textures[CROSSHAIR].id(), glm::vec3(0, 0, 1.0f), TEX_SIZE, 0.0f);
}


void RenderGame::render_transparent()
{
    for(int i = 40; i > 0; i--)
    {
        Renderer::draw_sprite(textures[TRANSPARENCY_TEST].id(),
                              glm::vec3(RG_GB::TEX_SIZE.x * 15.5f - 2000.0f, 0.0f, RG_GB::TEX_SIZE.y * i - 200.0f),
                              ENTITY_TEX_SIZE, 180.0f, glm::vec3(1, 0, 0), glm::vec4(1, 1, 1, 1));
    }
}