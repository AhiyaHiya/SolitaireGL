
#include "deck_of_cards.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <expected>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>


// Create a window to display the game. Board should be 800x600
[[nodiscard]]
static auto init_window(const int32_t width, const int32_t height)
    -> std::expected< std::shared_ptr< GLFWwindow >, std::pair< std::int32_t, std::string > >
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const auto title = std::string("SolitaireGL");

    auto window_ptr = glfwCreateWindow(width,
                                       height,
                                       title.c_str(),
                                       // Windowed mode
                                       nullptr,
                                       // Not sharing resources
                                       nullptr);

    if (!window_ptr)
    {
        // Something bad happened, so get the last error code and string
        // from GLFW
        const char* error_string;
        const auto  error_code = glfwGetError(&error_string);
        return std::unexpected(
            std::make_pair(error_code, error_string != nullptr ? error_string : "Unknown error"));
    }

    auto window =
        std::shared_ptr< GLFWwindow >(window_ptr, [](GLFWwindow* ptr) { glfwDestroyWindow(ptr); });

    return window;
}

static void render_frame(std::vector< Card >& deck, std::shared_ptr< GLFWwindow > window)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Simple 2D: Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw cards as quads with textures (pseudo-code)
    for (const auto& card : deck)
    {
        if (card.face_up)
        {
            // Bind texture, draw quad at card.pos
            // Use glm for transforms: model = translate(card.pos) * scale(0.1f);
        }
    }
    glfwSwapBuffers(window.get());
}



int main()
{
    std::cout << "Starting SolitaireGL..." << std::endl;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    constexpr auto width  = 800;
    constexpr auto height = 600;
    auto           result = init_window(width, height);
    if (!result)
    {
        auto [error_code, error_string] = result.error();
        std::cerr << "GLFW Error (" << error_code << "): " << error_string << std::endl;
        glfwTerminate();
        return 1;
    }
    auto window = result.value();

    glfwMakeContextCurrent(window.get());
    const auto glew_init_result = glewInit();
    if (glew_init_result != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: "
                  << reinterpret_cast< const char* >(glewGetErrorString(glew_init_result))
                  << std::endl;
        glfwTerminate();
        return 1;
    }

    auto card_deck = init_card_deck();
    shuffle_deck(card_deck);

    while (!glfwWindowShouldClose(window.get()))
    {
        glfwPollEvents();

        render_frame(card_deck, window);
    }

    glfwTerminate();
    return 0;
}
