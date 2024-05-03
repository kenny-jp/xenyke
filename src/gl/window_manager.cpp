# include "window_manager.hpp"
# include <xenyke/gl/window.hpp>

XKE_NAMESPACE_BEGIN

XKE_NODISCARD  GLFWwindow* WindowManager::createWindow(int32_t width, int32_t height, const std::string& title, Window* win, bool fullscreen)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    GLFWwindow* window = nullptr;

    if (fullscreen) {
        const Monitor& monitor = Monitor::getPrimaryMonitor();
        VideoMode vidmod = monitor.getVideoMode();
        glfwWindowHint(GLFW_RED_BITS,   vidmod.redBits_);
        glfwWindowHint(GLFW_GREEN_BITS, vidmod.greenBits_);
        glfwWindowHint(GLFW_BLUE_BITS,  vidmod.blueBits_);
        glfwWindowHint(GLFW_REFRESH_RATE,  vidmod.refreshRate_);

        window = glfwCreateWindow(width, height, title.c_str(), handle_cast<GLFWmonitor*>(monitor.getHandle()), nullptr);
    } else {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    __xke_assert(window != nullptr, "Failed to create window");

    glfwSetWindowUserPointer(window, win);

    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        glfwDestroyWindow(window);
        throw Exception("Failed to initialize OpenGL context.");
    }

    glfwSwapInterval(1);

    glfwSetWindowCloseCallback(window, WindowManager::close_callback);
    glfwSetFramebufferSizeCallback(window, WindowManager::framebuffer_size_callback);
    glfwSetWindowSizeCallback(window, WindowManager::window_size_callback);
    glfwSetWindowPosCallback(window, WindowManager::window_pos_callback);
    glfwSetWindowFocusCallback(window, WindowManager::window_focus_callback);

    return window;
}

void WindowManager::close_callback(GLFWwindow *window)
{
    getWindowInstancePtr(window)->closeEvent();
}

void WindowManager::framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
{
    getWindowInstancePtr(window)->framebufferResizeEvent(width, height);
}

void WindowManager::window_size_callback(GLFWwindow* window, int32_t width, int32_t height)
{
    getWindowInstancePtr(window)->resizeEvent(width, height);
}

void WindowManager::window_pos_callback(GLFWwindow* window, int32_t xpos, int32_t ypos)
{
    getWindowInstancePtr(window)->moveEvent(xpos, ypos);
}

void WindowManager::window_focus_callback(GLFWwindow* window, int32_t focused)
{
    if(focused)
        getWindowInstancePtr(window)->focusInEvent();
    else
        getWindowInstancePtr(window)->focusOutEvent();

}

Window* WindowManager::getWindowInstancePtr(GLFWwindow* window)
{
    return static_cast<Window*>(glfwGetWindowUserPointer(window));
}

XKE_NAMESPACE_END
