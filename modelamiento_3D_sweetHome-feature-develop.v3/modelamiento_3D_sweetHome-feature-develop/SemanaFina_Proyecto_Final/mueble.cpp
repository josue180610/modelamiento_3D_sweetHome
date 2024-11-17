#include "mueble.h"
#include <GLFW/glfw3.h>

void dibujarCubo(float ancho, float alto, float profundidad) {
    glBegin(GL_QUADS);

    // Cara frontal
    glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
    glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glVertex3f(-ancho / 2, alto / 2, profundidad / 2);

    // Cara trasera
    glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
    glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);

    // Cara izquierda
    glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
    glVertex3f(-ancho / 2, alto / 2, profundidad / 2);
    glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);

    // Cara derecha
    glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, -profundidad / 2);

    // Cara superior
    glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glVertex3f(-ancho / 2, alto / 2, profundidad / 2);

    // Cara inferior
    glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);

    glEnd();
}
