

#include "configuracion.h"
#include "movimentos.h"
#include <stdexcept>


Configuracion::Configuracion() {}

void Configuracion::inicializarOpenGL() {
	glEnable(GL_DEPTH_TEST); // habilitación del test de profundidad.
	glEnable(GL_LIGHTING); // habilitar la iluminación
	glEnable(GL_COLOR_MATERIAL); // habilitar los colores materiales.

	//Configuramos la luz ambiental
	GLfloat luzAmbiente[] = { 1.0f,1.0f,1.0f,1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	//Posicionar la luz en el espacio
	GLfloat posicionLuz[] = { 1.0f,1.0f,1.0f,0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);
}

