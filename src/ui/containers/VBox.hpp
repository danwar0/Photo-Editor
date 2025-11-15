#ifndef UI_VBOX_HPP
#define UI_VBOX_HPP

#include <string.h>

#include "../base/Container.hpp"
#include "Alignment.hpp"

namespace UI {

class VBox : public Container {
public:

    VBox() {}

    VBox(float r, float g, float b, float a) {
        background_colour[0] = r;
        background_colour[1] = g;
        background_colour[2] = b;
        background_colour[3] = a;
    }

    ~VBox() {}

    bool layout() override {
        float ratio_count = 0;
        for(int r : ratios) ratio_count += r;

        float offset = 0;
        for(int i = 0; i < children.size(); i++) {
            Element *child = children.at(i);

            child->set_position(x + margin_left, y + margin_top + offset);
            child->set_size(width - (margin_left + margin_right), ((height - (margin_top + margin_bottom)) / ratio_count) * ratios.at(i));

            if(child->get_width() < child->min_width) return false;
            if(child->get_height() < child->min_height) return false;

            if(!child->layout()) return false;

            offset += child->get_height();
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