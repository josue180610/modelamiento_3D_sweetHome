#pragma once
#include <GLFW/glfw3.h>

class Ventana
{

public:
	void centrarPantallaPrincipal(GLFWwindow*& windows);
	int screenWidth;
	int screenHeight;
	GLuint cargarTextura(const char* path);
	Ventana();
};

