#ifndef UI_SHAPE_HPP
#define UI_SHAPE_HPP

namespace UI {

enum class ShapeType {
    RECTANGLE,
    CIRCLE
};

struct Shape {

    Shape() {}
    
    Shape(float x, float y, float width, float height, float radius, float r, float g, float b, float a) {
        pos[0] = x;
        pos[1] = y;
        size[0] = width;
        size[1] = height;
        this->radius = radius;
        this->background_colour[0] = r;
        this->background_colour[1] = g;
        this->background_colour[2] = b;
        this->background_colour[3] = a;
    }

    Shape(float x, float y, float width, float height, float radius, const float background_colour[4]) {
        pos[0] = x;
        pos[1] = y;
        size[0] = width;
        size[1] = height;
        this->radius = radius;
        memcpy(this->background_colour, background_colour, 4*sizeof(float));
    }

    ~Shape() {}

    float pos[2] = {0};
    float size[2] = {0};
    float radius = 0;
    float background_colour[4] = {0};
};

}

#endif