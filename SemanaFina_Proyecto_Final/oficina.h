#ifndef OFICINA_H
#define OFICINA_H

#include "mueble.h"
#include <vector>
#include <GLFW/glfw3.h>

// L�mites del espacio de la oficina
extern const float oficinaXMin, oficinaXMax, oficinaZMin, oficinaZMax;

extern std::vector<Mueble> muebles; // Vector para almacenar todos los muebles en la oficina
extern int muebleSeleccionado;  // �ndice del mueble actualmente seleccionado para mover

// Funciones relacionadas con la oficina y los muebles
void inicializarMuebles();
void dibujarSuelo();
void procesarEntrada(GLFWwindow* window);
void configurarProyeccion();
void dibujarMueble(const Mueble& mueble);
void dibujarParedIzquierda();
void dibujarParedDerecha();
void dibujarParedFrontal();

#endif