cmake_minimum_required(VERSION 3.10)
project(hivemind)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


# Compile external dependencies
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
#cmake_policy(SET CMP0026 OLD)
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
#include(CreateLaunchers)
#include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
    add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

include_directories(
        external/AntTweakBar-1.16/include
        external/glfw-3.1.2/include
        external/glm
        external/glew-1.13.0/include
        external/assimp-3.0.1270/include
        external/fmt-master/include
        external/bullet-2.81-rev2613/src
        .
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        fmt
        glfw
        GLEW_1130
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)


# add exec
add_executable(hivemind src/main.cpp src/Human.cpp src/Human.h src/GridMap.cpp src/GridMap.h src/MapNode.h src/Pather.cpp src/Pather.h src/GameRunner.cpp src/GameRunner.h src/Map.h src/VisionMap.cpp src/VisionMap.h src/MapPosition.h src/MapEntity.h src/MapActor.h src/Camera.cpp src/Camera.h src/Mesh.h src/Structure.cpp src/Structure.h src/Prop.cpp src/Prop.h src/Institution.cpp src/Institution.h src/BaseRole.h src/GroundNode.h src/StructureNode.h src/StructureNode.cpp src/MapActor.cpp src/WorldMap.h)
target_link_libraries(hivemind
        ${ALL_LIBS}
        )
