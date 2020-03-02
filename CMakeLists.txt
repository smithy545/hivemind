cmake_minimum_required(VERSION 3.10)
project(society)

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
        external/glfw-3.1.2/include
        external/glm
        external/glew-1.13.0/include
        external/assimp-3.0.1270/include
        external/fmt-master/include
        external/json/include
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
add_executable(society src/main.cpp src/world/Human.cpp src/world/Human.h src/world/GridMap.cpp src/world/GridMap.h src/pathing/MapNode.h src/pathing/Pather.cpp src/pathing/Pather.h src/GameRunner.cpp src/GameRunner.h src/pathing/Map.h src/world/WorldEntity.h src/world/WorldActor.h src/render/Camera.cpp src/render/Camera.h src/render/Mesh.h src/world/Structure.cpp src/world/Structure.h src/world/Prop.cpp src/world/Prop.h src/society/Institution.cpp src/society/Institution.h src/society/BaseRole.h src/world/WorldActor.cpp src/world/WorldMap.h src/ui/UserInterface.cpp src/ui/UserInterface.h src/render/Renderer.cpp src/render/Renderer.h src/util/RenderUtil.cpp src/util/RenderUtil.h src/util/MeshUtil.cpp src/util/MeshUtil.h src/render/MeshObject.h src/util/FileUtil.cpp src/util/FileUtil.h)
target_link_libraries(society
        ${ALL_LIBS}
        )
