// Include standard headers
#include <array>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialise GLFW
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Cherno OpenGL Tutorial", nullptr, nullptr);
    if( window == nullptr ){
        std::cerr << "Failed to open GLFW window. Check the OpenGL hints." << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's OpenGL context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    // GLEW has a problem with core profiles, so we need to tell GLEW to use a modern approach to retrieving function pointers
    // GLEW will be used to load all OpenGL function pointers
    // GLEW must be initialized after we have a working OpenGL context
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Create a vertex array object of vertices to draw
    std::array<float, 6> positions = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f,
    };

    // Create a vertex array object (vao) to store the vertices
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a vertex buffer object (vbo) to store the vertices
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    // index 0 is the location of the vertex attribute
    // size is 2 because we have 2 components in the vertex
    // type is GL_FLOAT because each vertex is a float
    // normalized is GL_FALSE because we don't want the values to be normalized
    // stride is 2 * sizeof(float) because each vertex is 2 floats
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    // Load shaders
    Shader shader("shaders/vertex/vertex.glsl", "shaders/fragment/fragment.glsl");

    // Check if the shaders compiled. This isn't necessary, just here for debugging
    if (!shader.isCompiled()) {
        std::cerr << "Failed to compile shaders" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Check if the ESC key was pressed or the window was closed
    while(!glfwWindowShouldClose(window))
    {
        // Process user input
        processInput(window);

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader
        shader.use();

        // Bind the vertex array object
        glBindVertexArray(vao);

        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
}
