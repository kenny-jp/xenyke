# ifndef XKE_GL_MONITOR_HPP
# define XKE_GL_MONITOR_HPP

# include <xenyke/gl/fwd.hpp>
# include <map>
# include <vector>

XKE_NAMESPACE_BEGIN

class Monitor
{
    // Delete default ctor and copy ctors
    explicit Monitor() = delete;
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

public:
    using VideoModeMap = std::map<std::string, VideoMode>;

    // Default move ctors
    Monitor(Monitor&&) noexcept = default;
    Monitor& operator=(Monitor&&) noexcept = default;
    // Default destructor
    ~Monitor() noexcept = default;

    Vec2f getContentScale() const;
    void* getHandle() const;
    std::string getName() const;
    Vec2i getPosition() const;
    VideoMode getVideoMode() const;
    const VideoModeMap& getVideoModes() const;
    RectInt getWorkArea() const;

    bool isConnected() const;

    XKE_NODISCARD static std::vector<Monitor> getMonitorsList();
    XKE_NODISCARD static Monitor getPrimaryMonitor();

private:
    // ctor for Application class
    Monitor(void* monitor = nullptr);

    void* handle_;
    VideoModeMap modes_;
    bool isConnected_;

    friend class InternalMonitor;
};

XKE_NAMESPACE_END

# endif //XKE_GL_MONITOR_HPP
