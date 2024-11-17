#include "oficina.h"
#include "mueble.h"
#include <GLFW/glfw3.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Definir M_PI si no está definido
#endif

const float oficinaXMin = -3.5f, oficinaXMax = 3.5f; // Límites en el eje X
const float oficinaZMin = -3.0f, oficinaZMax = 3.0f; // Límites en el eje Z

std::vector<Mueble> muebles;
int muebleSeleccionado = 0;

void inicializarMuebles() {
    // Crear y agregar una mesa al vector de muebles
    muebles.push_back({ 0.0f, 0.4f, 0.0f, 1.5f, 0.8f, 0.8f, {0.6f, 0.3f, 0.1f} });
    // Crear y agregar una silla
    muebles.push_back({ -1.5f, 0.3f, 0.0f, 0.5f, 0.6f, 0.5f, {0.2f, 0.2f, 0.8f} });
    // Crear y agregar un armario
    muebles.push_back({ 1.5f, 1.0f, -1.5f, 1.0f, 2.0f, 0.5f, {0.5f, 0.4f, 0.3f} });
}

void dibujarSuelo() {
    glPushMatrix(); // Guardar la matriz de transformación actual
    glColor3f(0.8f, 0.8f, 0.8f); // Establecer el color del suelo (gris claro)
    glBegin(GL_QUADS);

    // Dibujar el suelo como un cuadrado grande
    glVertex3f(oficinaXMin, 0.0f, oficinaZMin);
    glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glVertex3f(oficinaXMax, 0.0f, oficinaZMax);
    glVertex3f(oficinaXMin, 0.0f, oficinaZMax);

    glEnd();
    glPopMatrix(); // Restaurar la matriz de transformación anterior
}

void procesarEntrada(GLFWwindow* window) {
    const float velocidadMovimiento = 0.001f; // Velocidad de movimiento del mueble

    // Cambiar el mueble seleccionado al presionar la tecla TAB
    static bool tabPresionado = false;
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        if (!tabPresionado) {
            muebleSeleccionado = (muebleSeleccionado + 1) % muebles.size(); // Cambiar al siguiente mueble
            tabPresionado = true; // Evitar múltiples activaciones mientras se presiona la tecla
        }
    }
    else {
        tabPresionado = false; // Permitir cambio nuevamente al soltar TAB
    }

    // Obtener referencia al mueble actualmente seleccionado
    Mueble& mueble = muebles[muebleSeleccionado];

    // Mover el mueble en función de las teclas de flecha presionadas, validando los límites
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (mueble.x - mueble.ancho / 2 > oficinaXMin) {
            mueble.x -= velocidadMovimiento;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (mueble.x + mueble.ancho / 2 < oficinaXMax) {
            mueble.x += velocidadMovimiento;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (mueble.z - mueble.profundidad / 2 > oficinaZMin) {
            mueble.z -= velocidadMovimiento;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (mueble.z + mueble.profundidad / 2 < oficinaZMax) {
            mueble.z += velocidadMovimiento;
        }
    }
}

void configurarProyeccion() {
    glMatrixMode(GL_PROJECTION); // Seleccionar la matriz de proyección
    glLoadIdentity(); // Reiniciar la matriz de proyección
    float fov = 45.0f; // Campo de visión
    float aspect = 800.0f / 600.0f; // Relación de aspecto
    float nearPlane = 0.1f; // Plano cercano
    float farPlane = 100.0f; // Plano lejano
    float top = nearPlane * tan(fov * M_PI / 360.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, nearPlane, farPlane); // Configurar la frustum
}

void dibujarMueble(const Mueble& mueble) {
    glPushMatrix();
    glTranslatef(mueble.x, mueble.y, mueble.z);
    glColor3f(mueble.color[0], mueble.color[1], mueble.color[2]);
    dibujarCubo(mueble.ancho, mueble.alto, mueble.profundidad);
    glPopMatrix();
}
// Nueva función para dibujar la pared izquierda
void dibujarParedIzquierda() {
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Color de la pared (gris claro)
    glBegin(GL_QUADS);

    // Dibujar la pared izquierda (vertical)
    glVertex3f(oficinaXMin, 0.0f, oficinaZMin);        // Esquina inferior frontal
    glVertex3f(oficinaXMin, 0.0f, oficinaZMax);        // Esquina inferior trasera
    glVertex3f(oficinaXMin, 3.0f, oficinaZMax);        // Esquina superior trasera
    glVertex3f(oficinaXMin, 3.0f, oficinaZMin);        // Esquina superior frontal

    glEnd();
    glPopMatrix();
}

// Función modificada para dibujar la pared frontal (antes era la pared trasera)
void dibujarParedFrontal() {
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Color gris claro
    glBegin(GL_QUADS);
    glVertex3f(oficinaXMin, 0.0f, oficinaZMin);
    glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glVertex3f(oficinaXMax, 3.0f, oficinaZMin);
    glVertex3f(oficinaXMin, 3.0f, oficinaZMin);
    glEnd();
    glPopMatrix();
}

// Función para dibujar la pared derecha
void dibujarParedDerecha() {
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Color gris claro
    glBegin(GL_QUADS);
    glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glVertex3f(oficinaXMax, 0.0f, oficinaZMax);
    glVertex3f(oficinaXMax, 3.0f, oficinaZMax);
    glVertex3f(oficinaXMax, 3.0f, oficinaZMin);
    glEnd();
    glPopMatrix();
}