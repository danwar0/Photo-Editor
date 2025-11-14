cmake_minimum_required(VERSION 3.28)
project(photo-editor)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE 
    ./src/main.cpp 
    ./src/misc/glad.c 
    ./src/application/Application.cpp 
    ./src/rendering/Renderer.cpp
    ./src/rendering/shaderprogram/ShaderProgram.cpp 
    ./src/rendering/shaderprogram/UniformSetters.cpp 
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ./include
)

target_link_directories(${PROJECT_NAME} PRIVATE ./libs)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 OpenGL::GL)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#add_compile_definitions(SHADER_DEBUG)