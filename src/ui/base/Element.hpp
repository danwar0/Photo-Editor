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

    virtual bool layout() = 0;
    virtual void render_init(RenderList& render_list) const = 0;

    virtual void destroy() { delete this; }

public:

    float x = 0, y = 0;
    float width = 0, height = 0;

    float min_width = 0, min_height = 0;

    float margin_left = 0;
    float margin_right = 0;
    float margin_top = 0;
    float margin_bottom = 0;

protected:

    bool enabled = false;

    float background_colour[4] = {0};

};

}

#endif