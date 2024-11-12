#pragma once
#include <GLFW/glfw3.h>
#include <string>

class ConfigModelOpenGL
{	

	public:
		ConfigModelOpenGL();
		void initWindowsCenter(GLFWwindow*& windows);
		void inicializarOpenGL();
		void configFrustumParameter();
		GLuint loadTextureFile(const char* path, GLuint& texturaId);
		
};

