#include "Display.h"
#include "SFEvent.h"
#include "Vec2.h"
#include "Settings.h"

#include <iostream>

#define TEST 0

#if !TEST
#define DEBUG

static bool wire_frame = false;
static bool y_mov_switch = false;
static bool out_of_focus = false;

// Everything I need to know for a PC platform
namespace PC
{
    int WIDTH = Settings::width();
    int HEIGHT = Settings::height();
    const std::string TITLE = "OpenGL Playground";
    bool FULLSCREEN = Settings::fullscreen();
}


namespace Main_GB
{
    bool collision = true;
    int current_level = 1;
}


int main()
{
    Display display(PC::WIDTH, PC::HEIGHT, PC::TITLE, PC::FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default);

    sf::Clock clock;
    float delta_time = 0.0f, current_time = 0.0f, last_time = 0.0f;

    SFEvent sfevent;

    //Enabling OpenGL stuff

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    glAlphaFunc(GL_GREATER, 0.5f);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

    std::cout << glGetString(GL_VERSION) << std::endl;

    while(!display.should_close)
    {
        current_time = (float)clock.getElapsedTime().asMilliseconds();
        delta_time = current_time - last_time;
        last_time = current_time;

        while(display.get().pollEvent(sfevent.get()))
        {
            switch(sfevent.type())
            {
            case sf::Event::Closed:
                display.close();
                break;
            case sf::Event::Resized:
                glViewport(0, 0, sfevent.size().width, sfevent.size().height);
                break;
#ifdef DEBUG
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
                {
                    display.switch_wireframe(!wire_frame);
                    wire_frame = !wire_frame;
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
                {
                    display.restrain_camera_y(!y_mov_switch);
                    y_mov_switch = !y_mov_switch;
                    Main_GB::collision = !Main_GB::collision;
                }
                break;
#endif
            case sf::Event::LostFocus:
                out_of_focus = true;
                break;
            case sf::Event::GainedFocus:
                out_of_focus = false;
                break;
            }
        }

        if(!out_of_focus)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            display.process_mouse_movement(delta_time);

            display.process_keyboard_input(delta_time, Main_GB::collision, Main_GB::current_level);

            glEnable(GL_CULL_FACE);
            display.render(Main_GB::current_level);

            glDisable(GL_CULL_FACE);
            display.render_transparent();

            display.update(); // Also swaps buffers
        }
    }
}


#else

void main()
{
    Vec2 v(3, 4);
    Vec2 o(2, 1);

    v /= o;

    std::cout << v << std::endl;

    std::cin.get();
}

#endif