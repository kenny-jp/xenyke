# file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
#                           ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)


# add_executable(tests ${sources})
# target_link_libraries(tests
#     xke-core
#     # xke-logger
#     xke-gl
#     xke-eng
# )
include_directories(${CMAKE_SOURCE_DIR}/include)
enable_testing()

add_executable(test_EntityAllocator test_EntityAllocator.cpp)

target_link_libraries(test_EntityAllocator
    GTest::gtest_main
    xke-eng
)

include(GoogleTest)
gtest_discover_tests(test_EntityAllocator)
