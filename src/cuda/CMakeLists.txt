cmake_minimum_required(VERSION 3.16)
project(cuda_stuff CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_library(cuda_stuff main.cu)
set(CUDA_LIBS_DIRECTORY "C:/Program\ Files/NVIDIA\ GPU\ Computing\ Toolkit/CUDA/v10.2/lib/x64")
target_link_libraries(cuda_stuff ${CUDA_LIBS_DIRECTORY}/cudart.lib)
set_target_properties(
        cuda_stuff
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
        CUDA_RESOLVE_DEVICE_SYMBOLS ON)