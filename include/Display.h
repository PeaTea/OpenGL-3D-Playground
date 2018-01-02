#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Window.hpp>
#include <GL/glew.h>
#include "RenderGame.h"

class Display
{
public:
    Display(int width, int height, std::string title, sf::Uint32 style);
    ~Display();
    sf::Window& get();
    void update();
    void render(int& curr_lvl);
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

    float last_mousex;
    float last_mousey;

};

#endif