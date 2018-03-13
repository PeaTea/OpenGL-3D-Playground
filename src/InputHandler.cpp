#include "InputHandler.h"
#include "BasicRenderer.h"


Camera      InputHandler::m_camera;
double      InputHandler::last_mousex;
double      InputHandler::last_mousey;
float       InputHandler::m_dt;
int         InputHandler::m_mov_speed;
bool        InputHandler::m_constrain_pitch = true;
bool        InputHandler::m_collision = true;
bool        InputHandler::first_mouse_movement = true;
bool        InputHandler::m_keys[512];
GLFWwindow* InputHandler::m_window;

void InputHandler::init(GLFWwindow* window)
{
    m_window = window;
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void InputHandler::update_dt(const float& dt)
{
    m_dt = dt;
}

void InputHandler::update_mov_speed(const int& mov_speed)
{
    m_mov_speed = mov_speed;
}

void InputHandler::update_collision(const bool& collision)
{
    m_collision = collision;
}

void InputHandler::switch_y_movement(const bool& y_mov)
{
    m_camera.y_movement = y_mov;
}

void InputHandler::handle_input()
{
    float v = m_collision ? 10 : 30;

    if(m_keys[GLFW_KEY_W])
    {
        m_camera.process_keyboard(FORWARD, m_dt, m_collision, v);
    }
    if(m_keys[GLFW_KEY_A])
    {
        m_camera.process_keyboard(LEFT, m_dt, m_collision, v);
    }
    if(m_keys[GLFW_KEY_S])
    {
        m_camera.process_keyboard(BACKWARD, m_dt, m_collision, v);
    }
    if(m_keys[GLFW_KEY_D])
    {
        m_camera.process_keyboard(RIGHT, m_dt, m_collision, v);
    }
    if(m_keys[GLFW_KEY_SPACE])
    {
        m_camera.process_keyboard(UP, m_dt, m_collision, v);
    }
    if(m_keys[GLFW_KEY_LEFT_SHIFT])
    {
        m_camera.process_keyboard(DOWN, m_dt, m_collision, v);
    }
}


void InputHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    static bool wireframe_switch = false;
    static bool speed_switch = false;

    // Only Executes this once, even if key is being pressed constantly
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, true);
    }
    if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        BasicRenderer::switch_wireframe_mode(wireframe_switch = !wireframe_switch);
    }
    if(key == GLFW_KEY_F2 && action == GLFW_PRESS)
    {
        m_camera.y_movement = !m_camera.y_movement;
        m_collision = !m_collision;
    }
    if(key == GLFW_KEY_F3 && action == GLFW_PRESS)
    {
        m_camera.mouse_sensitivity = (speed_switch = !speed_switch) ? 0.001 : 0.1;
        m_camera.movement_speed = (speed_switch) ? 1.0f : 100.0f;
    }

    if(action == GLFW_PRESS)
    {
        m_keys[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        m_keys[key] = false;
    }
}

void InputHandler::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(first_mouse_movement)
    {
        last_mousex = xpos;
        last_mousey = ypos;
        first_mouse_movement = false;
    }

    float xoffset = (float)(xpos - last_mousex);
    float yoffset = (float)(ypos - last_mousey);

    last_mousex = xpos;
    last_mousey = ypos;

    m_camera.process_mouse_movement(xoffset, -yoffset, m_constrain_pitch);
}

void InputHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_camera.process_mouse_scrolling(xoffset, yoffset);
}