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

#include "sat/PolygonArtist.h"
#include "util/ShaderProgram.h"

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
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);
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
		glm::vec2(-0.5f, -0.5f),
		glm::vec2(0.5f, -0.5f),
		glm::vec2(0,  0.5f)
	};

	glm::vec2 square[4] = {
		glm::vec2(-0.5f, -0.5f),
		glm::vec2(0.5f, -0.5f),
		glm::vec2(0.5f,  0.5f),
		glm::vec2(-0.5f, 0.5f)
	};
	
	Polygon poly1(tri, 3);
	Polygon poly2(square, 4);
	ShaderProgram shaderProgram;
	if(!shaderProgram.loadProgram("SimpleVertexShader.vert", "SimpleFragmentShader.frag")) {
		printf("unable to load shader!\n");
	}
	else {
		shaderProgram.bind();
	}

	// Projection matrix : 10x10 region, bottom right (0,0) 
    glm::mat4 projection = glm::ortho<GLfloat>(0.0, 10, 10, 0.0, 1.0, -1.0);
	// Camera matrix: identity
    glm::mat4 view = glm::mat4();

	shaderProgram.setProjection(projection);
	shaderProgram.setView(view);

	poly1.translate(1, 1);
	poly2.translate(5, 5);

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		if(glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			poly1.translate(0.1f, 0);
		}
		if(glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
			poly1.translate(-0.1f, 0);
		}
		if(glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
			poly1.translate(0, -0.1f);
		}
		if(glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
			poly1.translate(0, 0.1f);
		}

		glm::vec2 mtv;
		if(poly1.intersects(&poly2, mtv)) {
			glClearColor(0.4f, 0.0f, 0.0f, 0.0f);
			poly1.translate(mtv.x, mtv.y);
		}
		else {
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		}

        // The polygon is the "model" that is being rendered.
        shaderProgram.setModel(poly1.getModel());
		shaderProgram.updateMVP();
        PolygonArtist::render(&poly1);

        shaderProgram.setModel(poly2.getModel());
		shaderProgram.updateMVP();
        PolygonArtist::render(&poly2);

		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
