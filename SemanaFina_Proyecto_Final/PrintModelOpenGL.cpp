#include "PrintModelOpenGL.h"
#include <iostream>
using namespace std;

PrintModelOpenGL::PrintModelOpenGL(float _y, float _z, float _xrl, float _rotacionX,
	float _rotacionY, float _rotacionZ, bool _activeMove) {
	y = _y;
	z = _z;
	xrl = _xrl;
	activeMove = _activeMove;
	rotacionX = _rotacionX;
	rotacionY = _rotacionY;
	rotacionZ = 2.925f;
}

void PrintModelOpenGL::enableTexture() {
	//Función para dibujar un estructura con textura
	glEnable(GL_TEXTURE_2D); //habilitamos el uso de texturas

}

void PrintModelOpenGL::disableTexture() {
	glDisable(GL_TEXTURE_2D); //deshabilitamos el uso de texturas para otros objetos
	//si los hubiera   
}


void PrintModelOpenGL::printSquad(GLuint texturaId) {
	glBindTexture(GL_TEXTURE_2D, texturaId); // enlaza la presente textura (de la estructura)
	// con la que hemos cargado, es decir, "texturaID"  
	glBegin(GL_QUADS);
	// piso del establecimiento
	// glColor3f(0.0f, 0.0f, 1.0f); // azul
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-xrl, -y, -z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xrl, -y, -z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xrl, -y, (z - 1.0f));
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-xrl, -y, (z - 1.0f));
	glEnd();
	//fin de la generación de la estructura
}

void PrintModelOpenGL::printLeftWindowAndWall(GLuint texturaId) {
	glBindTexture(GL_TEXTURE_2D, texturaId); // enlaza la presente textura (de la estructura)
	// con la que hemos cargado, es decir, "texturaID"  
	glBegin(GL_QUADS);
	// pared izquierda
	// glColor3f(1.0f, 0.0f, 0.0f); // rojo
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-xrl, -y, -z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-xrl, -y, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-xrl, y, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-xrl, y, -z);
	glEnd();
}

void PrintModelOpenGL::printRightWindowAndWall(GLuint texturaId) {
	glBindTexture(GL_TEXTURE_2D, texturaId); // enlaza la presente textura (de la estructura)
	// con la que hemos cargado, es decir, "texturaID"  
	glBegin(GL_QUADS);
	// pared derecha
	// glColor3f(1.0f, 0.0f, 0.0f); // rojo

	glTexCoord2f(0.0f, 0.0f); glVertex3f(xrl, -y, -z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xrl, -y, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xrl, y, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xrl, y, -z);
	glEnd();
}


void PrintModelOpenGL::printRearWallAndAnyObjects(GLuint texturaId) {

	glBindTexture(GL_TEXTURE_2D, texturaId); // enlaza la presente textura (de la estructura)
	// con la que hemos cargado, es decir, "texturaID"  
	glBegin(GL_QUADS);
	// Cara frontal
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// pared trasera
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.35, -y, -1.5f);  // inferior izquierda
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.35f, -y, -1.5f);; // inferior derecha
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.35f, y, -1.5f);;  // superior derecha
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.35f, y, -1.5f); // superior izquierda
	glEnd();

}


void PrintModelOpenGL::procesarEntrada(GLFWwindow* window, bool activeMove) {
	cout << "valor: " << activeMove << endl;
	cout << "rotacionX: " << rotacionX << endl;
	cout << "rotacionY: " << rotacionY << endl;
	cout << "rotacionZ: " << rotacionZ << endl;
	if (activeMove) {
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotacionX -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotacionX += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotacionY -= 0.05f;
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotacionY += 0.05f;
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) rotacionZ += 0.001f; // retroceder objeto
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) rotacionZ -= 0.001f; // avanzar objeto
	}
}