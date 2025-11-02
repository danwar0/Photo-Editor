#include "ShaderProgram.hpp"

void ShaderProgram::set_uniform_int(const std::string& uniform_name, int value) {
    if(program_object == 0) return;
    int uniform_location = glGetUniformLocation(program_object, uniform_name.c_str());
    if(uniform_location < 0) return;
    glUniform1i(uniform_location, value);
}