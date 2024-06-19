//
// Created by Christopher Gruber on 6/18/24.
//

#ifndef CHERNOOPENGLTUTORIAL_SHADER_H
#define CHERNOOPENGLTUTORIAL_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    // Constructor that builds the shader from a vertex and fragment shader file
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    // Use the current shader
    void use();

    // Utility functions
    GLuint getProgramID() const;

private:
    // Program ID
    GLuint programID;

    // Utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif //CHERNOOPENGLTUTORIAL_SHADER_H
