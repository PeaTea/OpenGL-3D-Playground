/*
 * This file is deprecated. Use DisplayGLFW instead
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "RenderGame.h"

class DisplaySFML
{
public:
    DisplaySFML(int width, int height, std::string title, sf::Uint32 style, int current_lvl = 0);
    ~DisplaySFML();
    sf::Window& get_instance();
    void update();
    void render();
    void render_transparent();
    void process_keyboard_input(float deltatime, bool collision, const int& curr_lvl);
    void process_mouse_movement(float deltatime);
    void close();
    void switch_wireframe(bool wireframe);
    void restrain_camera_y(bool y_mov);

    bool should_close;

private:
    RenderGame* render_game;
    sf::Window window;

    int last_mousex;
    int last_mousey;
};

#endif