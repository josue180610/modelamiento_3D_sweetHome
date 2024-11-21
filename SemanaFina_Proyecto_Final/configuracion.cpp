#include "configuracion.h"
#include "movimentos.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes

Configuracion::Configuracion() {

}

void Configuracion::dibujarVentana(bool textura) {

	const float oficinaXMin = -3.0f, oficinaXMax = 3.5f; // Límites en el eje X
	const float oficinaZMin = -3.0f, oficinaZMax = 3.0f; // Límites en el eje Z
	float ventanaXMin = (oficinaXMin + oficinaXMax) / 2.0f - 1.0f; // Centrada, restando la mitad del ancho
	float ventanaXMax = (oficinaXMin + oficinaXMax) / 2.0f + 1.0f; // Centrada, sumando la mitad del ancho
	float ventanaYMin = 0.75f; // A una altura específica desde la base (por ejemplo, 0.75)
	float ventanaYMax = 2.25f; // Altura máxima (ventanaYMin + altura ventana)
	float ventanaZ = oficinaZMin; // Misma profundidad que la pared

	
	// Dibujar la ventana (puedes agregar textura aquí si lo deseas)
	// glColor3f(0.6f, 0.8f, 1.0f); // Color de vidrio de ventana (opcional)
	glBegin(GL_QUADS);
	glVertex3f(ventanaXMin, ventanaYMin, ventanaZ);
	glVertex3f(ventanaXMax, ventanaYMin, ventanaZ);
	glVertex3f(ventanaXMax, ventanaYMax, ventanaZ);
	glVertex3f(ventanaXMin, ventanaYMax, ventanaZ);
	glEnd();
}

GLuint Configuracion::cargarTextura(const char* path) {
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

void Configuracion::inicializarOpenGL() {
	glEnable(GL_DEPTH_TEST); // habilitación del test de profundidad.
	glEnable(GL_LIGHTING); // habilitar la iluminación
	glEnable(GL_COLOR_MATERIAL); // habilitar los colores materiales.

	//Configuramos la luz ambiental
	GLfloat luzAmbiente[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	//Posicionar la luz en el espacio
	GLfloat posicionLuz[] = { 1.0f,1.0f,1.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz); //Aplicar posición de la luz
}

void Configuracion::centrarPantallaPrincipal(GLFWwindow*& windows) {
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