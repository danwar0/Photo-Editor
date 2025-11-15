#ifndef UI_HBOX_HPP
#define UI_HBOX_HPP

#include <string.h>

#include "../base/Container.hpp"
#include "Alignment.hpp"

namespace UI {

class HBox : public Container {
public:

    HBox() {}

    HBox(float r, float g, float b, float a) {
        background_colour[0] = r;
        background_colour[1] = g;
        background_colour[2] = b;
        background_colour[3] = a;
    }

    ~HBox() {}

    bool layout() override {
        float ratio_count = 0;
        for(int r : ratios) ratio_count += r;

        float offset = 0;
        for(int i = 0; i < children.size(); i++) {
            Element *child = children.at(i);

            child->set_position(x + margin_left + offset, y + margin_top);
            child->set_size(((width - (margin_left + margin_right)) / ratio_count) * ratios.at(i), height - (margin_top + margin_bottom));

            if(child->get_width() < child->min_width) return false;
            if(child->get_height() < child->min_height) return false;

            if(!child->layout()) return false;

            offset += child->get_width();
        }

        return true;
    }

    void render_init(RenderList& render_list) const override {
        Shape s(x, y, width, height, 0.0f, background_colour);
        render_list.shapes.push_back(s);
        for(Element *child : children) child->render_init(render_list);
    }

    void add_child(Element *child) override { children.push_back(child); ratios.push_back(1.0f); }
    void add_child(Element *child, float ratio) { children.push_back(child); ratios.push_back(ratio); }

    void clear_children() override { children.clear(); ratios.clear(); }

private:

    std::vector<int> ratios;

};

}

#endif 