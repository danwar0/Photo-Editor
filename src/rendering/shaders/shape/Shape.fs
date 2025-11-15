#version 330 core

in vec2 corner; // screen-space coordinates with origin at bottom-left
in vec2 size;
in float radius;
in vec4 colour;    

float sdf_circle() {
    return 0;
}

float sdf_rectangle(vec2 pos) {
    float x = clamp(pos.x, corner.x + radius, corner.x + size.x - radius);
    float y = clamp(pos.y, corner.y - size.y + radius, corner.y - radius);
    return length(pos - vec2(x, y)) - radius;
}

void main() {
    float t = 1.0 - smoothstep(-1.0, 1.0, sdf_rectangle(gl_FragCoord.xy));
    gl_FragColor = mix(vec4(0,0,0,0), colour, t);
}