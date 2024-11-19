#include "movimentos.h"
#include "movimentos.h"

using namespace std;

float Movimentos::lastMouseX = 0.0f;
float Movimentos::lastMouseY = 0.0f;
float Movimentos::objectX = 0.0f;
float Movimentos::objectY = 0.0f;
float Movimentos::sensibilidad = 0.01f;
bool Movimentos::isDragging = false;

void Movimentos::obtenerPosicionUltimaMouse(GLFWwindow* window, double xCurrentpos, double yCurrentpos) {
	if (isDragging) {
		/*Procedemos a calcular la diferencia entre la posición final y actual*/
		float deltaX = static_cast<float>(xCurrentpos - lastMouseX);
		float deltaY = static_cast<float>(yCurrentpos - lastMouseY);
		
		objectX += deltaX * sensibilidad; // 0.01f es la sensibilidad de movimiento del mouse en la posición X
		objectY -= deltaY * sensibilidad;

		/*Actualizar la nueva posición final*/
		lastMouseX = static_cast<float>(xCurrentpos);
		lastMouseY = static_cast<float>(yCurrentpos);

	}
}

void Movimentos::activarMovimientoPorMouse(GLFWwindow* window, int buttonActive, int actionPress, int mods) {
	/*Validar si tenemos apretado el click izquierdo*/
	if (buttonActive == GLFW_MOUSE_BUTTON_LEFT && actionPress == GLFW_PRESS) {
		isDragging = true;
		// Obtener la posición inicial del mouse al presionar
		double xLastMouseX = static_cast<double>(lastMouseX);
		double yLastMouseY = static_cast<double>(lastMouseY);
		glfwGetCursorPos(window, &xLastMouseX, &yLastMouseY);
		lastMouseX = static_cast<float>(xLastMouseX);
		lastMouseY = static_cast<float>(yLastMouseY);
	}
	else if (actionPress == GLFW_RELEASE) {
		isDragging = false;
	}
}
