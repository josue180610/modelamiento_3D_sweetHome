#include "oficina.h"
#include "mueble.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include "configuracion.h"
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas


#ifndef M_PI
#define M_PI 3.14159265358979323846 // Definir M_PI si no está definido
#endif

const float oficinaXMin = -3.0f, oficinaXMax = 3.5f; // Límites en el eje X
const float oficinaZMin = -3.0f, oficinaZMax = 3.0f; // Límites en el eje Z

std::vector<Mueble> muebles;
int muebleSeleccionado = 0;
//
// glBindTexture(GL_TEXTURE_2D, cfg.cargarTextura("textures/pisos/textura-piso-01.jpg")); // enlaza la presente textura (de la estructura)
GLuint salaParedesLaterales;
GLuint salaParedFrontalAtras;
GLuint salaPiso;
GLuint objetos[2];
Configuracion cfg = Configuracion();

void inicializarMuebles() {
    // id,x, y, z, ancho, alto, profundidad, color
    // Crear y agregar una mesa al vector de muebles
    //muebles.push_back({ -1,0.75f, 0.4f, 0.0f, 1.0f, -1.25f, 0.8f, {0.6f, 0.3f, 0.1f},cfg.cargarTextura("textures/objetos/cocina/mesa_cocina_01.png") });
    // Crear y agregar una silla
    //muebles.push_back({ -1,-2.5f, 1.0f, -1.5f, 1.2f, -2.5f, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/mesa_cocina_01.png") });

    // Crear y agregar un armario
    // muebles.push_back({ -1,-1.0f, 1.0f, -1.5f, 1.2f, -2.5f, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/cocina.png") }); //
    float positionH = 2.5f;
    float positionW = 1.2f;
    float positionX = 2.5f;
    float positionY = 1.25f;
    float positionZ = 2.5f;
    muebles.push_back({ -1,positionX, positionY, -positionZ, positionW, -positionH, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/refrigeradora.png") });// inferior esquina derecha 
    muebles.push_back({ -1,-positionX, positionY, positionZ, positionW, -positionH, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/refrigeradora.png") }); // superior esquina izquierda
    muebles.push_back({ -1,positionX, positionY, positionZ, positionW, -positionH, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/refrigeradora.png") }); // superior esquina derecha
    muebles.push_back({ -1,-positionX, positionY, -positionZ, positionW, -positionH, 0.5f,{0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/refrigeradora.png") });// inferior esquina izquierda 

    // objeto del centro - mesa
    muebles.push_back({ -1,0.0, 0.75f, 1.25f, 1.2f, -1.5f, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/cocina.png") });// mesa de centro

    // mueble en pared frontal tracera
    muebles.push_back({ -1,0.0, 0.55f, -1.25f, 2.25f, -1.05f, 0.5f, {0.5f, 0.4f, 0.3f},cfg.cargarTextura("textures/objetos/cocina/cocina.png") });// mesa de centro


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
    glPushMatrix(); // Guardar la matriz de transformación actual
    //glColor3f(0.8f, 0.8f, 0.8f); // Establecer el color del suelo (gris claro)
    
    glBegin(GL_QUADS);

    // Dibujar el suelo como un cuadrado grande
    glTexCoord2f(0.0f, 0.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMin);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(oficinaXMax, 0.0f, oficinaZMax);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(oficinaXMin, 0.0f, oficinaZMax);
        
    glDisable(GL_TEXTURE_2D);
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

void dibujarMueble(const Mueble& mueble,float objectX, float objectY) {
    glPushMatrix();
    glTranslatef(mueble.x, mueble.y, mueble.z);
    //glTranslatef(objectX, objectY, 0.0f);
    //glColor3f(mueble.color[0], mueble.color[1], mueble.color[2]);
    dibujarCubo(mueble.ancho, mueble.alto, mueble.profundidad,mueble.textura);
    glPopMatrix();
}
// Nueva función para dibujar la pared izquierda
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

// Función modificada para dibujar la pared frontal (antes era la pared trasera)
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

// Función para dibujar la pared derecha
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