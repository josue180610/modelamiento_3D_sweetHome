#pragma once
#include<GLFW/glfw3.h>

class BaseModelObject
{
	private:
		GLuint texturaID[3];
		GLuint windowsWall;
		float y;
		float z;
		float xrl;
		float rotacionX = 0.0f;
		float rotacionY = 0.0f;
		GLuint loadTextureFile(const char* path);
		void loadTextureForWindows(int n, char* path);
	public:
		BaseModelObject(float _y, float _z, float _xrl, float rotacionX, float rotacionY);
		float rotacionZ;
		void procesarEntrada(GLFWwindow* window);
		//void configFrustumParameter();
		void enableTexture();
		void disableTexture();
		void printSquad();
		void printLeftWindowAndWall();
		void printRightWindowAndWall();
		void printRearWallAndAnyObjects();

};

