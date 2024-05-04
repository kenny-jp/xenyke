# ifndef XKE_GL_WINDOW_HPP
# define XKE_GL_WINDOW_HPP

# include <xenyke/core/color.hpp>
# include <xenyke/core/rect.hpp>
# include <xenyke/core/vec.hpp>

XKE_NAMESPACE_BEGIN

class Window
{
public:
    Window(int32_t width, int32_t height, const std::string& title, bool fullscreen = false);
    virtual ~Window();
    void create(int32_t width, int32_t height, const std::string& title, bool fullscreen = false);

    Vec2i getPosition() const;
    Vec2u getSize() const;
    std::string getTitle() const;

    void setPosition(const Vec2i& pos);
    void setSize(const Vec2u& size);
    void setTitle(const std::string& title);

    void display();
    void clear(const Color& backgroundColor);
    void close();
    bool isOpen() const;

    handle_t getHandle();

    static Window* getStaticWindow();

protected:
    virtual void closeEvent();
    virtual void framebufferResizeEvent(const RectInt& rect);

    virtual void resizeEvent(int width, int height) {}
    virtual void moveEvent(int xpos, int ypos) {}
    virtual void focusInEvent() {}
    virtual void focusOutEvent() {}

    handle_t handle_;

    friend class WindowManager;
};

XKE_NAMESPACE_END

# endif //XKE_GL_WINDOW_HPP
