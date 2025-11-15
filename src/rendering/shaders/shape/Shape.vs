#version 330 core 

layout (location=0) in vec2 a_vertex_pos; // NDC

layout (location=1) in vec2 a_translate; // standard UI screen-space coordinates
layout (location=2) in vec2 a_scale; // standard UI screen-space coordinates
layout (location=3) in float a_radius; // standard UI screen-space coordinates
layout (location=4) in vec4 a_colour;

uniform vec2 screen_size;

out vec2 corner; // screen-space coordinates with origin at bottom-left
out vec2 size;
out float radius;
out vec4 colour;

void main() {
    float x = a_vertex_pos.x * a_scale.x + (a_translate.x / screen_size.x) * 2.0 - 1.0;
    float y = a_vertex_pos.y * a_scale.y + (1.0 - (a_translate.y / screen_size.y)) * 2.0 - 1.0;
    gl_Position = vec4(x, y, 0, 1);  

    corner = vec2(a_translate.x, screen_size.y-a_translate.y);
    size = a_scale;
    radius = a_radius;
    colour = a_colour;
}