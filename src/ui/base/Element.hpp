#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <vector>

#include "../renderlist/RenderList.hpp"

namespace UI {

class Element {
public:

    Element() {}

    ~Element() {}

    void enable() { enabled = true; }
    void disable() { enabled = false; }

    void set_position(float x, float y) { this->x = x; this->y = y; }
    void set_size(float width, float height) { this->width = width; this->height = height; }
    void set_position_and_size(float x, float y, float width, float height) { set_position(x, y); set_size(width, height); }

    float get_x() { return x; }
    float get_y() { return y; }
    float get_width() { return width; }
    float get_height() { return height; }

    virtual bool layout() = 0;
    virtual void render_init(RenderList& render_list) const = 0;

    virtual void destroy() { delete this; }

public:

    float min_width = 0, min_height = 0;

    float margin_left = 0;
    float margin_right = 0;
    float margin_top = 0;
    float margin_bottom = 0;

protected:

    bool enabled = false;

    float x = 0, y = 0;
    float width = 0, height = 0;

    float background_colour[4] = {0, 0, 0, 0}; // transparent by default

};

}

#endif