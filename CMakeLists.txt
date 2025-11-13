cmake_minimum_required(VERSION 4.1.2)
project(SolitaireDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg will set these targets automatically
find_package(OpenGL REQUIRED)
find_package(glfw3  CONFIG REQUIRED)
find_package(GLEW   CONFIG REQUIRED)
find_package(glm    CONFIG REQUIRED)

add_executable(solitaire Game/main.cpp)
target_link_libraries(solitaire
    OpenGL::GL
    glfw
    GLEW::GLEW
    glm::glm
)
