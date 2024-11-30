#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "oficina.h"
#include "ventana.h"
#include <stdexcept>
#include <iostream>

using namespace std;
// Tama�o de la ventana
Ventana::Ventana() {
	screenWidth = 1024;
	screenHeight = 640;

}

/*==============================================*/
GLuint selectionFBO, selectionTexture;

void Ventana::activarClickDeMouse(int x, int y) {
	glBindFramebuffer(GL_FRAMEBUFFER, selectionFBO); // Bind del framebuffer de selecci�n
	glReadBuffer(GL_COLOR_ATTACHMENT0); // Establece el buffer de lectura al color del FBO

	unsigned char pixel[3]; // Para almacenar el color del p�xel seleccionado
	glReadPixels(x, screenHeight - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel); // Leer el p�xel en las coordenadas (x, y)

	glBindFramebuffer(GL_FRAMEBUFFER, 0); // Restaurar el framebuffer a su estado normal

	// Convertir el color del p�xel a un ID
	int id = pixel[0] | (pixel[1] << 8) | (pixel[2] << 16);
	std::cout << "Cubo seleccionado con ID: " << id << std::endl;

	// Procesar la selecci�n
	for (auto& mueble : muebles) {
		if (mueble.id == id) { // Si el ID coincide con el mueble
			muebleSeleccionado = id; // Establecer el mueble como seleccionado
			break;
		}
	}
}

void Ventana::onMouseClick(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) { // Solo procesar si el bot�n fue presionado
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos); // Obtener la posici�n del cursor

		// Llamar a la funci�n para procesar la selecci�n en base a la posici�n
		activarClickDeMouse((int)xpos, (int)ypos);
	}
}


void Ventana::renderizarMueblePorSeleccion() {
	glBindFramebuffer(GL_FRAMEBUFFER, selectionFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el framebuffer de selecci�n
	
}

void Ventana::restaurarMueblePorSeleccion() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Ventana::inicializarFramebufferSeleccion(int width, int height) {
	glad_glGenFramebuffers(1, &selectionFBO);
	glad_glBindFramebuffer(GL_FRAMEBUFFER, selectionFBO);
	// Crear la textura para almacenar colores �nicos
	glad_glGenTextures(1, &selectionTexture);
	glad_glBindTexture(GL_TEXTURE_2D, selectionTexture);
	glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, selectionTexture, 0);

	// Crear un Renderbuffer para el depth buffer
	GLuint depthRenderbuffer;
	glad_glGenRenderbuffers(1, &depthRenderbuffer);
	glad_glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	glad_glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glad_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);


	if (glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Error: Framebuffer de selecci�n no est� completo." << std::endl;
	}

	glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
/*==============================================*/

void Ventana::centrarPantallaPrincipal(GLFWwindow*& windows) {
	// Inicializar GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Error al inicializar GLFW.");
	}


	windows = glfwCreateWindow(Ventana::screenWidth, Ventana::screenHeight, "Modelamiento: Interior de Hogar - Muebles", NULL, NULL);
	if (!windows) {
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicaci�n.");
	}
	int actualWidth, actualHeight;
	glfwGetFramebufferSize(windows, &actualWidth, &actualHeight);
	if (Ventana::screenWidth != actualWidth) {
		Ventana::screenWidth = actualWidth;
	}
	if (Ventana::screenHeight != actualHeight) {
		Ventana::screenHeight = actualHeight;
	}
	// Calcular valores de la pantalla
	const GLFWvidmode* viewMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (!viewMode) {
		throw std::runtime_error("No se pudo obtener la informaci�n del modo de video del monitor primario.");
	}
	const int screenWidthWin = viewMode->width;
	const int screenHeightWin = viewMode->height;

	// Calculando posici�n x e y de la pantalla
	const int screenPositionX = (screenWidthWin - Ventana::screenWidth) / 2;
	const int screenPositionY = (screenHeightWin - Ventana::screenHeight) / 2;

	// Permite cambiar la posici�n de la ventana creada con glfwCreateWindow
	glfwSetWindowPos(windows, screenPositionX, screenPositionY);

	// Establece como contexto actual, la ventana que se ha creado y en donde se ejecutar� el c�digo 
	// siguiente al elemento window (actual)
	glfwMakeContextCurrent(windows);


	// Inicializar GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwDestroyWindow(windows);
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicaci�n.");
	}

}
