#pragma once

#include "DisplayGLFW.h"
#include "Camera.h"
#include "Level.h"


class InputHandler
{
public:
    static void init(GLFWwindow* window);

    static void update_dt(const float& dt);
    static void update_mov_speed(const int& mov_speed);
    static void update_collision(const bool& collision);
    static void switch_y_movement(const bool& y_mov);
    static void handle_input();

    static Camera m_camera;
    static bool m_constrain_pitch;

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                      int mode);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static double last_mousex;
    static double last_mousey;

    static float m_dt;
    static int m_mov_speed;

    static bool first_mouse_movement;
    static bool m_collision;

    static bool m_keys[512];

    static GLFWwindow* m_window;
};