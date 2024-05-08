file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                          ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)


add_executable(tests ${sources})
target_link_libraries(tests
    xke-core
    # xke-logger
    # xke-gl
    # xke-eng
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
