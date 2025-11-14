#ifndef CALLBACKS_HPP
#define CALLBACKS_HPP

#include <GLFW/glfw3.h>

#include <iostream>

#include "Application.hpp"

static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->screenwidth = width;
    app->screenheight = height;
    glViewport(0, 0, width, height);
}

static void window_focus_callback(GLFWwindow *window, int focussed) {}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {}

static void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos) {}

static void filepath_drop_callback(GLFWwindow *window, int count, const char **paths) {
    std::cout << "DROPPED FILEPATH(S)\n";
    std::cout << "n filepaths: " << count << "\n";

    for(int i = 0; i < count; i++) {
        std::cout << "FILEPATH: " << paths[i] << "\n";
    }

    std::cout << "\n";
}

#endif