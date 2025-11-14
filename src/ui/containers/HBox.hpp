#ifndef HBOX_HPP
#define HBOX_HPP

#include <string.h>

#include "../base/Container.hpp"
#include "Alignment.hpp"

namespace UI {

class HBox : public Container {
public:

    HBox() {}

    ~HBox() {}

    bool layout() override {
        float ratio_count = 0;
        for(int r : ratios) ratio_count += r;

        float offset = 0;
        for(int i = 0; i < children.size(); i++) {
            Element *child = children.at(i);

            child->x = x + margin_left + offset; 
            child->y = y + margin_top; 
            child->width = ((width - (margin_left + margin_right)) / ratio_count) * ratios.at(i);
            child->height = height - (margin_top + margin_bottom); 

            if(child->width < child->min_width) return false;
            if(child->height < child->min_height) return false;

            offset += child->width;
        }

        return true;
    }

    void render_init(RenderList& render_list) const override {
        Shape s;
        s.pos[0] = x;
        s.pos[1] = y;
        s.size[0] = width;
        s.size[1] = height;
        memcpy(s.background_colour, background_colour, sizeof(float)*4);
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