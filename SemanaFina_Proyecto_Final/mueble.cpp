#include "mueble.h"
#include <GLFW/glfw3.h>
#include <string>
#include "configuracion.h"

void dibujarCubo(float ancho, float alto, float profundidad, std::string texturaObjeto) {
    
    Configuracion cfg = Configuracion();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,cfg.cargarTextura(texturaObjeto.c_str()));
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

    glDisable(GL_TEXTURE_2D);
}
