// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "sat\PolygonArtist.h"
#include "util\ShaderProgram.h"

bool loadContent();


int main( void )
{
    // Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
	//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Collision" );

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	
	glm::vec2 tri[3] = {
		glm::vec2(-1.0f, -1.0f),
		glm::vec2(1.0f, -1.0f),
		glm::vec2(0.0f,  1.0f)
	};
	
	Polygon poly(tri, 3);
	ShaderProgram shaderProgram;
	if(!shaderProgram.loadProgram("SimpleVertexShader.vert", "SimpleFragmentShader.frag")) {
		printf("unable to load shader!\n");
	}
	else {
		shaderProgram.bind();
	}

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	projection = glm::ortho<GLfloat>(0.0, 10, 10, 0.0, 1.0, -1.0);
	// Camera matrix
	glm::mat4 view = glm::lookAt(
		glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0)  // Head is up
	);
	view = glm::mat4(1.0f);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(5,5,0));

	shaderProgram.setProjection(projection);
	shaderProgram.setView(view);
	shaderProgram.setModel(model);
	shaderProgram.updateMVP();

	poly.translate(5, 5);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		shaderProgram.setModel(poly.getModel());
		PolygonArtist::render(&poly);

		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
