#include "Application.hpp"

#include "Callbacks.hpp"

Application::Application(int initial_screenwidth, int initial_screenheight) : screenwidth(initial_screenwidth), screenheight(initial_screenheight) {
    if(glfwInit() != GLFW_TRUE) {
        std::cout << "ERROR: failed to init glfw\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(initial_screenwidth, initial_screenheight, "Photo Editor", NULL, NULL);
    if(window == NULL) {
        std::cout << "ERROR: failed to create window\n";
        glfwTerminate();
        return;
    }

    glfwSetWindowSizeLimits(window, 250, 250, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetDropCallback(window, filepath_drop_callback);

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: failed to load OpenGL functions (GLAD)\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    renderer = new Renderer();
    if(renderer == nullptr) {
        std::cout << "ERROR: failed to create renderer\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }
    renderer->screenwidth = screenwidth;
    renderer->screenheight = screenheight;

    glViewport(0, 0, initial_screenwidth, initial_screenheight);
    glClearColor(1, 0, 0, 1);

    UI::HBox* root = new UI::HBox;
    root->add_child(new UI::HBox, 2.0f);
    root->add_child(new UI::HBox);

    UI::RenderList render_list;

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        render_list.clear();

        root->x = 0;
        root->y = 0;
        root->width = screenwidth;
        root->height = screenheight;

        root->layout();
        root->render_init(render_list);

        renderer->render_ui(render_list);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    root->destroy();
}