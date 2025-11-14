#version 330 core

in Data {
    vec2 corner; // screen-space coordinates with origin at bottom-left
    float radius;
    vec4 colour;    
} data_in;

float sdf_circle() {
    return 0;
}

float sdf_rectangle() {
    return 0;
}

void main() {
    float distance = length(gl_FragCoord.xy - data_in.corner);
    float v = distance / 800.0;
    gl_FragColor = vec4(0,0,v,1);
}