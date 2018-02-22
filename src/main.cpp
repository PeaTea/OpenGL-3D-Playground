#include "Settings.h"
#include "Display.h"
#include "SFEvent.h"
#include "Vec2.h"
#include "OutUtils.h"
#include "Maths.h"
#include "Timer.h"

#include <iostream>

#define TEST 0

struct StartupOperations
{
    StartupOperations() 
    {
        //std::ios::sync_with_stdio(false); 
        output::print("Starting...");    
    }
}   so;

struct ExitOperations
{
    ~ExitOperations() 
    { 
        output::print("Press enter to exit...");
        std::cin.get();
    }
}   eo;


#if !TEST
#define DEBUGMODE

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
    bool show_fps = Settings::show_fps();
    int current_level = 2;
}


int main()
{
    Display display(PC::WIDTH, PC::HEIGHT, PC::TITLE, PC::FULLSCREEN ? sf::Style::Fullscreen : sf::Style::Default, Main_GB::current_level);
    std::cout << glGetString(GL_VERSION) << std::endl;

    sf::Clock clock;
    float delta_time = 1.0f, current_time = 0.0f, last_time = 0.0f;

    SFEvent sfevent;

    //Enabling OpenGL stuff
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glAlphaFunc(GL_GREATER, 0.5f);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

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
#ifdef DEBUGMODE
            case sf::Event::KeyPressed:
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
                {
                    display.switch_wireframe(!wire_frame);
                    wire_frame = !wire_frame;
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
                {
                    display.restrain_camera_y(y_mov_switch);
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
            glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            display.process_mouse_movement(delta_time);

            display.process_keyboard_input(delta_time, Main_GB::collision, Main_GB::current_level);

            display.render();

            glDisable(GL_CULL_FACE);
            display.render_transparent();

            display.update();

            if(Main_GB::show_fps)
            {
                logging::log(std::to_string((1 / delta_time) * 1000), lstream::info);
            }
        }
    }
}


#else

#include "Tests.h"

int main()
{
    //test_files_write();
    test_files_read();
}

#endif