
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
    std::cout << "Hello, Solitaire!\n";
    if (!glfwInit()) { exit(1); }
    return 0;
}
