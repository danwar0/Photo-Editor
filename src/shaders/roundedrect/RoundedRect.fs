#version 330 core

in vec2 centre; 
in vec2 scale;
in float corner_radius;
in vec2 pos_screenspace;

float sdf(vec2 screen_pos) {
    vec2 S = abs(scale * 0.5);
    vec2 P = abs(screen_pos - centre);
    vec2 R = S - corner_radius;
    vec2 RP = P - R;

    if(RP.x >= 0 && RP.y >= 0) return length(RP) - corner_radius; // corner area

    return -1;
}

void main() {
    float alpha = 1.0 - smoothstep(-1.0, 1.0, sdf(pos_screenspace));
    gl_FragColor = vec4(1,0,0,alpha);
}