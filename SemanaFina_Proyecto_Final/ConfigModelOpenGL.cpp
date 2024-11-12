#include "ConfigModelOpenGL.h"
#include<GLFW/glfw3.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes
#include <stdexcept>

ConfigModelOpenGL::ConfigModelOpenGL() {
	// Inicialización de GLFW (opcional aquí si se desea que se inicialice solo una vez)
	
	if (!glfwInit()) {
		// Si el entorno no se inicializa correctamente
		throw std::runtime_error("Error al inicializar GLFW.");// termina el programa y devuelve un error
	}
};

void ConfigModelOpenGL::initWindowsCenter(GLFWwindow*& windows) {
	// Inicializar GLFW
	if (!glfwInit()) {
		throw std::runtime_error("Error al inicializar GLFW.");
	}
	// Tamaño de la ventana
	int windowWidth = 840;
	int windowHeight = 480;

	windows = glfwCreateWindow(windowWidth, windowHeight, "Modelamiento: Interior de Hogar - Muebles", NULL, NULL);
	if (!windows) {
		glfwTerminate();
		throw std::runtime_error("Error al inicializar la aplicación.");
	}

	// Calcular valores de la pantalla
	const GLFWvidmode* viewMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
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
}

 void ConfigModelOpenGL::inicializarOpenGL() {
	 //prepara el entorno para el trazado y la visualización de un sólido
	 glEnable(GL_DEPTH_TEST); //habilitar el test de profunidad
	 glEnable(GL_LIGHTING); //habilitar la iluminación
	 // glEnable(GL_LIGHT0); //habilitar la luz 0
	 glEnable(GL_COLOR_MATERIAL); //habilitar colores de materiales

	 //Configurar la luz difusa
	 //GLfloat luzDifusa[] = { 1.0f,1.0f,1.0f,1.0f }; //luz blanca
	 //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa); //aplicar luz de difusa

	 //Configuramos la luz ambiental
	 GLfloat luzAmbiente[] = { 1.0f,1.0f,1.0f,1.0f };
	 glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	 //Posicionar la luz en el espacio
	 GLfloat posicionLuz[] = { 1.0f,1.0f,1.0f,0.0f };
	 glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz); //Aplicar posición de la luz

 }

 GLuint ConfigModelOpenGL::loadTextureFile(const char* path, GLuint& texturaId) {
	 // Cargar la imagen utilizando la librería stb_image
	 int w, h, ch; // ancho, alto y canales
	 unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
	 if (!data) {
		 printf("Error al cargar la textura\n");// se notifica el error
		 glfwTerminate();
		 throw std::runtime_error("Error al inicializar la aplicación.");
	 }

	 // Generar y enlazar la textura.
	 glGenTextures(1, &texturaId);// genera un único objeto de textura en OpenGL y almacena su identificador en texturaID.
	 glBindTexture(GL_TEXTURE_2D, texturaId); // vincula esta textura a la unidad de textura 2D

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
	 return texturaId;
 }



//Configurar su visualización, proyección en perspectiva

void ConfigModelOpenGL::configFrustumParameter() {
	 // Inicializar la matriz de proyección en perspectiva
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 float fov = 45.0f;
	 float aspect = 640.0f / 480.0f;
	 float nearClip = 0.1f;
	 float farClip = 10.0f;
	 float top = tan(fov * 3.1416 / 360.0) * nearClip;
	 float bottom = -top;
	 float right = top * aspect;
	 float left = -right;
	 glFrustum(left, right, bottom, top, nearClip, farClip); // establece una matriz de proyección en perspectiva
	 /*Este tipo de proyección es comúnmente utilizada en gráficos 3D para simular la profundidad*/

 }
