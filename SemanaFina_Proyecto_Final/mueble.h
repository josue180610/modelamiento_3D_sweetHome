#ifndef MUEBLE_H
#define MUEBLE_H
#include <string>
struct Mueble {
    float x, y, z;        // Posici�n del mueble en los ejes X, Y y Z
    float ancho, alto, profundidad; // Dimensiones del mueble (ancho, alto y profundidad)
    float color[3];       // Color del mueble (valores RGB)
    std::string texturaObjeto;
};

void dibujarCubo(float ancho, float alto, float profundidad, std::string texturaObjeto);

#endif