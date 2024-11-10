
#include "print_objects.h"
#include "screem_utils.h"   // Incluye el encabezado
#include<GLFW/glfw3.h>
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas


using namespace std;
float rotacionX = 0.0f;
float rotacionY = 0.0f;

void procesarEntrada(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotacionX -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotacionX += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotacionY -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotacionY += 0.05f;
}
int main() {


	if (!glfwInit()) { // Si el entorno no se inicializa correctamente
		return -1; // termina el programa y devuelve un error
	}
	
	GLFWwindow* window = initWindowsCenter();
	// Realizo la configuración de luminosidad para el objeto a mostrar.
	inicializarOpenGL();
	// Establecer la matriz de proyección en perspectiva
	configFrustumParameter();

	while (!glfwWindowShouldClose(window)) { // Ejecutar todo lo que se encuentre en la ventana, mientras no se cierre
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // permite borrar la pantalla, antes de dibujar
		// esto evita que las imagenes se sobrepongan y también permite eliminar el buffer de produndidad
		procesarEntrada(window); // permite mover el objeto, es decir, la estructura
		//Aplicar las transformaciones de visualización al cubo
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//Reseteamos la matriz de modelo-vista
		glTranslatef(0.0f, 0.0f, -3.0f); //Alejar la cámara
		// glRotatef(0.0f, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		// cout << "Entero: " << rotacionX << endl;
	
		glRotatef(rotacionX, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
		enableTexture();
		printLeftWindowAndWall();
		printRightWindowAndWall();
		printRearWallAndAnyObjects();
		printSquad();

		disableTexture();
		// glRotatef(anguloRotacion, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		glfwSwapBuffers(window); // intercambiar el buffer de pantalla actual
		// con el buffer del dibujo, es decir, el render.
		glfwPollEvents(); // Gestión de dispositivos de entrada (mouse, teclado...)
		// para interactuar con la ventana
	}
	glfwTerminate(); // termina la operación.
	return 0;
}