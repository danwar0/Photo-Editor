#ifndef UI_RENDER_LIST_HPP
#define UI_RENDER_LIST_HPP

#include <vector>

#include "Shape.hpp"
#include "Text.hpp"
#include "Image.hpp"

namespace UI {

class RenderList {
public:
    
    void clear() {
        shapes.clear();
        text.clear();
    }

public:

    std::vector<Shape> shapes;
    std::vector<Text> text;

};

}

#endif