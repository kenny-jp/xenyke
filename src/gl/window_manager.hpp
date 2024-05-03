# ifndef XKE_GL_WINDOW_MANAGER_HPP
# define XKE_GL_WINDOW_MANAGER_HPP

# include <xenyke/gl/monitor.hpp>
# include <xenyke/gl/ext/gl.h>
# include <GLFW/glfw3.h>

XKE_NAMESPACE_BEGIN

class Window;

class WindowManager
{
public:
    WindowManager() = delete;

    XKE_NODISCARD static GLFWwindow* createWindow(int32_t width, int32_t height, const std::string& title, Window* win, bool fullscreen = false);

    static void close_callback(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height);
    static void window_size_callback(GLFWwindow* window, int32_t width, int32_t height);
    static void window_pos_callback(GLFWwindow* window, int32_t xpos, int32_t ypos);
    static void window_focus_callback(GLFWwindow* window, int32_t focused);

    static Window* getWindowInstancePtr(GLFWwindow* window);
};

XKE_NAMESPACE_END

# endif //XKE_GL_WINDOW_MANAGER_HPP
