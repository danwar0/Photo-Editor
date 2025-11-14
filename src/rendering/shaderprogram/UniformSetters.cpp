#include "ShaderProgram.hpp"

void ShaderProgram::set_uniform_int(const std::string& uniform_name, int value) {
    if(program_object == 0) return;
    int uniform_location = glGetUniformLocation(program_object, uniform_name.c_str());
    if(uniform_location < 0) return;
    glUniform1i(uniform_location, value);
}

void ShaderProgram::set_uniform_vec2(const std::string& uniform_name, float v0, float v1) {
    if(program_object == 0) { 
        std::cout << "ERROR: failed to set vec2 uniform because program_object = 0\n";
        return;
    }

    int uniform_location = glGetUniformLocation(program_object, uniform_name.c_str());
    if(uniform_location < 0) {
        std::cout << "ERROR: failed to set vec2 uniform because uniform_location < 0\n";
        return;    
    }

    glUniform2f(uniform_location, v0, v1);
}