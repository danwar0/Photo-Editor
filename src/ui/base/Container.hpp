#ifndef UI_CONTAINER_HPP
#define UI_CONTAINER_HPP

#include <vector>

#include "Element.hpp"

namespace UI {

class Container : public Element {
public:

    Container() {}

    ~Container() {}

    virtual void add_child(Element *child) { children.push_back(child); }
    virtual void clear_children() { children.clear(); }

    void destroy() override {
        for(Element *child : children) child->destroy();
        delete this;
    }

protected:

    std::vector<Element*> children;

};

}

#endif