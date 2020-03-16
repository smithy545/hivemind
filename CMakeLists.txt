cmake_minimum_required(VERSION 3.10)
project(society C CXX)

set(CMAKE_CXX_STANDARD 14)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif ()
if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()
if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()


# Compile external dependencies
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            -lGL -lGLU -lXrandr -lXext -lX11 -lrt
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(OPENGL_LIBRARY
            ${OPENGL_LIBRARY}
            ${CMAKE_DL_LIBS}
            ${GLFW_LIBRARIES}
            )
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLFW (opengl window/input) ###
set(GLFW_LIB ../external/glfw/lib-vc2019/glfw3)

### GLEW (opengl types) ###
add_library(GLEW STATIC external/glew/src/glew.c)
target_link_libraries(GLEW ${OPENGL_LIBRARY})

find_package(OpenGL REQUIRED)

include_directories(
        external/glew/include
        external/glfw/include
        external/json/include
        external/glm
        external/cimg
        src
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLFW_LIB}
        GLEW
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach ()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
print_all_variables()
# add exec
add_executable(society src/main.cpp src/world/Human.cpp src/world/Human.h src/world/GridMap.cpp src/world/GridMap.h src/pathing/MapNode.h src/pathing/Pather.cpp src/pathing/Pather.h src/GameRunner.cpp src/GameRunner.h src/pathing/Map.h src/world/WorldEntity.h src/world/WorldActor.h src/render/Camera.cpp src/render/Camera.h src/render/Sprite.h src/world/Structure.cpp src/world/Structure.h src/world/Prop.h src/society/Institution.cpp src/society/Institution.h src/society/BaseRole.h src/world/WorldActor.cpp src/world/WorldMap.h src/ui/UserInterface.cpp src/ui/UserInterface.h src/render/Renderer.cpp src/render/Renderer.h src/util/RenderUtil.cpp src/util/RenderUtil.h src/util/SpriteUtil.cpp src/util/SpriteUtil.h src/render/SpriteCollection.h src/util/FileUtil.cpp src/util/FileUtil.h src/society/ProductionRole.h src/society/Transaction.h src/society/ResourcePool.h src/society/Recipe.h src/society/ServiceRole.h src/society/ResourcePool.cpp src/common/Entity.h src/ui/UIEntity.cpp src/ui/UIEntity.h)
target_link_libraries(society ${ALL_LIBS})
