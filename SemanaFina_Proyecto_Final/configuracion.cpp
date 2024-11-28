

#include "configuracion.h"
#include "movimentos.h"
#include <stdexcept>






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
	//glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz); //Aplicar posición de la luz
}

