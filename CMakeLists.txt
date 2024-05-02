cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(XenykEngine)

include(cmake/utils.cmake)

find_package(glfw3 3.3 QUIET)
add_subdirectory(libs/)
if(USE_GLFW_SYSTEM)
    set(EXPORT_TARGETS xke-core)
else()
    set(EXPORT_TARGETS xke-core glfw)
endif()

xke_add_module(core)
# xke_add_module(ecs)

