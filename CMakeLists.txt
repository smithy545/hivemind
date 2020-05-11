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

### XML ###
add_library(TINYXML STATIC external/tinyxml/tinystr.cpp external/tinyxml/tinyxml.cpp external/tinyxml/tinyxmlerror.cpp external/tinyxml/tinyxmlparser.cpp)
target_include_directories(TINYXML PUBLIC external/tinyxml)

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

### MY COMMON LIB ###
add_library(common
        src/common/SchemaObject.cpp
        src/common/SchemaObject.h)

### MY PATHING LIB ##
add_library(pathing src/pathing/GridNode.cpp
        src/pathing/GridNode.h
        src/pathing/Pather.cpp
        src/pathing/Pather.h
        src/pathing/Map.h
        src/pathing/GridMap.cpp
        src/pathing/GridMap.h
        src/pathing/MapNode.h
        src/pathing/TopologicalNode.h)

### MY UTIL LIB ###
add_library(util STATIC
        src/util/RenderUtil.cpp
        src/util/RenderUtil.h
        src/util/FileUtil.cpp
        src/util/FileUtil.h)

### MY RENDERER LIB ###
add_library(renderer STATIC
        src/render/Camera.cpp
        src/render/Camera.h
        src/render/Sprite.cpp
        src/render/Sprite.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/render/RenderNode.cpp
        src/render/RenderNode.h
        src/render/RenderEntity.cpp
        src/render/RenderEntity.h)
target_link_libraries(renderer util)

### MY COLLISION LIB ###
add_library(collision STATIC
        src/collision/QuadTree.cpp
        src/collision/QuadTree.h
        src/collision/Rectangle.cpp
        src/collision/Rectangle.h)

include_directories(
        external/json-schema-validator/src
        external/glew/include
        external/glfw/include
        external/json/include
        external/fmt/include
        external/glm
        external/cimg
        external/tinyxml
        src)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        ${GLFW_LIB}
        fmt
        nlohmann_json_schema_validator
        GLEW
        TINYXML
        common
        util
        renderer
        pathing
        collision)

include_directories(
        external/json-schema-validator/src
        external/glew/include
        external/glfw/include
        external/json/include
        external/fmt/include
        external/glm
        external/cimg
        external/tinyxml
        src
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


add_executable(society
        src/main.cpp
        src/GameState.cpp
        src/GameState.h
        src/GameRunner.cpp
        src/GameRunner.h
        src/UserInterface.cpp
        src/UserInterface.h
        src/PhysicsCollider.cpp
        src/PhysicsCollider.h
        src/WorldMap.cpp
        src/WorldMap.h src/PhysicsIntegrator.cpp src/PhysicsIntegrator.h)
target_link_libraries(society ${ALL_LIBS})
