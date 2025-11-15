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

    renderer = new Renderer(*this);
    if(renderer == nullptr) {
        std::cout << "ERROR: failed to create renderer\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    glViewport(0, 0, initial_screenwidth, initial_screenheight);
    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    UI::HBox* root = new UI::HBox;
    root->add_child(new UI::HBox(0.6f,0.1f,0.1f,1), 2.0f);

    UI::VBox *right_side = new UI::VBox(0,0,0,1);
    right_side->add_child(new UI::VBox(0.4f,0.4f,0.4f,1));

    UI::VBox *button_box = new UI::VBox(0.2f,0.8f,0.2f,1);
    button_box->margin_left = 5.0f;
    button_box->margin_right = 5.0f;
    button_box->margin_top = 5.0f;
    button_box->margin_bottom = 5.0f;
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));
    button_box->add_child(new UI::Button(0.1f,0.1f,0.4f,1));

    right_side->add_child(button_box, 3.0f);
    root->add_child(right_side);

    double accumulated_time = 0;
    int current_frame = 0;
    int accumulate_frame_count = 10;

    while(!glfwWindowShouldClose(window)) {
        double t1 = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT);

        renderer->render_ui(root);

        glfwSwapBuffers(window);
        glfwPollEvents();

        double t2 = glfwGetTime();

        accumulated_time += t2 - t1; 
        current_frame++;

        if(current_frame >= accumulate_frame_count) {
            double fps = 1.0f / (accumulated_time / accumulate_frame_count);
            std::string title = "Photo Editor " + std::to_string((int)fps) + "fps"; 
            glfwSetWindowTitle(window, title.c_str());
            accumulated_time = 0;
            current_frame = 0;
        }
    }

    root->destroy();
}