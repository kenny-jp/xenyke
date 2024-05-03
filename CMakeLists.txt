cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(XenykEngine)

include(cmake/utils.cmake)

find_package(glfw3 3.3 QUIET)
add_subdirectory(libs/)

xke_add_module(core)
xke_add_module(logger)
xke_add_module(gl)

target_link_libraries(xke-gl glfw)

if(USE_GLFW_SYSTEM)
    set(EXPORT_TARGETS xke-core xke-logger xke-gl)
else()
    set(EXPORT_TARGETS xke-core xke-logger xke-gl glfw)
endif()

add_executable(tests tests/main.cpp)
target_link_libraries(tests xke-core xke-logger)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
