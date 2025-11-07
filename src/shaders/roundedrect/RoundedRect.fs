#version 330 core

in Data {
    vec2 origin; // origin bottom left, x right, y up
    vec2 scale;
    float corner_radius;
} data_in;

float sdf(vec2 screen_pos) {
    float x = clamp(screen_pos.x, data_in.origin.x + data_in.corner_radius, data_in.origin.x + data_in.scale.x - data_in.corner_radius);
    float y = clamp(screen_pos.y, data_in.origin.y - data_in.scale.y + data_in.corner_radius, data_in.origin.y - data_in.corner_radius);
    vec2 P = vec2(x, y);
    return length(screen_pos - P) - data_in.corner_radius;
}

void main() {
    float alpha = 1.0 - smoothstep(-1.0, 1.0, sdf(gl_FragCoord.xy));
    gl_FragColor = vec4(0.4,0.4,0.4,alpha);
}