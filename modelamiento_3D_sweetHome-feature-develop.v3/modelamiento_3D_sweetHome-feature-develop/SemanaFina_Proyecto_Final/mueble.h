#ifndef MUEBLE_H
#define MUEBLE_H

struct Mueble {
    float x, y, z;        // Posición del mueble en los ejes X, Y y Z
    float ancho, alto, profundidad; // Dimensiones del mueble (ancho, alto y profundidad)
    float color[3];       // Color del mueble (valores RGB)
};

void dibujarCubo(float ancho, float alto, float profundidad);

#endif
