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

### Boost PP ###
add_subdirectory(external/boost/libs/preprocessor)

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
add_library(common INTERFACE)
target_sources(common INTERFACE
        ${PROJECT_SOURCE_DIR}/src/common/Body.h
        ${PROJECT_SOURCE_DIR}/src/common/LinkedNode.h
        ${PROJECT_SOURCE_DIR}/src/common/TreeNode.h
        ${PROJECT_SOURCE_DIR}/src/common/DoublyLinkedNode.h
        ${PROJECT_SOURCE_DIR}/src/common/TopologicalNode.h)

### MY COLLISION LIB ###
add_library(collision STATIC
        src/collision/QuadTree.cpp
        src/collision/QuadTree.h
        src/collision/Rectangle.cpp
        src/collision/Rectangle.h
        src/collision/CollisionNode.cpp
        src/collision/CollisionNode.h
        src/collision/Bound.h)

### MY PATHING LIB ##
add_library(pathing STATIC
        src/pathing/GridMap.cpp
        src/pathing/GridMap.h
        src/pathing/Map.h
        src/pathing/MapNode.h
        src/pathing/Pather.cpp
        src/pathing/Pather.h)

### MY UTIL LIB ###
add_library(util STATIC
        src/util/FileUtil.cpp
        src/util/FileUtil.h
        src/util/MathUtil.cpp
        src/util/MathUtil.h
        src/util/RenderUtil.cpp
        src/util/RenderUtil.h
        src/util/StringUtil.cpp
        src/util/StringUtil.h)

### MY RENDERER LIB ###
add_library(render STATIC
        src/render/Camera.cpp
        src/render/Camera.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/render/RenderNode.cpp
        src/render/RenderNode.h
        src/render/Mesh.cpp
        src/render/Mesh.h
        src/render/Drawable.h)

### MY UI LIB ####
add_library(ui STATIC
        src/interface/InterfaceNode.cpp
        src/interface/InterfaceNode.h)

### MY DYNAMICS LIB ###
add_library(dynamics STATIC
        src/collision/PhysicsBody.cpp
        src/collision/PhysicsBody.h
        src/collision/Collider.cpp
        src/collision/Collider.h
        src/collision/Integrator.cpp
        src/collision/Integrator.h)

### GAME ENGINE ###
add_library(engine STATIC
        src/engine/State.cpp
        src/engine/State.h
        src/engine/Interface.cpp
        src/engine/Interface.h)

add_library(world STATIC
        src/world/Person.cpp
        src/world/Person.h
        src/world/Role.cpp
        src/world/Role.h
        src/world/Task.cpp
        src/world/Task.h
        src/world/Resource.cpp
        src/world/Resource.h
        src/world/SuperTask.cpp
        src/world/SuperTask.h
        src/world/God.cpp
        src/world/God.h
        src/world/Actor.h)

### CUDA STUFF ###
add_subdirectory(src/cuda)

include_directories(
        external/json-schema-validator/src
        external/glew/include
        external/glfw/include
        external/json/include
        external/fmt/include
        external/glm
        external/cimg
        external/tinyxml
        external/boost
        src)

set(ALL_LIBS
        # external
        ${OPENGL_LIBRARY}
        ${GLFW_LIB}
        GLEW
        fmt
        nlohmann_json_schema_validator
        TINYXML
        # internal
        common
        collision
        pathing
        util
        render
        ui
        engine
        world
        dynamics
        cuda_stuff
        boost_preprocessor)

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
#print_all_variables()


add_executable(society src/main.cpp)
target_link_libraries(society ${ALL_LIBS})
