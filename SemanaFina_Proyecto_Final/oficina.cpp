#include "oficina.h"
#include "mueble.h"
#include <cmath>
#include "ventana.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#ifndef M_PI
#define M_PI 3.14159265358979323846 // Definir M_PI si no est� definido
#endif

const float oficinaXMin = -3.0f, oficinaXMax = 3.5f; // L�mites en el eje X
const float oficinaZMin = -3.0f, oficinaZMax = 3.0f; // L�mites en el eje Z

std::vector<Mueble> muebles;

int muebleSeleccionado = 0;
//
// glBindTexture(GL_TEXTURE_2D, cfg.cargarTextura("textures/pisos/textura-piso-01.jpg")); // enlaza la presente textura (de la estructura)
GLuint salaParedesLaterales;
GLuint salaParedFrontalAtras;
GLuint salaPiso;
GLuint objetos[2];
Ventana cfg = Ventana();

using namespace std;

void inicializarMuebles() {
    // id,x, y, z, ancho, alto, profundidad, color
    //ancho
    float positionH = 2.5f;

    float positionW = 1.2f;
    float positionX = 2.5f;

    //altura
    float positionY = 1.25f;
    float positionZ = 2.5f;

    float rotationY = 90.0f;
    float posicionPegadoPared = oficinaZMax - 0.265f;
    float posicionPegadoParedLateral = 1.65f;
    //Refrigeradora
    muebles.push_back({ 0, 2.85f, 1.25f, -posicionPegadoPared, positionW, -positionH, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/refrigeradora.png"), 0.0f });

    //Mueble de cocina
    muebles.push_back({ 1, -posicionPegadoParedLateral, 0.75f, -posicionPegadoPared, 2.6f, -1.5f, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/mueble-cocina-mesa.png"), 0.0f });

    //Cocina
    muebles.push_back({ 2, 0.255F, 0.75f, -posicionPegadoPared, positionW, -(positionH - 1.0f), 0.5f,{0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/cocina.png"), 0.0f });// mesa de centro

    //Campana
    muebles.push_back({ 3, 0.255F, 2.38f, -posicionPegadoPared, positionW, -(positionH - 1.5f), 0.5f,{0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/campana.png"), 0.0f });// mesa de centro

    //Minibar
    muebles.push_back({ 4, 1.45F, 0.75f, -posicionPegadoPared, 2.25f, -(positionH - 1.0f), 0.5f,{0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/minibar.png"), 0.0f });// mesa de centro

    //Bar
    //muebles.push_back({ -1, -2.89f, 1.25f, -2.35f, 0.5f, -2.5, 0.15f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/bar.png"), 90.0f });

    //Televisor
    muebles.push_back({ 5, -2.89f, 2.25f, 0.5f, 2.5f, -1.2, 0.1f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/televisor.png"), 90.0f });
    muebles.push_back({ 6, -2.8f, 0.25f, 0.5f, 2.5f, -0.35, 0.25f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/mueble-tv.png"), 90.0f });// mesa de centro


    //Sofa
    muebles.push_back({ 7, 3.25f, 0.55f, 0.5f, 2.5f, -1.0, 0.25f,{0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/sala-de-estar.png"), 90.0f });

    //Isla para cocina
    muebles.push_back({ 8, 0.65f, 0.825f,-0.85f, 5.5f, -1.5f, 0.1f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/sala/isla-cocina.png"), 0.0f });


    // Cargar texturas
    salaPiso = cfg.cargarTextura("textures/pisos/textura-piso-05.jpg"); // piso
    salaParedesLaterales = cfg.cargarTextura("textures/paredes/textura-pared-05.jpg"); // paredes laterales
    salaParedFrontalAtras = cfg.cargarTextura("textures/paredes/textura-pared-01.jpg"); // pared tracera

}



void deshabilitarTextura() {
    glDisable(GL_TEXTURE_2D);
}

void dibujarSuelo() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, salaPiso);
    glPushMatrix(); // Guardar la matriz de transformaci�n actual
    //glColor3f(0.8f, 0.8f, 0.8f); // Establecer el color del suelo (gris claro)

    glBegin(GL_QUADS);

    // Dibujar el suelo como un cuadrado grande
    glTexCoord2f(0.0f, 0.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMax);

    glDisable(GL_TEXTURE_2D);
    glEnd();
    glPopMatrix(); // Restaurar la matriz de transformaci�n anterior

}

void procesarEntrada(GLFWwindow* window, Mueble* muebleClickSelecionado) {
    const float limiteAuxiliarMovimiento = 0.05f;
    const float velocidadMovimiento = 0.001f; // Velocidad de movimiento del mueble
    const float velocidadRotacion = 0.05; // Velocidad de rotaci�n del mueble
    // Cambiar el mueble seleccionado al presionar la tecla TAB
    static bool tabPresionado = false;
    if (muebleClickSelecionado) {
        Mueble& mueble = *muebleClickSelecionado;

        // Obtener referencia al mueble actualmente seleccionado
        // Mueble& mueble = muebles[muebleSeleccionado];

        // Mover el mueble en funci�n de las teclas de flecha presionadas, validando los l�mites
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
        bool condicionMovimiento = ((((mueble.z + mueble.profundidad / 2) + limiteAuxiliarMovimiento < oficinaZMax) && ((mueble.z - mueble.profundidad / 2) + limiteAuxiliarMovimiento > oficinaZMin)) &&
            (((mueble.x - mueble.ancho / 2) + limiteAuxiliarMovimiento > oficinaXMin) && ((mueble.x + mueble.ancho / 2) + limiteAuxiliarMovimiento < oficinaXMax)));
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            if (condicionMovimiento) {
                mueble.anguloRotacion += velocidadRotacion;
            }
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {

            if (condicionMovimiento) {
                mueble.anguloRotacion -= velocidadRotacion;
            }
        }

    }
}

void configurarProyeccion() {
    glMatrixMode(GL_PROJECTION); // Seleccionar la matriz de proyecci�n
    glLoadIdentity(); // Reiniciar la matriz de proyecci�n
    float fov = 45.0f; // Campo de visi�n
    float aspect = 800.0f / 600.0f; // Relaci�n de aspecto
    float nearPlane = 0.1f; // Plano cercano
    float farPlane = 100.0f; // Plano lejano
    float top = nearPlane * tan(fov * M_PI / 360.0f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, nearPlane, farPlane); // Configurar la frustum
}

void dibujarMueble(const Mueble& mueble, float objectX, float objectY) {
    glPushMatrix();
    glTranslatef(mueble.x, mueble.y, mueble.z);
    glRotatef(mueble.anguloRotacion, 0.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaci�n
    // Rotar el mueble en el eje Y (para cambiar su orientaci�n)
    //glTranslatef(objectX, objectY, 0.0f);
    //glColor3f(mueble.color[0], mueble.color[1], mueble.color[2]);
    dibujarCubo(mueble.ancho, mueble.alto, mueble.profundidad, mueble.textura);
    glPopMatrix();
}

void dibujarMueblePersonalizado(const Mueble& mueble, float objectX, float objectY)
{
}


// Nueva funci�n para dibujar la pared izquierda
void dibujarParedIzquierda() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, salaParedesLaterales);
    glPushMatrix();
    glBegin(GL_QUADS);

    // Dibujar la pared izquierda (vertical)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMin);        // Esquina inferior frontal
    glTexCoord2f(1.0f, 0.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMax);        // Esquina inferior trasera
    glTexCoord2f(1.0f, 1.0f); glVertex3f(oficinaXMin, 3.0f, oficinaZMax);        // Esquina superior trasera
    glTexCoord2f(0.0f, 1.0f); glVertex3f(oficinaXMin, 3.0f, oficinaZMin);        // Esquina superior frontal

    glDisable(GL_TEXTURE_2D);
    glEnd();
    glPopMatrix();
}

// Funci�n modificada para dibujar la pared frontal (antes era la pared trasera)
void dibujarParedFrontal() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, salaParedFrontalAtras);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(oficinaXMax, 3.0f, oficinaZMin);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(oficinaXMin, 3.0f, oficinaZMin);

    glDisable(GL_TEXTURE_2D);
    glEnd();
    glPopMatrix();
}

// Funci�n para dibujar la pared derecha
void dibujarParedDerecha() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, salaParedesLaterales);
    glPushMatrix();
    glBegin(GL_QUADS);


    glTexCoord2f(0.0f, 0.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMax);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(oficinaXMax, 3.0f, oficinaZMax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(oficinaXMax, 3.0f, oficinaZMin);

    glDisable(GL_TEXTURE_2D);
    glEnd();
    glPopMatrix();
}