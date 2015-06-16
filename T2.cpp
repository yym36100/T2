#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#include "stdafx.h"

#include "glutils.h"

#if 0
int _tmain(int argc, _TCHAR* argv[])
{
	//GLuint programID;
	GLFWwindow* window= InitGraphics();

	GLuint programID = LoadShaders( "simplevertshader.glsl", "simplefragshader.glsl" );
	printf("Shaders loaded\n");

	GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	while (!glfwWindowShouldClose(window)){

		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		//                glEnableVertexAttribArray(vertexPosition_modelspaceID);
		//                glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0, //vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			g_vertex_buffer_data // (void*)0            // array buffer offset
			);

		// see above glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glEnableVertexAttribArray ( 0 );

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}



#endif
int _tmain(int argc, _TCHAR* argv[])
{
	//GLuint programID;
	GLFWwindow* window= InitGraphics();

	GLuint programID = LoadShaders( "simplevertshader.glsl", "simplefragshader.glsl" );
	printf("Shaders loaded\n");

	GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	// Get a handle for our buffers
	GLuint colorhandle = glGetUniformLocation(programID, "mycolor");
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertex");

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


	

	float tLast = glfwGetTime();
	unsigned int frames = 0;
	bool once =true;
	float color =0;
	while (!glfwWindowShouldClose(window)){
		glUniform1f(colorhandle, color);
		color+=0.0001;
		if(color>1.0)color = 0;

		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(vertexPosition_modelspaceID,3, GL_FLOAT, GL_FALSE,0,(void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); 

		//glDisableVertexAttribArray(vertexPosition_modelspaceID);

			if(once){
			once = false;

			int GScreenWidth = 320;
			int GScreenHeight = 240;

			void* image = malloc(GScreenWidth*GScreenHeight*4);
			glBindFramebuffer(GL_FRAMEBUFFER,0);
			glReadPixels(0,0,GScreenWidth,GScreenHeight, GL_RGBA, GL_UNSIGNED_BYTE, image); //GScreenWidth,GScreenHeight,
			FILE *fp = fopen("screenshot.ppm", "wb");
			//fprintf(fp, "P6\n%d %d\n255\n", GScreenWidth, GScreenHeight);
			fwrite(image, GScreenWidth*GScreenHeight*4, 1, fp);
			fclose(fp);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (1) {
			frames++;
			if (frames > 500) {
				printf("FPS: %f\n",(float(frames)/(glfwGetTime()-tLast)));
				tLast = glfwGetTime();
				frames=0;
			}
		}

	

	}

	glDeleteBuffers(1, &vertexbuffer);
	return 0;
}

