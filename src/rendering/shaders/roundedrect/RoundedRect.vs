#version 330 core

layout (location = 0) in vec2 a_vertex; // origin bottom left, x right, y up

layout (location = 1) in vec2 a_translation; // origin top left, x right, y down
layout (location = 2) in vec2 a_scale;
layout (location = 3) in float a_corner_radius;

uniform int screen_width;
uniform int screen_height;

out Data {
    vec2 origin; // origin bottom left, x right, y up
    vec2 scale;
    float corner_radius;
} data_out;

void main() {
    data_out.origin = vec2(a_translation.x, screen_height - a_translation.y);
    data_out.scale = a_scale;
    data_out.corner_radius = a_corner_radius;

    vec2 pos = a_vertex*a_scale + vec2(a_translation.x, screen_height - a_translation.y);
    gl_Position = vec4(pos.x/screen_width * 2.0 - 1.0, pos.y/screen_height * 2.0 - 1.0, 0, 1);
}