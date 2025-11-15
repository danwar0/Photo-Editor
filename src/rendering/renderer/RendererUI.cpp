#include "Renderer.hpp"

void Renderer::render_ui(UI::Element *root) {
    if(root == nullptr) return;

    root->set_position_and_size(0, 0, app.screenwidth, app.screenheight);
    root->layout();

    render_list.clear();
    root->render_init(render_list);

    // shape

    if(render_list.shapes.size() > 0) {
        shape_program.use();
        shape_program.set_uniform_vec2("screen_size", app.screenwidth, app.screenheight);

        glBindVertexArray(shape_vao);

        glBindBuffer(GL_ARRAY_BUFFER, shape_instancebuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(UI::Shape)*render_list.shapes.size(), render_list.shapes.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, pos)));
        glVertexAttribDivisor(1, 1);
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, size)));
        glVertexAttribDivisor(2, 1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, radius)));
        glVertexAttribDivisor(3, 1);
        glEnableVertexAttribArray(3);

        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(UI::Shape), (void*)(offsetof(UI::Shape, background_colour)));
        glVertexAttribDivisor(4, 1);
        glEnableVertexAttribArray(4);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, render_list.shapes.size());

        glBindVertexArray(0);
    }

    // text

    // image

    // menu bar

}
