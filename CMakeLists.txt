cmake_minimum_required(VERSION 3.16)
project(society C CXX)
set(CMAKE_CXX_STANDARD 20)

# Check name of build and source directories. Fuck spaces amiright?
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif ()
if (CMAKE_SOURCE_DIR MATCHES " ")
    message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()
if (CMAKE_BINARY_DIR MATCHES " ")
    message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif ()

# Setup OpenGL for Linux or Mac (Darwin)
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
find_package(OpenGL REQUIRED)

set(ALL_LIBS ${OPENGL_LIBRARY})
set(ALL_INCLUDES src)

### Libs in external/ directory:
### FMT ###
add_subdirectory(external/fmt)
set(ALL_LIBS ${ALL_LIBS} fmt)
set(ALL_INCLUDES ${ALL_INCLUDES} external/fmt/include)

### JSON ###
add_subdirectory(external/json)
add_subdirectory(external/json-schema-validator)
set(ALL_LIBS ${ALL_LIBS} nlohmann_json_schema_validator)
set(ALL_INCLUDES ${ALL_INCLUDES} external/json-schema-validator/src external/json/include)

### GLFW (opengl window/input) ###
set(ALL_LIBS ${ALL_LIBS} ../external/glfw/lib-vc2017/glfw3)
set(ALL_INCLUDES ${ALL_INCLUDES} external/glfw/include)

### GLEW (opengl types) ###
add_library(GLEW STATIC external/glew/src/glew.c)
target_link_libraries(GLEW ${OPENGL_LIBRARY})
set(ALL_LIBS ${ALL_LIBS} GLEW)
set(ALL_INCLUDES ${ALL_INCLUDES} external/glew/include)

### GLM ###
set(ALL_INCLUDES ${ALL_INCLUDES} external/glm)

### CIMG ###
set(ALL_INCLUDES ${ALL_INCLUDES} external/cimg)

### Source directory libs:
### MY COMMON LIB ###
add_library(common INTERFACE)
target_sources(common INTERFACE
        ${PROJECT_SOURCE_DIR}/src/common/Body.h
        ${PROJECT_SOURCE_DIR}/src/common/LinkedNode.h
        ${PROJECT_SOURCE_DIR}/src/common/TreeNode.h
        ${PROJECT_SOURCE_DIR}/src/common/DoublyLinkedNode.h
        ${PROJECT_SOURCE_DIR}/src/common/TopologicalNode.h)
set(ALL_LIBS ${ALL_LIBS} common)

### MY COLLISION LIB ###
add_library(collision STATIC
        src/collision/QuadTree.cpp
        src/collision/QuadTree.h
        src/collision/Rectangle.cpp
        src/collision/Rectangle.h
        src/collision/Bound.h)
set(ALL_LIBS ${ALL_LIBS} collision)

### MY PATHING LIB ##
add_library(pathing STATIC
        src/pathing/GridMap.cpp
        src/pathing/GridMap.h
        src/pathing/Map.h
        src/pathing/MapNode.h
        src/pathing/Pather.cpp
        src/pathing/Pather.h)
set(ALL_LIBS ${ALL_LIBS} pathing)

### MY UTIL LIB ###
add_library(util STATIC
        src/util/FileUtil.cpp
        src/util/FileUtil.h
        src/util/MathUtil.cpp
        src/util/MathUtil.h
        src/util/RenderUtil.cpp
        src/util/RenderUtil.h
        src/util/StringUtil.cpp
        src/util/StringUtil.h
        src/util/MeshUtil.cpp
        src/util/MeshUtil.h)
set(ALL_LIBS ${ALL_LIBS} util)

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
set(ALL_LIBS ${ALL_LIBS} render)

### MY UI LIB ####
add_library(ui STATIC
        src/interface/InterfaceNode.cpp
        src/interface/InterfaceNode.h)
set(ALL_LIBS ${ALL_LIBS} ui)

### CORE ENGINE/STRUCTURES ###
add_library(engine STATIC
        src/engine/State.cpp
        src/engine/State.h
        src/engine/Interface.cpp
        src/engine/Interface.h)
add_library(world STATIC
        src/world/Person.cpp
        src/world/Person.h
        src/world/God.cpp
        src/world/God.h
        src/world/Actor.h)
set(ALL_LIBS ${ALL_LIBS} world engine)

### CUDA STUFF ###
add_subdirectory(src/cuda)
set(ALL_LIBS ${ALL_LIBS} cuda_stuff)

# Put it all together
include_directories(${ALL_INCLUDES})
link_libraries(${ALL_LIBS})
add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)
add_executable(society src/main.cpp)

# FOR DEBUGGING
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach ()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()
#print_all_variables()