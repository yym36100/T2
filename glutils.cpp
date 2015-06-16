#include <stdlib.h>
#include <stdio.h>

#include "glutils.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) exit(0);
}

GLFWwindow* InitGraphics(void){
	printf("Init graphics\n");
	if (!glfwInit())      return 0;
	GLFWwindow* window = glfwCreateWindow(320,240, "T2", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(window, key_callback);
	glewInit();
	glViewport(0, 0, 320, 240);   
	printf("Screen started\n");
	return window;
}

bool LoadFile(const char* filename, char **str){ 
	FILE* f = fopen(filename, "rb");
	fseek(f,0,SEEK_END);
	int sz = ftell(f);
	fseek(f,0,SEEK_SET);
	char *Src = new char[sz+1];
	fread(Src,1,sz,f);
	Src[sz] = 0; //null terminate it!
	fclose(f);
	*str = Src;
	return true;
}

GLuint compShader(GLenum type, const char* src){
	GLuint shader;
	GLint compiled;

	shader = glCreateShader(type);
	if (shader == 0) return 0;

	glShaderSource(shader, 1, &src, NULL); 
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Error compiling shader: %s\n",infoLog);
			free(infoLog);
		}
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
	char *vs,*fs;
	if(!LoadFile(vertex_file_path,&vs)) return 0;
	if(!LoadFile(fragment_file_path,&fs)) return 0;


	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;
	GLuint handle;

	vertexShader = compShader(GL_VERTEX_SHADER, vs);
	fragmentShader = compShader(GL_FRAGMENT_SHADER, fs);

	handle = glCreateProgram();

	if (handle == 0)
		return 0;

	glAttachShader(handle, vertexShader);
	glAttachShader(handle, fragmentShader);

	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv ( handle, GL_INFO_LOG_LENGTH, &infoLen );

		if ( infoLen > 1 )
		{
			char* infoLog = (char*)malloc(sizeof(char) * infoLen);

			glGetProgramInfoLog ( handle, infoLen, NULL, infoLog);
			printf("Error linking program:%s\n",infoLog);
			free(infoLog);
		}
		glDeleteProgram(handle);
		return 0;
	}

	return handle;
}
