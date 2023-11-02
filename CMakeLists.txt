cmake_minimum_required(VERSION 3.23)
project(Playground)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCES main.cpp Shader.cpp Text.cpp object.cpp Button.cpp)

add_executable(Playground ${PROJECT_SOURCES})

find_package(Freetype REQUIRED)

target_link_libraries(Playground -lfreeglut -lglew32 -lopengl32 -lglfw3 Freetype::Freetype)
