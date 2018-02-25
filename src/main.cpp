#include "Settings.h"
#include "DisplayGLFW.h"
#include "SFEvent.h"
#include "Vec2.h"
#include "OutUtils.h"
#include "Maths.h"
#include "Timer.h"
#include "RenderGame.h"
#include "InputHandler.h"

#include <iostream>

#define TEST 0

struct StartupOperations
{
    StartupOperations() 
    {
        //std::ios::sync_with_stdio(false); 
        output::print("Starting...");
        glfwInit();
    }
}   so;

struct ExitOperations
{
    ~ExitOperations() 
    {
        output::print("Press enter to exit...");
        std::cin.get();
        glfwTerminate();
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
    uint WIDTH = Settings::width();
    uint HEIGHT = Settings::height();
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
    DisplayGLFW display {PC::WIDTH, PC::HEIGHT, PC::TITLE, PC::FULLSCREEN ? FULLSCREEN : WINDOWED};
    InputHandler::init(&display.get_instance());
    RenderGame render_game {PC::WIDTH, PC::HEIGHT, Main_GB::current_level, InputHandler::m_camera};
    InputHandler::m_camera.current_level = render_game.m_levels[Main_GB::current_level];

    float delta_time;
    float current_time;
    float last_time {0.0f};

    //Enabling OpenGL stuff
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
    glAlphaFunc(GL_GREATER, 0.5f);
    //glDepthFunc(GL_LESS);
    //glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);

    glEnable(GL_MULTISAMPLE);

    //glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);

    while(!display.close_requested())
    {
        current_time = (float)glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;

        render_game.set_deltatime(delta_time);
        render_game.update_camera_pos(InputHandler::m_camera.position);

        InputHandler::update_dt(delta_time);

        if(!out_of_focus)
        {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

            InputHandler::handle_input();

            render_game.render(InputHandler::m_camera);

            glDisable(GL_CULL_FACE);
            render_game.render_transparent();

            if(Main_GB::show_fps)
            {
                output::print("FPS: " + std::to_string((1.0f / delta_time)));
            }

            glfwPollEvents();
        }

        glfwSwapBuffers(&display.get_instance());
    }
}


#else

#include "Tests.h"

int main()
{
    //ptest_files_write();
    //ptest_files_read();
    //test_files_multiple_read();
    //test_files_read_line();
}

#endif