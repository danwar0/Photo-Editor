#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../ui/UI.hpp"
#include "../rendering/renderer/Renderer.hpp"

class Renderer;

class Application {
public:

    Application() = delete;

    Application(int initial_screenwidth, int initial_screenheight);

    ~Application() {}

    //void main_loop();

public:

    Renderer *renderer = nullptr;
    int screenwidth, screenheight;

private:

    GLFWwindow *window = NULL;

};

#endif 