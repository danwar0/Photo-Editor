#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include "../base/Element.hpp"

namespace UI {

class Button : public Element {
public:

    Button() {}

    Button(float r, float g, float b, float a) {
        background_colour[0] = r;
        background_colour[1] = g;
        background_colour[2] = b;
        background_colour[3] = a;
    }

    ~Button() {}

    bool layout() override {
        return true;
    }

    void render_init(RenderList& render_list) const override {
        Shape s(x, y, width, height, 10.0f, background_colour);
        render_list.shapes.push_back(s);
    }

private:

};

}

#endif