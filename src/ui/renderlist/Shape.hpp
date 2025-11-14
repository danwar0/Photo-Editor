#ifndef UI_SHAPE_HPP
#define UI_SHAPE_HPP

namespace UI {

enum class ShapeType {
    RECTANGLE,
    CIRCLE
};

struct Shape {
    float pos[2];
    float size[2];
    float radius;
    float background_colour[4];
    //ShapeType type;
};

}

#endif