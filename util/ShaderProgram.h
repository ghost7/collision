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
	
	GLuint loadShaderFromFile(std::string path, GLenum shaderType);
	GLuint loadShaderString(std::string shaderString, GLenum shaderType);
	void printShaderLog(GLuint shader);
	void printProgramLog(GLuint program);

public:
	ShaderProgram();
	~ShaderProgram();
	bool loadProgram(std::string vertexFilePath, std::string fragmentFilePath);
	void setProjection(glm::mat4 const & projection);
	void setView(glm::mat4 const & view);
	void setModel(glm::mat4 const & model);
	void updateMVP();
	bool bind();
	void unbind();
};

#endif
