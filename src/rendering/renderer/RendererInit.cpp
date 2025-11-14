#include "Renderer.hpp"

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