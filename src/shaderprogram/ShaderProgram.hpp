#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <iostream>
#include <glad/glad.h>

class ShaderProgram {
public:

    ShaderProgram() = delete;
    ~ShaderProgram();

    ShaderProgram(const std::string& vertex_and_fragment_shader_filepath);
    ShaderProgram(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath);

    ShaderProgram(const ShaderProgram& other);
    ShaderProgram(ShaderProgram&& other) noexcept;

    ShaderProgram& operator=(const ShaderProgram& other);
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    bool is_valid() const;

    void use() const;

    unsigned int get_id() const;

    void set_uniform_int(const std::string& uniform_name, int value);

private:

    unsigned int program_object = 0;
    unsigned int *program_object_instance_count = nullptr;

};

#endif