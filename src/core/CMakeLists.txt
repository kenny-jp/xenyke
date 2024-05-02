set(XKE_HEADERS ${xke_core_public_headers} ${xke_core_private_headers})
file(GLOB_RECURSE XKE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

xke_add_library(${module} ${XKE_SOURCES} ${XKE_HEADERS})
