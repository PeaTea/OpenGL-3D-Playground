#include "Display.h"
#include "Camera.h"
#include "OutUtils.h"

#include <iostream>

static Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

Display::Display(int width, int height, std::string title, sf::Uint32 style, int current_lvl)
    :	should_close	{false}
    ,	last_mousex		{width / 2}
    ,	last_mousey		{height / 2}
{
    sf::ContextSettings settings;
    settings.minorVersion = 3;
    settings.majorVersion = 3;
    settings.antialiasingLevel = 4;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.attributeFlags = sf::ContextSettings::Core;

    window.create(sf::VideoMode(width, height), title, style, settings);
    window.setVisible(false);
    window.setVerticalSyncEnabled(Settings::vsync_enabled());

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        logging::log("Failed to init GLEW", lstream::error);
    }

    render_game = new RenderGame(width, height, current_lvl, camera);

    window.setMouseCursorVisible(false);
    window.setVisible(true);
}

Display::~Display()
{
    if(render_game != nullptr) 
        delete render_game;
}

sf::Window& Display::get()
{
    return window;
}

void Display::update()
{
    window.display();
}

void Display::render()
{
    render_game->render(camera);
}

void Display::render_transparent()
{
    render_game->render_transparent();
}

void Display::process_keyboard_input(float dt, bool collision, const int& curr_lvl)
{
    render_game->set_deltatime(dt);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        close();
    }

    int v = collision ? 2 : 50;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        camera.process_keyboard(CameraMovement::FORWARD, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    } if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        camera.process_keyboard(CameraMovement::LEFT, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    } if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        camera.process_keyboard(CameraMovement::BACKWARD, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    } if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        camera.process_keyboard(CameraMovement::RIGHT, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    } if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera.process_keyboard(CameraMovement::UP, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    } if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera.process_keyboard(CameraMovement::DOWN, dt, render_game->m_levels[curr_lvl], curr_lvl, collision, v);
    }

    render_game->update_camera_pos(camera.position);
}

void Display::restrain_camera_y(bool y_mov)
{
    camera.restrain_y_mov(y_mov);
}

void Display::process_mouse_movement(float deltatime)
{
    last_mousex = sf::Mouse::getPosition(window).x;
    last_mousey = sf::Mouse::getPosition(window).y;

    int xoffset = last_mousex - window.getSize().x / 2;
    int yoffset = window.getSize().y / 2 - last_mousey;

    camera.process_mouse_movement(static_cast<float>(xoffset),
                                  static_cast<float>(yoffset));

    sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window);
}

void Display::close()
{
    should_close = true;
    window.close();
}

void Display::switch_wireframe(bool wireframe)
{
    if(wireframe)   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}