
#include "screem_utils.h"   // Incluye el encabezado
#include <iostream>
#include "ConfigModelOpenGL.h"
#include "PrintModelOpenGL.h"
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas


using namespace std;

GLuint texturaID[3];
GLuint windowsWall;
int main() {
	/*valores para constructor ConfigModelOpenGL*/
	float y = 1.0f;
	float z = 1.5f;
	float xrl = 1.35f;
	float rotacionX = 0.0f;
	float rotacionY = 0.0f;
	float rotacionZ = 2.5f;
	ConfigModelOpenGL modeloOpenGl = ConfigModelOpenGL();
	PrintModelOpenGL windowOpenGl = PrintModelOpenGL(y, z, xrl,true,rotacionX,rotacionY,rotacionZ);
	if (!glfwInit()) { // Si el entorno no se inicializa correctamente
		return -1; // termina el programa y devuelve un error
	}
	GLFWwindow* window;
	modeloOpenGl.initWindowsCenter(window); // Obtengo el valor de la variable window por referencia
	// Realizo la configuración de luminosidad para el objeto a mostrar.
	modeloOpenGl.inicializarOpenGL();
	// Establecer la matriz de proyección en perspectiva
	modeloOpenGl.configFrustumParameter();
	float xi = 1.0f;
	float zi = 1.0f;
	// Obtengo las texturas
	modeloOpenGl.loadTextureFile("textures/ventanas/textura-ventana-02.jpg", texturaID[0]);
	modeloOpenGl.loadTextureFile("textures/paredes/textura-pared-01.jpg", texturaID[1]);
	modeloOpenGl.loadTextureFile("textures/pisos/textura-piso-03.jpg", texturaID[2]);
	modeloOpenGl.loadTextureFile("image/ventanas/ventana02.png", windowsWall);
	while (!glfwWindowShouldClose(window)) { // Ejecutar todo lo que se encuentre en la ventana, mientras no se cierre
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // permite borrar la pantalla, antes de dibujar
		// esto evita que las imagenes se sobrepongan y también permite eliminar el buffer de produndidad
		windowOpenGl.procesarEntrada(window, windowOpenGl.activeMove); // permite mover el objeto, es decir, la estructura
		//Aplicar las transformaciones de visualización al cubo
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//Reseteamos la matriz de modelo-vista
		glTranslatef(0.0f, 0.0f, -windowOpenGl.rotacionZ); //Alejar la cámara
		// glRotatef(0.0f, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		// cout << "Entero: " << rotacionX << endl;
	
		glRotatef(windowOpenGl.rotacionX, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		glRotatef(windowOpenGl.rotacionY, 0.0f, 1.0f, 0.0f);
		windowOpenGl.enableTexture();

		windowOpenGl.printLeftWindowAndWall(texturaID[0]);
		windowOpenGl.printRightWindowAndWall(texturaID[0]);
		windowOpenGl.printRearWallAndAnyObjects(texturaID[1]);
		windowOpenGl.printSquad(texturaID[2]);

		windowOpenGl.disableTexture();
		// glRotatef(anguloRotacion, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
		glfwSwapBuffers(window); // intercambiar el buffer de pantalla actual
		// con el buffer del dibujo, es decir, el render.
		glfwPollEvents(); // Gestión de dispositivos de entrada (mouse, teclado...)
		// para interactuar con la ventana
	}
	glfwTerminate(); // termina la operación.
	return 0;
}