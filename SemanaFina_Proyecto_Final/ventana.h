#pragma once
#include <GLFW/glfw3.h>

class Ventana
{

public:
	void centrarPantallaPrincipal(GLFWwindow*& windows);
	int screenWidth;
	int screenHeight;
	void renderizarMueblePorSeleccion();
	void restaurarMueblePorSeleccion();
	void onMouseClick(GLFWwindow* window, int button, int action, int mods);
	void inicializarFramebufferSeleccion(int width, int height);
	Ventana();
private:
	void activarClickDeMouse(int x, int y);
};

