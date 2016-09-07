// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>

//Include custom libraries
#include "file_loader.h"
#include "Display.h"
using namespace glm;





int main( void )
{
	int width = 1024;
	int height = 768;

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( width, height, "Interior Decorator", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	Display Scene("test.txt", window);
	
	do{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		///glClear( GL_COLOR_BUFFER_BIT );

		//Scene.Rotate(1,0.001f,0.0f,0.0f);
		/*
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			Scene.Translate(0, 0.0, 0.007, 0.00);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			Scene.Translate(0, 0.0, -0.007, -0.00);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			Scene.Rotate(0, 0.001f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			Scene.Rotate(0, -0.001f, 0.0f, 0.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			Scene.Scale(0, 1.001f, 1.001f, 1.001f);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			Scene.Scale(0, 0.999f, 0.999f, 0.999f);
		}*/
		//Scene.Translate(2, 0, 0.0007, 0.000);
		//Scene.Scale(2, 1.0003, 1.0003, 1.0003);
		Scene.Draw();

		// Swap buffers
		///glfwSwapBuffers(window);
		//glClearColor(0.0f, 1.0f, 0.4f, 0.0f);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	///Scene.Save();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	
	return 0;
}

