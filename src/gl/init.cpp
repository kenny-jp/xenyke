# include <xenyke/gl/init.hpp>
# include <xenyke/logger/debug.hpp>
# include <GLFW/glfw3.h>

XKE_NAMESPACE_BEGIN

void error_callback(int code, const char* description)
{
    xkeDebug("XKE_ERROR[{}]: {}", code, description);
}

void xkeinit(int argc, char** argv)
{
    glfwSetErrorCallback(error_callback);
    glfwInit();
}

int xkeTerminate()
{
    glfwTerminate();
    const int errorCode {glfwGetError(nullptr)};
    return errorCode;
}

XKE_NAMESPACE_END
