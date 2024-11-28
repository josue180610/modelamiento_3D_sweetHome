#pragma once
#include <GLFW/glfw3.h>

class Ventana
{

public:
	void centrarPantallaPrincipal(GLFWwindow*& windows);
	GLuint cargarTextura(const char* path);
};

