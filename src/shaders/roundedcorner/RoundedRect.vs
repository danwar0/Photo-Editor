#version 330 core

layout (location = 0) in vec2 a_vertex;

layout (location = 1) in vec2 a_translation;
layout (location = 2) in vec2 a_scale;
layout (location = 3) in float a_corner_radius;

uniform int screen_width;
uniform int screen_height;

out vec2 centre; 
out vec2 scale;
out float corner_radius;
out vec2 pos_screenspace;

void main() {
    vec2 pos = a_vertex * a_scale + a_translation;

    centre = vec2(a_translation.x + a_scale.x*0.5, a_translation.y - a_scale.y*0.5);
    scale = a_scale;
    corner_radius = a_corner_radius;
    pos_screenspace = pos;

    pos.x = (pos.x / screen_width) * 2.0 - 1.0;
    pos.y = (pos.y / screen_height) * 2.0 - 1.0;
    gl_Position = vec4(pos, 0, 1);
}