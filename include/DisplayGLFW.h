#pragma once

#include <GL/glew.h>
#include <glfw3.h>
#include "Types.h"

enum WindowStyle
{
    FULLSCREEN,
    WINDOWED
};

class DisplayGLFW
{
public:
    DisplayGLFW(const uint& w, const uint& h, conststrref title,
                const WindowStyle& style);
    ~DisplayGLFW();

    GLFWwindow& get_instance();
    void close();
    
    bool close_requested();
    bool is_active();

private:
    GLFWwindow* m_window;
};
