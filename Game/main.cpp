
#include <GLFW/glfw3.h>

#include <cstdint>
#include <expected>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Create a window to display the game. Board should be 800x600
[[nodiscard]]
auto init_window(const int32_t width, const int32_t height) -> std::expected< std::shared_ptr< GLFWwindow >, std::pair<std::int32_t, std::string> >
{
    const auto     title  = std::string("SolitaireGL");
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
        const auto error_code = glfwGetError(&error_string);
        return std::unexpected(std::make_pair(error_code, error_string ? error_string : "Unknown error"));
    }

    auto window =
        std::shared_ptr< GLFWwindow >(window_ptr, [](GLFWwindow* ptr) { glfwDestroyWindow(ptr); });

    return window;
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
    auto window = init_window(width, height);
    if (!window)
    {
        auto [error_code, error_string] = window.error();
        std::cerr << "GLFW Error (" << error_code << "): " << error_string << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwTerminate();
    return 0;
}
