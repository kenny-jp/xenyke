add_executable(tests main.cpp)
target_link_libraries(tests
    xke-core
    xke-logger
    xke-gl
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
