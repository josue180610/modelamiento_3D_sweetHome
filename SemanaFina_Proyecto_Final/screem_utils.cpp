#include <GLFW/glfw3.h>
#include <stdexcept>

using namespace std;

GLFWwindow* initWindowsCenter() {
	// Tamaño de la ventana
	int windowWidth = 640;
	int windowHeight = 480;

	GLFWwindow* windows = glfwCreateWindow(windowWidth, windowHeight, "Modelamiento: Interior de Hogar - Muebles", NULL, NULL);
	if (!windows) {
		glfwTerminate();
		throw runtime_error("Error al inicializar la aplicación.");
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
	return windows;
}


void inicializarOpenGL() {
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
