cmake_minimum_required(VERSION 3.24)
project(Solitaire LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)
find_package(glfw3  CONFIG REQUIRED)
find_package(GLEW REQUIRED)

add_executable(solitaire
    Game/deck_of_cards.cpp
    Game/deck_of_cards.hpp
    Game/main.cpp
)

target_link_libraries(solitaire
    PRIVATE
        glfw
        GLEW::GLEW
        OpenGL::GL
)

install(TARGETS solitaire
    RUNTIME DESTINATION bin
)
