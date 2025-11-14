#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

#include <iostream>
#include <filesystem>

#include "../../application/Application.hpp"
#include "../shaderprogram/ShaderProgram.hpp"
#include "../../ui/renderlist/RenderList.hpp"

class Application;

class Renderer {
public:

    Renderer(const Application& app);

    ~Renderer();

    void render_ui(UI::Element *root);

private:

    void init_shape();
    void init_text();
    void init_image();

private:

    const Application& app;

    UI::RenderList render_list;

    ShaderProgram shape_program;
    unsigned int shape_vao = 0;
    unsigned int shape_vertexbuffer = 0;
    unsigned int shape_instancebuffer = 0;

};

#endif