#include "Renderer.hpp"

#define UI_INSTANCE_BUFFER_SIZE 1024

Renderer::Renderer(const Application& app) : 
    app(app), 
    shape_program(std::filesystem::path(__FILE__).parent_path().string() + "/../shaders/shape/Shape") 
{
    init_shape();
    init_text();
    init_image();
}

Renderer::~Renderer() {
    if(shape_vertexbuffer != 0) glDeleteBuffers(1, &shape_vertexbuffer);
    if(shape_instancebuffer != 0) glDeleteBuffers(1, &shape_instancebuffer);
}
