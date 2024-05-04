# include <xenyke/gl/monitor.hpp>
# include <GLFW/glfw3.h>

XKE_NAMESPACE_BEGIN

class InternalMonitor
{
public:
    static void monitor_callback(GLFWmonitor *__m, int __ev)
    {
        xke::Monitor* monitor = static_cast<xke::Monitor*>(glfwGetMonitorUserPointer(__m));
        __xke_assert(monitor != nullptr);

        if (__ev == GLFW_CONNECTED) {
            monitor->isConnected_ = true;
        } else if (__ev == GLFW_DISCONNECTED) {
            monitor->isConnected_ = false;
        }
    }
};

namespace {
// void setVideoMode(VideoMode& vm, const GLFWvidmode &m) const;
auto setVideoMode = [](VideoMode &vm, const GLFWvidmode &m)->void {
    vm.width_ = m.width;
    vm.height_ = m.height;
    vm.redBits_ = m.redBits;
    vm.greenBits_ = m.greenBits;
    vm.blueBits_ = m.blueBits;
    vm.refreshRate_ = m.refreshRate;

};

// cast handle to GLFWmonitor*
auto h_cast = [](void* handle){return handle_cast<GLFWmonitor*>(handle);};

} // Anonymous namespace

Vec2f Monitor::getContentScale() const
{
    if(!isConnected_)
        return Vec2f(0, 0);

    Vec2f scale;
    glfwGetMonitorContentScale(h_cast(handle_), &scale.x, &scale.y);
    return scale;
}

Vec2i Monitor::getPosition() const
{
    if(!isConnected_)
        return Vec2i(0, 0);

    Vec2i pos;
    glfwGetMonitorPos(h_cast(handle_), &pos.x, &pos.y);
    return pos;
}

RectInt Monitor::getWorkArea() const
{
    if(!isConnected_)
        return RectInt(0, 0, 0, 0);

    RectInt rect;
    glfwGetMonitorWorkarea(h_cast(handle_), &rect.x, &rect.y, &rect.width, &rect.height);
    return rect;
}

std::string Monitor::getName() const
{
    if(!isConnected_)
        return std::string("null");

    return glfwGetMonitorName(h_cast(handle_));
}

VideoMode Monitor::getVideoMode() const
{
    VideoMode vm;
    if (isConnected_) {
        const GLFWvidmode* mode = glfwGetVideoMode(h_cast(handle_));
        setVideoMode(vm, *mode);
    }
    return vm;
}

const Monitor::VideoModeMap& Monitor::getVideoModes() const
{
    return modes_;
}

bool Monitor::isConnected() const
{
    return isConnected_;
}

std::vector<Monitor> Monitor::getMonitorsList()
{
    int32_t monitorCount;
    GLFWmonitor** glfwmonitors {glfwGetMonitors(&monitorCount)};
    std::vector<Monitor> monitors;
    for (int i {0}; i < monitorCount; ++i) {
        monitors.emplace_back(Monitor{glfwmonitors[i]});
    }
    return monitors;
}

Monitor Monitor::getPrimaryMonitor()
{
    GLFWmonitor* glfwmonitor {glfwGetPrimaryMonitor()};
    if (!glfwmonitor) {
        throw Exception("Primary monitor cannot be found.");
    }
    Monitor monitor(glfwmonitor);
    return monitor;
}

void* Monitor::getHandle() const
{
    return handle_;
}

Monitor::Monitor(void* monitor) :
    handle_(monitor)
{
    if (monitor) {
        isConnected_ = true;

        int vidModeCount;
        const GLFWvidmode* modes = glfwGetVideoModes(h_cast(handle_), &vidModeCount);

        for(int i {0}; i < vidModeCount; ++i){
            const GLFWvidmode& m = modes[i];
            const std::string widthStr = std::to_string(m.width);
            const std::string heightStr = std::to_string(m.height);

            VideoMode newMode;
            setVideoMode(newMode, m);
            modes_.insert({std::format("{}x{}", widthStr, heightStr), newMode});
        }

        glfwSetMonitorCallback(InternalMonitor::monitor_callback);
        glfwSetMonitorUserPointer(h_cast(handle_), this);
    } else {
        isConnected_ = false;
    }
}

XKE_NAMESPACE_END
