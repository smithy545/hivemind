cmake_minimum_required(VERSION 3.10)
project(society C CXX)

set(CMAKE_CXX_STANDARD 17)

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

### FMT ###
add_subdirectory(external/fmt)

### JSON ###
add_subdirectory(external/json)
add_subdirectory(external/json-schema-validator)

### GLFW (opengl window/input) ###
set(GLFW_LIB ../external/glfw/lib-vc2019/glfw3)

### GLEW (opengl types) ###
add_library(GLEW STATIC external/glew/src/glew.c)
target_link_libraries(GLEW ${OPENGL_LIBRARY})

find_package(OpenGL REQUIRED)

include_directories(
        external/json-schema-validator/src
        external/glew/include
        external/glfw/include
        external/json/include
        external/fmt/include
        external/glm
        external/cimg
        src
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLFW_LIB}
        fmt
        nlohmann_json_schema_validator
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
add_executable(society
        src/main.cpp
        src/GameRunner.cpp
        src/GameRunner.h
        src/common/SchemaEntity.cpp
        src/common/SchemaEntity.h
        src/common/Actor.h
        src/common/Stage.cpp
        src/common/Stage.h
        src/pathing/MapNode.h
        src/pathing/Pather.cpp
        src/pathing/Pather.h
        src/pathing/Map.h
        src/render/Camera.cpp
        src/render/Camera.h
        src/render/Sprite.cpp
        src/render/Sprite.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/state/GameState.cpp
        src/state/GameState.h
        src/ui/UserInterface.cpp
        src/ui/UserInterface.h
        src/ui/UIEntity.cpp
        src/ui/UIEntity.h
        src/util/RenderUtil.cpp
        src/util/RenderUtil.h
        src/util/SpriteUtil.cpp
        src/util/SpriteUtil.h
        src/util/FileUtil.cpp
        src/util/FileUtil.h
        src/world/GridMap.cpp
        src/world/GridMap.h
        src/world/WorldEntity.cpp
        src/world/WorldEntity.h
        src/world/WorldActor.cpp
        src/world/WorldActor.h
        src/world/WorldMap.h
        )
target_link_libraries(society ${ALL_LIBS})
