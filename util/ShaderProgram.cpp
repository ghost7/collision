#include <fstream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
    programID = 0;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programID);
}

bool ShaderProgram::loadProgram(std::string vertexFilePath, 
    std::string fragmentFilePath)
{
    programID = glCreateProgram();

    // Load the vertex shader
    GLuint vertexShader = loadShaderFromFile(vertexFilePath, 
        GL_VERTEX_SHADER);

    if(vertexShader == 0) {
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    // Load the fragment shader
    GLuint fragmentShader = loadShaderFromFile(fragmentFilePath, 
        GL_FRAGMENT_SHADER);

    if(fragmentShader == 0) {
        glDeleteShader(vertexShader);
        glDeleteProgram(programID);
        programID = 0;
        return false;
    }

    // Attach the shaders and link
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    // Don't need the shaders any more
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Check for errors
    GLint programSuccess = GL_TRUE;

    glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
    if(programSuccess != GL_TRUE) {
        printf( "Error linking program %d!\n", programID );
        printProgramLog( programID );
        glDeleteProgram( programID );
        programID = 0;
        return false;
    }

    matrixID = glGetUniformLocation(programID, "MVP");

    return true;
}

bool ShaderProgram::bind()
{
    glUseProgram(programID);

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error binding shader! %s\n", gluErrorString( error ) );
        printProgramLog( programID );
        return false;
    }

    return true;
}

void ShaderProgram::unbind()
{
    // Use default program
    glUseProgram(NULL);
}

void ShaderProgram::setProjection(glm::mat4 const & projection)
{
    this->projection = projection;
}

void ShaderProgram::setView(glm::mat4 const & view)
{
    this->view = view;
}

void ShaderProgram::setModel(glm::mat4 const & model)
{
    this->model = model;
}

void ShaderProgram::updateMVP()
{
    glm::mat4 MVP = projection * view * model;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
}

GLuint ShaderProgram::loadShaderFromFile(std::string path, GLenum shaderType)
{
    std::string shaderString;
    std::ifstream sourceFile(path.c_str());

    if(sourceFile)	{
        // Get shader source
        shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), 
            std::istreambuf_iterator<char>());
        return loadShaderString(shaderString, shaderType);
    }
    else {
        printf("Unable to open file %s.\n", path.c_str());
    }
    return 0;
}

GLuint ShaderProgram::loadShaderString(std::string shaderProgram, GLenum shaderType)
{
    int shaderID = glCreateShader(shaderType);

    const GLchar* shaderSource = shaderProgram.c_str();
    glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

    // Compile the shader source
    glCompileShader(shaderID);

    // Check the shader for any errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
    if(shaderCompiled != GL_TRUE) {
        printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, 
            shaderSource);
        printShaderLog(shaderID);
        glDeleteShader(shaderID);
        shaderID = 0;
    }
    return shaderID;
}

void ShaderProgram::printShaderLog(GLuint shader)
{
    //Make sure name is shader
    if( glIsShader( shader ) ) {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            printf( "%s\n", infoLog );
        }

        delete[] infoLog;
    }
    else {
        printf( "Name %d is not a shader\n", shader );
    }
}

void ShaderProgram::printProgramLog(GLuint program)
{
    //Make sure name is shader
    if( glIsProgram( program ) ) {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 ) {
            printf( "%s\n", infoLog );
        }

        delete[] infoLog;
    }
    else {
        printf( "Name %d is not a program\n", program );
    }
}
