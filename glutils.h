#ifndef __GLUTILS_H__
#define __GLUTILS_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow*  InitGraphics(void); 
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif //__GLUTILS_H__