#include "ShaderProgram.hpp"

#include <string>
#include <streambuf>
#include <fstream>

#define INFO_LOG_BUFFER_SIZE 512

unsigned int load_shader(const std::string& shader_filepath, GLenum shader_type) {
    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: loading shader: \"" << shader_filepath << "\"...\n";
    std::cout << "MESSAGE: opening shader file: \"" << shader_filepath << "\"...\n";
    #endif

    std::ifstream filestream(shader_filepath, std::ios::binary);
    if(!filestream) { std::cout << "ERROR: failed to open shader file: \"" << shader_filepath << "\"\n"; return 0; }

    std::string shader_string((std::istreambuf_iterator<char>(filestream)), std::istreambuf_iterator<char>());
    const char *shader_c_string = shader_string.c_str();

    filestream.close();

    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: succesfully loaded shader file: \"" << shader_filepath << "\"" << " into c style string\n";
    std::cout << "MESSAGE: creating shader object...\n";
    #endif

    unsigned int shader_object = glCreateShader(shader_type);
    if(shader_object == 0) { std::cout << "ERROR: failed to load shader: \"" << shader_filepath << "\" -> OpenGL failed to create shader object\n"; return 0; }

    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: setting shader source...\n";
    #endif

    glShaderSource(shader_object, 1, &shader_c_string, NULL);

    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: compiling shader...\n";
    #endif

    glCompileShader(shader_object);

    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: checking shader compilation success...\n";
    #endif

    int success;
    glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);
    if(!success) {
        char info_log[INFO_LOG_BUFFER_SIZE];
        glGetShaderInfoLog(shader_object, INFO_LOG_BUFFER_SIZE, NULL, info_log);
        std::cout << "ERROR: failed to compile shader: \"" << shader_filepath << "\" -> " << info_log << "\n";
        glDeleteShader(shader_object);
        return 0;
    }

    #ifdef SHADER_DEBUG
    std::cout << "MESSAGE: successfully loaded and compiled shader: \"" << shader_filepath << "\"\n";
    #endif

    return shader_object;
}

ShaderProgram::ShaderProgram(const std::string& vertex_and_fragment_shader_filepath) : 
    ShaderProgram(vertex_and_fragment_shader_filepath + ".vs", vertex_and_fragment_shader_filepath + ".fs") {}

ShaderProgram::ShaderProgram(const std::string& vertex_shader_filepath, const std::string& fragment_shader_filepath) {
    unsigned int vertex_shader_object = load_shader(vertex_shader_filepath, GL_VERTEX_SHADER);
    if(vertex_shader_object == 0) return;

    unsigned int fragment_shader_object = load_shader(fragment_shader_filepath, GL_FRAGMENT_SHADER);
    if(fragment_shader_object == 0) {
        glDeleteShader(vertex_shader_object);
        return;
    }

    program_object = glCreateProgram();
    if(program_object == 0) {
        std::cout << "ERROR: failed to create shader program with shaders: \"" << vertex_shader_filepath << "\" and \"" << fragment_shader_filepath << "\" -> OpenGL failed to create shader object\n";
        glDeleteShader(vertex_shader_object);
        glDeleteShader(fragment_shader_object);
        return;
    }

    glAttachShader(program_object, vertex_shader_object);
    glAttachShader(program_object, fragment_shader_object);

    glLinkProgram(program_object);

    int success;
    glGetProgramiv(program_object, GL_LINK_STATUS, &success);
    if(!success) {
        char info_log[INFO_LOG_BUFFER_SIZE];
        glGetProgramInfoLog(program_object, INFO_LOG_BUFFER_SIZE, NULL, info_log);
        std::cout << "ERROR: failed to link program with shaders: \"" << vertex_shader_filepath << "\" and \"" << fragment_shader_filepath << "\" -> " << info_log << "\n";
        glDeleteShader(vertex_shader_object);
        glDeleteShader(fragment_shader_object);
        glDeleteProgram(program_object);
        program_object = 0;
    }

    glDeleteShader(vertex_shader_object);
    glDeleteShader(fragment_shader_object);

    program_object_instance_count = new (std::nothrow) unsigned int{1};
    if(program_object_instance_count == nullptr) {
        std::cout << "ERROR: failed to allocate memory for program object instance counting\n";
        glDeleteProgram(program_object);
        program_object = 0;
    }
}

ShaderProgram::~ShaderProgram() {
    if(program_object_instance_count == nullptr) return;

    (*program_object_instance_count)--;
    if(*program_object_instance_count == 0) { 
        glDeleteProgram(program_object);
        delete program_object_instance_count;
    } 
}

ShaderProgram::ShaderProgram(const ShaderProgram& other) {
    if(other.program_object_instance_count == nullptr) return;
    program_object = other.program_object;
    program_object_instance_count = other.program_object_instance_count;
    (*program_object_instance_count)++;
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept {
    program_object = other.program_object;
    program_object_instance_count = other.program_object_instance_count;
    other.program_object = 0;
    other.program_object_instance_count = nullptr;
}

ShaderProgram& ShaderProgram::operator=(const ShaderProgram& other) {
    if(this == &other) return *this;

    if(program_object_instance_count != nullptr) {
        (*program_object_instance_count)--;
        if(*program_object_instance_count == 0) {
            glDeleteProgram(program_object);
            delete program_object_instance_count;
        }
    }

    program_object = other.program_object;
    program_object_instance_count = other.program_object_instance_count;
    if(program_object_instance_count != nullptr) (*program_object_instance_count)++;

    return *this;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {
    if(this == &other) return *this;

    if(program_object_instance_count != nullptr) {
        (*program_object_instance_count)--;
        if(*program_object_instance_count == 0) {
            glDeleteProgram(program_object);
            delete program_object_instance_count;
        }
    }

    program_object = other.program_object;
    program_object_instance_count = other.program_object_instance_count;
    other.program_object = 0;
    other.program_object_instance_count = nullptr;

    return *this;
}

bool ShaderProgram::is_valid() const {
    return program_object != 0;
}

void ShaderProgram::use() const {
    if(program_object == 0) std::cout << "ERROR: tried to use invalid program -> program now unbound\n";
    glUseProgram(program_object);
}

unsigned int ShaderProgram::get_id() const {
    return program_object;
}