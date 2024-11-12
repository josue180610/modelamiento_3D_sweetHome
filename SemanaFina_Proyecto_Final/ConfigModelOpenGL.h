#pragma once
#include <GLFW/glfw3.h>
#include <string>

class ConfigModelOpenGL
{	

	public:
		float y;
		float z;
		float xrl;
		ConfigModelOpenGL(float y, float z, float xrl);
		void initWindowsCenter(GLFWwindow*& windows);
		void inicializarOpenGL();
		GLuint loadTextureFile(const char* path, GLuint& texturaId);
		void enableTexture();
		void disableTexture();
		void printSquad(GLuint texturaId);
		void printLeftWindowAndWall(GLuint texturaId);
		void printRightWindowAndWall(GLuint texturaId);
		void printRearWallAndAnyObjects(GLuint texturaId);
		void configFrustumParameter();
		

};

