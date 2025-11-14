#include "Renderer.hpp"

#define UI_INSTANCE_BUFFER_SIZE 1024

Renderer::Renderer() : shape_program(std::filesystem::path(__FILE__).parent_path().string() + "/shaders/shape/Shape") {
    init_shape();
    init_text();
    init_image();
}

Renderer::~Renderer() {
    if(shape_vertexbuffer != 0) glDeleteBuffers(1, &shape_vertexbuffer);
    if(shape_instancebuffer != 0) glDeleteBuffers(1, &shape_instancebuffer);
}

void Renderer::init_shape() {
    float vertices[] = {
        0.0f, 0.0f, 
        1.0f, -1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, -1.0f, 
        1.0f, -1.0f
    };     

    glGenVertexArrays(1, &shape_vao);
    if(shape_vao == 0) {
        std::cout << "ERROR: failed to generate vertex array\n";
        return;
    }

    glGenBuffers(1, &shape_vertexbuffer);
    if(shape_vertexbuffer == 0) {
        std::cout << "ERROR: failed to generate vertex buffer\n";   
        return;
    }

    glGenBuffers(1, &shape_instancebuffer);
    if(shape_instancebuffer == 0) {
        std::cout << "ERROR: failed to generate instance buffer\n";
        return;
    }
    
    glBindVertexArray(shape_vao);

    glBindBuffer(GL_ARRAY_BUFFER, shape_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
    
void Renderer::init_text() {
    return;
}
    
void Renderer::init_image() {
    return;
}

void Renderer::render_ui(const UI::RenderList& render_list) {
    // shape

    if(render_list.shapes.size() > 0) {
        shape_program.use();
        shape_program.set_uniform_vec2("screen_size", screenwidth, screenheight);

        glBindVertexArray(shape_vao);

        glBindBuffer(GL_ARRAY_BUFFER, shape_instancebuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(UI::Shape)*render_list.shapes.size(), render_list.shapes.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, pos)));
        glVertexAttribDivisor(1, 1);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, size)));
        glVertexAttribDivisor(2, 1);
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, render_list.shapes.size());

        glBindVertexArray(0);
    }

    // text


    // image
}