#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <sys/wait.h>

GLuint VAO, VBO, shader;

// Vertext shader
static const char* v_shader = "             \n\
#version 410                                            \n\
layout (location = 0) in vec3 pos; \n\
void main(){        \n\
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); \n\
}                \n\
";

static const char* f_shader = " \n\
#version 410 \n\
\n\
out vec4 colour; \n\
\n\
void main(){\n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);\n\
}\n\
";

void add_shader(GLuint program, const char* shader_code, GLenum shader_type){
    GLuint the_shader = glCreateShader(shader_type);

    const GLchar* the_code[1];
    the_code[0] = shader_code;

    GLint code_length[1];
    code_length[0] = std::strlen(shader_code); 

    glShaderSource(the_shader, 1, the_code, code_length);
    glCompileShader(the_shader);

    GLint result = 0;
    GLchar e_log[1024] = {0};

    glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);

    if(!result){
        glGetShaderInfoLog(the_shader, sizeof(e_log), NULL, e_log);
        std::cout << "Error compiling " << 
            (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << " shader: " << e_log << std::endl;
        return;
    }

    glAttachShader(program, the_shader);
}

void compile_shaders(){
    shader = glCreateProgram();
    
    if(!shader){
        std::cout << "Shader not initilized" << std::endl;
        return;
    }

    add_shader(shader, v_shader, GL_VERTEX_SHADER);
    add_shader(shader, f_shader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar e_log[1024] = {0};
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);

    if(!result){
        glGetProgramInfoLog(shader, sizeof(e_log), NULL, e_log);
        std::cout << "Error linking program" << e_log << std::endl;
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);

    if(!result){
        glGetProgramInfoLog(shader, sizeof(e_log), NULL, e_log);
        std::cout << "Error validating program" << e_log << std::endl;
        return;
    }

}

void create_triangle(){
    GLfloat verticies[]{
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

int main() {
    if(!glfwInit()){
        std::cout << "Couln't intilise GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "tomiczrd", NULL, NULL);

    if(window == NULL){
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glClearColor(.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    create_triangle();
    compile_shaders();
    
    while(!glfwWindowShouldClose(window)){
        // Clear the buffer
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glUseProgram(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
