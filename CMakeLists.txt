cmake_minimum_required(VERSION 3.6)
project(game)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp utility/shader.cpp utility/texture.cpp resourceManager.cpp component/spriteRenderer.cpp game.h game.cpp )
add_executable(game ${SOURCE_FILES})
target_link_libraries(game  glew32s  glfw3 gdi32 freetype soil opengl32)