
#include "screem_utils.h"   // Incluye el encabezado
#include <iostream>
#include "ConfigModelOpenGL.h"
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas


using namespace std;
float rotacionX = 0.0f;
float rotacionY = 0.0f;
float rotacionZ = 2.5f;
void procesarEntrada(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotacionX -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotacionX += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotacionY -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotacionY += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) rotacionZ += 0.001f; // retroceder objeto
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) rotacionZ -= 0.001f; // avanzar objeto
}

GLuint texturaID[3];
GLuint windowsWall;
int main() {
	/*valores para constructor ConfigModelOpenGL*/
	float y = 1.0f;
	float z = 1.5f;
	float xrl = 1.35f;
	ConfigModelOpenGL modeloOpenGl = ConfigModelOpenGL(y,z,xrl);
	
	if (!glfwInit()) { // Si el entorno no se inicializa correctamente
		return -1; // termina el programa y devuelve un error
	}
	GLFWwindow* window;
	modeloOpenGl.initWindowsCenter(window); // Obtengo el valor de la variable window por referencia
	// Realizo la configuraci�n de luminosidad para el objeto a mostrar.
	modeloOpenGl.inicializarOpenGL();
	// Establecer la matriz de proyecci�n en perspectiva
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
		// esto evita que las imagenes se sobrepongan y tambi�n permite eliminar el buffer de produndidad
		procesarEntrada(window); // permite mover el objeto, es decir, la estructura
		//Aplicar las transformaciones de visualizaci�n al cubo
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();//Reseteamos la matriz de modelo-vista
		glTranslatef(0.0f, 0.0f, -rotacionZ); //Alejar la c�mara
		// glRotatef(0.0f, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaci�n
		// cout << "Entero: " << rotacionX << endl;
	
		glRotatef(rotacionX, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaci�n
		glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);
		modeloOpenGl.enableTexture();

		modeloOpenGl.printLeftWindowAndWall(texturaID[0]);
		modeloOpenGl.printRightWindowAndWall(texturaID[0]);
		modeloOpenGl.printRearWallAndAnyObjects(texturaID[1]);
		modeloOpenGl.printSquad(texturaID[2]);

		modeloOpenGl.disableTexture();
		// glRotatef(anguloRotacion, 1.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaci�n
		glfwSwapBuffers(window); // intercambiar el buffer de pantalla actual
		// con el buffer del dibujo, es decir, el render.
		glfwPollEvents(); // Gesti�n de dispositivos de entrada (mouse, teclado...)
		// para interactuar con la ventana
	}
	glfwTerminate(); // termina la operaci�n.
	return 0;
}