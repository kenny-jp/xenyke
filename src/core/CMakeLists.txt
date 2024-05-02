set(XKE_HEADERS ${xke_${module}_public_headers} ${xke_${module}_private_headers})
file(GLOB_RECURSE XKE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

xke_add_library(${module} ${XKE_SOURCES} ${XKE_HEADERS})
