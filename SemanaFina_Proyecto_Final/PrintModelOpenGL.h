#pragma once
#include <GLFW/glfw3.h>
#include <string>
class PrintModelOpenGL
{
	public:
		float y;
		float z;
		float xrl;
		float rotacionX;
		float rotacionY;
		float rotacionZ;
		bool activeMove;
		PrintModelOpenGL(float y, float z, float xrl, float rotacionX,
			float rotacionY, float rotacionZ, bool activeMove);
		void enableTexture();
		void disableTexture();
		void printSquad(GLuint texturaId);
		void printLeftWindowAndWall(GLuint texturaId);
		void printRightWindowAndWall(GLuint texturaId);
		void printRearWallAndAnyObjects(GLuint texturaId);
		void procesarEntrada(GLFWwindow* window, bool activeMove);
};

