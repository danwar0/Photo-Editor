#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

#include <iostream>
#include <filesystem>

#include "shaderprogram/ShaderProgram.hpp"
#include "../ui/renderlist/RenderList.hpp"

class Renderer {
public:

    Renderer();

    ~Renderer();

    void render_ui(const UI::RenderList& render_list);

public:

    int screenwidth, screenheight;

private:

    void init_shape();
    void init_text();
    void init_image();

private:

    ShaderProgram shape_program;
    unsigned int shape_vao = 0;
    unsigned int shape_vertexbuffer = 0;
    unsigned int shape_instancebuffer = 0;

};

#endif