#include "mueble.h"
#include <string>
#include "configuracion.h"

// Metodo encargado de obtener las coordenadas y las texturas para dibujar los cubos
void dibujarCubo(float ancho, float alto, float profundidad, GLuint textura) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);

    // Habilitar mezcla para transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);

    // Cara frontal
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ancho / 2, alto / 2, profundidad / 2);

    // Cara trasera
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);

    // Cara izquierda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-ancho / 2, alto / 2, profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);

    // Cara derecha
    glTexCoord2f(0.0f, 0.0f); glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(ancho / 2, alto / 2, -profundidad / 2);

    // Cara superior
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-ancho / 2, alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ancho / 2, alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(ancho / 2, alto / 2, profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ancho / 2, alto / 2, profundidad / 2);

    // Cara inferior
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(ancho / 2, -alto / 2, -profundidad / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(ancho / 2, -alto / 2, profundidad / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-ancho / 2, -alto / 2, profundidad / 2);

    glEnd();

    glDisable(GL_BLEND); // Deshabilitar mezcla despu�s de dibujar el cubo
    glDisable(GL_TEXTURE_2D);
}
