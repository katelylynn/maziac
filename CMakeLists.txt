cmake_minimum_required(VERSION 4.1)
project(maziac)

set(CMAKE_CXX_STANDARD 20)

# Set SDL3 include and lib paths
if (WIN32)
    set(SDL3_PATH "C:/App/SDL3")
    include_directories(${SDL3_PATH}/include)
    link_directories(${SDL3_PATH}/lib)
endif ()

add_executable(maziac
        src/main.cpp
        src/Game.cpp
)

target_link_libraries(maziac
        SDL3
)
