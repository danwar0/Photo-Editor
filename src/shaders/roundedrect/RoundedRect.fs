#version 330 core

in vec2 centre; 
in vec2 scale;
in float corner_radius;
in vec2 pos_screenspace;

void main() {
    float rx = abs(pos_screenspace.x - centre.x);
    float ry = abs(pos_screenspace.y - centre.y);

    float distance_x1 = rx - scale.x*0.5;
    float distance_y1 = ry - scale.y*0.5;



    gl_FragColor = vec4(1,0,0,1);
}