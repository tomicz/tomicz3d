#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Renamed to snake_case
void check_shader_compile_errors(unsigned int shader) {
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "Shader compilation failed:\n" << info_log << std::endl;
        glfwTerminate();
        exit(-1);
    }
}

int main() {
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Move these hints before window creation
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(mode->width, mode->height, "Tomicz3D", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Add GLEW initialization error check
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW initialization failed: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    // Scale factor (e.g., 0.3 for a smaller square, 2.0 for a larger square)
    float scale = 1.0f;  // Adjust this value to change size
    
    float vertices[] = {
        // First triangle
         0.5f * scale,  0.5f * scale, 0.0f,  // top right
         0.5f * scale, -0.5f * scale, 0.0f,  // bottom right
        -0.5f * scale, -0.5f * scale, 0.0f,  // bottom left
        // Second triangle
        -0.5f * scale, -0.5f * scale, 0.0f,  // bottom left
        -0.5f * scale,  0.5f * scale, 0.0f,  // top left
         0.5f * scale,  0.5f * scale, 0.0f   // top right
    };

    // Create and bind Vertex Buffer Object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create and compile vertex shader
    const char* vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform float scale;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z, 1.0);\n"
        "}\0";
    
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    check_shader_compile_errors(vertexShader);

    // Create and compile fragment shader
    const char* fragmentShaderSource = 
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    check_shader_compile_errors(fragmentShader);

    // Create shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Add program linking error check
    int success;
    char info_log[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
        std::cerr << "Shader program linking failed:\n" << info_log << std::endl;
        return -1;
    }

    // Clean up shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Create Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Get the location of the scale uniform
    int scaleLocation = glGetUniformLocation(shaderProgram, "scale");
    
    while (!glfwWindowShouldClose(window)) {
        // Set clear color (dark grey background)
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        glUseProgram(shaderProgram);
        
        // Set the scale uniform (can be changed dynamically)
        float scale = 0.3f;  // Adjust this value to change size
        glUniform1f(scaleLocation, scale);
        
        // Bind the VAO and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}