#ifndef MUEBLE_H
#define MUEBLE_H
#include <string>
#include <GLFW/glfw3.h>

struct Mueble {
    int id; // identificador de objeto
    float x, y, z;        // Posición del mueble en los ejes X, Y y Z
    float ancho, alto, profundidad; // Dimensiones del mueble (ancho, alto y profundidad)
    float color[3];       // Color del mueble (valores RGB)
    GLuint textura;
    float anguloRotacion;
};
void dibujarCubo(float ancho, float alto, float profundidad,GLuint textura);
void dibujarCuboPersonalizado(float ancho, float alto, float profundidad, GLuint textura);

#endif
