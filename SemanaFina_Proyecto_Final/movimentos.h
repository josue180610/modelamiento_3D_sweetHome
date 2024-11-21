#pragma once
#include <GLFW/glfw3.h>

class Movimentos
{
	public:
		static float sensibilidad;
		static void obtenerPosicionUltimaMouse(GLFWwindow* window, double xCurrentpos, double yCurrentpos);
		static void activarMovimientoPorMouse(GLFWwindow* window, int buttonActive, int actionPress, int mods);
	private:
		static float objectX, objectY;
		static float lastMouseX, lastMouseY;
		static bool isDragging;
		
};

