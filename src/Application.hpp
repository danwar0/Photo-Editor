#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderprogram/ShaderProgram.hpp"

class Application {
public:

    Application() = delete;

    Application(int screen_width, int screen_height) {
        if(!glfwInit()) { std::cout << "ERROR: failed to init GLFW\n"; return; }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(screen_width, screen_height, "window title", NULL, NULL);
        if(window == NULL) {
            std::cout << "ERROR: failed to create window\n";
            glfwTerminate();
            return;
        }
    
        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "ERROR: failed to load OpenGL function pointers\n";
            glfwTerminate();
            return;
        }

        glViewport(0, 0, screen_width, screen_height);
        glClearColor(0,0,1.0f,1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        ShaderProgram program("../src/shaders/roundedcorner/RoundedRect");
        if(!program.is_valid()) {
            glfwDestroyWindow(window);
            glfwTerminate();
            return;
        }

        program.use();
        program.set_uniform_int("screen_width", screen_width);
        program.set_uniform_int("screen_height", screen_height);

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        float vertices[] = {
            0.0f, 0.0f,
            1.0f, -1.0f,
            1.0f, 0.0f,

            0.0f, 0.0f, 
            0.0f, -1.0f, 
            1.0f, -1.0f
        };

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        const int n_instances = 20;
        float instance_data[n_instances*5];

        for(int i = 0; i < n_instances; i++) {
            instance_data[i*5] = rand() % screen_width;
            instance_data[i*5+1] = rand() % screen_height;
            float w = rand() % 200;
            float h = rand() % 200;
            instance_data[i*5+2] = w;
            instance_data[i*5+3] = h;
            float min_size = w < h ? w : h;
            float max_radius = min_size * 0.4f;
            instance_data[i*5+4] = rand() % (int)max_radius;
        }
        
        unsigned int instance_vbo;
        glGenBuffers(1, &instance_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(instance_data), instance_data, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(4*sizeof(float)));
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribDivisor(1, 1);
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);

        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, n_instances);

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    ~Application() {

    }

private:

    //static 

};

#endif 