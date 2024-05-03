# include "window_manager.hpp"
# include <xenyke/gl/window.hpp>

XKE_NAMESPACE_BEGIN

    namespace {
    // cast handle to GLFWwindow*
    static constexpr auto h_cast = [](void* handle){return handle_cast<GLFWwindow*>(handle);};
}

Window::~Window()
{
}

void Window::create(int32_t width, int32_t height, const std::string& title, bool fullscreen)
{
    handle_ = WindowManager::createWindow(width, height, title, this, fullscreen);
}

Vec2i Window::getPosition() const
{
    int32_t xpos, ypos;

    glfwGetWindowPos(h_cast(handle_), &xpos, &ypos);

    return Vec2i(xpos, ypos);
}

Vec2u Window::getSize() const
{
    int32_t width, height;

    glfwGetWindowSize(h_cast(handle_), &width, &height);

    return Vec2u(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

std::string Window::getTitle() const
{
    return glfwGetWindowTitle(h_cast(handle_));
}

void Window::setPosition(const Vec2i& pos)
{
    glfwSetWindowPos(h_cast(handle_), pos.x, pos.y);
}

void Window::setSize(const Vec2u& size)
{
    glfwSetWindowSize(h_cast(handle_),
                      static_cast<int>(size.x),
                      static_cast<int>(size.y));
}

void Window::setTitle(const std::string& title)
{
    glfwSetWindowTitle(h_cast(handle_), title.c_str());
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(h_cast(handle_));
}

handle_t Window::getHandle()
{
    return handle_;
}

XKE_NAMESPACE_END
