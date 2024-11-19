#pragma once
#include <GLFW/glfw3.h>
class Configuracion
{
public:
	void centrarPantallaPrincipal(GLFWwindow*& windows);
	void inicializarOpenGL();
	GLuint cargarTextura(const char* path);
	void dibujarVentana(bool tieneTextura);
	Configuracion();
};

