#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ventana.h"
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes

using namespace std;

void Ventana::centrarPantallaPrincipal(GLFWwindow*& windows) {
	// Inicializar GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Error al inicializar GLFW.");
	}
	// Tamaño de la ventana
	int windowWidth = 1024;
	int windowHeight = 640;

	windows = glfwCreateWindow(windowWidth, windowHeight, "Modelamiento: Interior de Hogar - Muebles", NULL, NULL);
	if (!windows) {
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicación.");
	}

	// Calcular valores de la pantalla
	const GLFWvidmode* viewMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (!viewMode) {
		throw std::runtime_error("No se pudo obtener la información del modo de video del monitor primario.");
	}
	const int screenWidth = viewMode->width;
	const int screenHeight = viewMode->height;

	// Calculando posición x e y de la pantalla
	const int screenPositionX = (screenWidth - windowWidth) / 2;
	const int screenPositionY = (screenHeight - windowHeight) / 2;

	// Permite cambiar la posición de la ventana creada con glfwCreateWindow
	glfwSetWindowPos(windows, screenPositionX, screenPositionY);

	// Establece como contexto actual, la ventana que se ha creado y en donde se ejecutará el código 
	// siguiente al elemento window (actual)
	glfwMakeContextCurrent(windows);


	// Inicializar GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwDestroyWindow(windows);
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicación.");
	}

	// 6. Configurar el viewport
	/*
	 Esto asegura que las dimensiones de la ventana estén correctamente aplicadas.
	*/
	glViewport(0, 0, 800, 600);

}

GLuint Ventana::cargarTextura(const char* path) {
	int w, h, ch; // ancho, alto y canal: valores por referencia
	unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
	if (!data) {
		printf("Error al cargar la textura\n");// se notifica el error
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicación.");
	}

	// Generar y enlazar la textura.
	GLuint textura;
	glGenTextures(1, &textura);// genera un único objeto de textura en OpenGL y almacena su identificador en texturaID.
	glBindTexture(GL_TEXTURE_2D, textura); // vincula esta textura a la unidad de textura 2D

	// Especificar los parametros de la textura (repetición, ubicaçión y comportamiento).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Cargar los datos de la imágen en la textura.
	if (ch == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (ch == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data); // Liberamos la imagen de la memoria.
	return textura;
}