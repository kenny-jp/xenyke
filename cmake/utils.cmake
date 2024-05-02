function(xke_check_headers module)
    set(include_dir ${CMAKE_SOURCE_DIR}/include)
    set(include_module_path ${include_dir}/xenyke/${module})

    file(GLOB_RECURSE headers
        LIST_DIRECTORIES false
        ${include_module_path}/*.hpp
        ${include_module_path}/*.h
        ${include_module_path}/*.inl
    )

    if(headers)
        set(xke_${module}_headers ${headers})
        message(STATUS "XKE ${module} headers:")
        foreach(h ${headers})
            message(${h})
        endforeach()
    endif()

    unset(headers)

    set(include_dir ${CMAKE_SOURCE_DIR}/src/)
    set(include_module_path ${include_dir}/${module})
    file(GLOB_RECURSE headers
        LIST_DIRECTORIES false
        ${include_module_path}/*.hpp
        ${include_module_path}/*.h
        ${include_module_path}/*.inl
    )

    if(headers)
        set(xke_${module}_internals_headers ${headers})
        message(STATUS "XKE ${module} internals headers:")
        foreach(h ${headers})
            message(${h})
        endforeach()
    endif()


    set(xke_${module}_public_headers ${xke_${module}_headers} PARENT_SCOPE)
    set(xke_${module}_private_headers ${xke_${module}_internals_headers} PARENT_SCOPE)

endfunction()

function(xke_add_library module)
    set(SOURCES ${ARGN})
    if(SOURCES)
        add_library(xke-${module} ${SOURCES})
        set_target_properties(xke-${module}
            PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 20
            INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include/
        )
    endif()
endfunction()

function(xke_add_module module)
    xke_check_headers(${module})

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${module}/CMakeLists.txt)
        add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/${module})
    endif()

endfunction()
