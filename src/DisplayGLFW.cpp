#include "DisplayGLFW.h"
#include "OutUtils.h"
#include "Settings.h"

#ifdef _WIN32
#include <GL/wglew.h>
#include <Windows.h>
#endif

DisplayGLFW::DisplayGLFW(const uint& w, const uint& h, conststrref title,
                         const WindowStyle& style)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, Settings::multisamples());
    glfwWindowHint(GLFW_DECORATED, style == FULLSCREEN ? GLFW_FALSE : GLFW_TRUE);

    m_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if(status != GLEW_OK)
        logging::log("Failed to initialize GLEW", lstream::exception);

    glfwSetInputMode(m_window, GLFW_CURSOR, Settings::mouse_cursor_hidden() ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);

#ifdef _WIN32
    if(WGLEW_EXT_swap_control)
        wglSwapIntervalEXT(Settings::vsync_enabled());
    else
        logging::log("Failed to enable VSync - WGLEW_EXT_swap_control not supported\n" + 
                     std::string{"Continuing without VSync..."}, lstream::warning);
#else
    glfwSwapInterval(Settings::vsync_enabled());
#endif
}

DisplayGLFW::~DisplayGLFW()
{
    glfwDestroyWindow(m_window);
}

GLFWwindow& DisplayGLFW::get_instance()
{
    return *m_window;
}

void DisplayGLFW::close()
{
    glfwSetWindowShouldClose(m_window, true);
}

bool DisplayGLFW::close_requested()
{
    return glfwWindowShouldClose(m_window);
}

bool DisplayGLFW::is_active()
{
    return glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
}