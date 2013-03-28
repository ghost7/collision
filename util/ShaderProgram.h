/**
* Utility class used to load and use shaders, defined in text file.
* 
* Example Usage:
* shader.loadProgram("vertexShader.vert", "fragmentShader.frag");
* shader.bind();
*/

#ifndef _UTIL_SHADER_PROG_
#define _UTIL_SHADER_PROG_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

class ShaderProgram
{
private:
    GLuint programID;
    GLuint matrixID;
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 model;

    /**
    * Load a shader from a file.
    *
    * @param path Path of the file.
    * @param shaderType Type of shader to load.
    */
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);

    /**
    * Load a shader defined from the contents of a string.
    *
    * @param shaderString String contating the shader definition
    * @param shaderType Type of shader to load.
    */
    GLuint loadShaderString(std::string shaderString, GLenum shaderType);

    /**
    * Incase of errors with the shader, the log can be printed to the standard
    * out.
    *
    * @param shader Shader whose log is to be printed.
    */
    void printShaderLog(GLuint shader);

    /**
    * Incase of errors with the shader program, the log can be printed to the 
    * standard out.
    */
    void printProgramLog(GLuint program);

public:
    ShaderProgram();
    ~ShaderProgram();

    /**
    * Load a shader program with a vertex shader and fragment shader.
    *
    * @param vertexFilePath File path of the vertex shader.
    * @param fragmentFilePath File path of the fragment shader.
    */
    bool loadProgram(std::string vertexFilePath, std::string fragmentFilePath);

    /**
    * For calculation of the model, view, projection vector. Load the
    * projection matrix.
    *
    * @param projection Projection matrix.
    */
    void setProjection(glm::mat4 const & projection);

    /**
    * For calculation of the model, view, projection vector. Load the
    * view matrix.
    *
    * @param projection View matrix.
    */
    void setView(glm::mat4 const & view);

    /**
    * For calculation of the model, view, projection vector. Load the
    * model matrix.
    *
    * @param projection Model matrix.
    */
    void setModel(glm::mat4 const & model);

    /**
    * Send the updated model, view, projection matrices to the graphics card.
    * If this function is not called, the matrices will not be updated for the 
    * shader program.
    */
    void updateMVP();

    /**
    * Use this shader program.
    */
    bool bind();

    /**
    * Stop using this shader program.
    */
    void unbind();
};

#endif
