#include "oficina.h"
#include "mueble.h"
#include <cmath>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Definir M_PI si no está definido
#endif

const float oficinaXMin = -3.0f, oficinaXMax = 3.5f; // Límites en el eje X
const float oficinaZMin = -3.0f, oficinaZMax = 3.0f; // Límites en el eje Z

std::vector<Mueble> muebles;

// Texturas principales del entorno(sala)
GLuint salaParedesLaterales;
GLuint salaParedFrontalAtras;
GLuint salaPiso;

int muebleSeleccionado = -1;  // valor que desees asignar por defecto

using namespace std;

GLuint cargarTextura(const char* path) {
    int w, h, ch; // ancho, alto y canal: valores por referencia
    unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
    if (!data) {
        printf("Error al cargar la textura\n");// se notifica el error
        glfwTerminate();
        throw std::runtime_error("Error al inicializar la aplicación.");
    }

    // Generar y enlazar la textura.
    GLuint textura;
    glGenTextures(1, &textura);// genera un único objeto de textura en OpenGL y almacena su identificador en texturaID.
    glBindTexture(GL_TEXTURE_2D, textura); // vincula esta textura a la unidad de textura 2D

    // Especificar los parametros de la textura (repetición, ubicaçión y comportamiento).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Cargar los datos de la imágen en la textura.
    if (ch == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (ch == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data); // Liberamos la imagen de la memoria.
    return textura;
}

// Metodo utilizado para dibujar los muebles.
void inicializarMuebles() {
    // id,x, y, z, ancho, alto, profundidad, color
    float positionH = 2.5f;
    float positionW = 1.2f;
    float positionX = 2.5f;
    float positionY = 1.25f;
    float positionZ = 2.5f;
    float rotationY = 90.0f;
    float posicionPegadoPared = oficinaZMax - 0.265f;
    float posicionPegadoParedLateral = 1.65f;
    //Refrigeradora
    muebles.push_back({ 0, 2.85f, 1.25f, -posicionPegadoPared, positionW, -positionH, 0.5f, {0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/cocina/refrigeradora.png"), 0.0f });
    //Mueble de cocina
    muebles.push_back({ 1, -posicionPegadoParedLateral, 0.75f, -posicionPegadoPared, 2.5f, -1.5f, 0.5f, {0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/cocina/mueble-cocina-mesa.png"), 0.0f });
    //Cocina
    muebles.push_back({ 2, 0.255F, 0.75f, -posicionPegadoPared, positionW, -(positionH - 1.0f), 0.5f,{0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/cocina/cocina.png"), 0.0f });
    //Campana
    muebles.push_back({ 3, 0.255F, 2.38f, -posicionPegadoPared, positionW, -(positionH - 1.5f), 0.5f,{0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/cocina/campana.png"), 0.0f });
    //Minibar
    muebles.push_back({ 4, 1.55F, 0.75f, -posicionPegadoPared, (positionW+0.225f), -(positionH - 1.0f), 0.5f,{0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/sala/minibar.png"), 0.0f });
    //Televisor
    muebles.push_back({ 5, -2.89f, 1.4f, 1.25f, 2.5f, -1.2, 0.1f, {0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/sala/televisor.png"), 90.0f });
    //Mueble para tv
    muebles.push_back({ 6, -2.8f, 0.25f, 1.25f, 2.5f, -0.45, 0.25f, {0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/sala/mueble-tv.png"), 90.0f });
    //Sofa
    muebles.push_back({ 7, 3.25f, 0.55f, 1.25f, 2.25f, -1.0, 0.25f,{0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/sala/sala-de-estar.png"), 90.0f });
    //Isla para cocina
    muebles.push_back({ 8, -0.65f, 0.825f,-0.85f, 4.5f, -1.5f, 0.5f, {0.5f, 0.4f, 0.3f},cargarTextura("textures/objetos/sala/isla-cocina.png"), 0.0f });
    // Cargar texturas
    salaPiso = cargarTextura("textures/pisos/textura-piso-05.jpg"); // piso
    salaParedesLaterales = cargarTextura("textures/paredes/textura-pared-05.jpg"); // paredes laterales
    salaParedFrontalAtras = cargarTextura("textures/paredes/textura-pared-01.jpg"); // pared tracera

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

//Permite el movimiento en los ejes x,y,z de los objetos
void procesarEntrada(GLFWwindow* window, int indice) {
    const float limiteAuxiliarMovimiento = 0.05f;
    const float velocidadMovimiento = 0.001f; // Velocidad de movimiento del mueble
    const float velocidadRotacion = 0.025; // Velocidad de rotación del mueble
 
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

void dibujarMueble(const Mueble& mueble, float objectX, float objectY) {
    glPushMatrix();
    glTranslatef(mueble.x, mueble.y, mueble.z);
    glRotatef(mueble.anguloRotacion, 0.0f, 1.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
    // Rotar el mueble en el eje Y (para cambiar su orientación)
    //glTranslatef(objectX, objectY, 0.0f);
    //glColor3f(mueble.color[0], mueble.color[1], mueble.color[2]);
    dibujarCubo(mueble.ancho, mueble.alto, mueble.profundidad, mueble.textura);
    glPopMatrix();
}

void dibujarMueblePersonalizado(const Mueble& mueble, float objectX, float objectY)
{
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