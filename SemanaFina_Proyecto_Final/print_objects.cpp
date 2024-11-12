#include<GLFW/glfw3.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de im�genes
#include <stdexcept>

using namespace std;

GLuint texturaID[4];

GLuint loadTextureFile(const char* path) {
    // Cargar la imagen utilizando la librer�a stb_image
    int w, h, ch; // ancho, alto y canales
    unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
    if (!data) {
        printf("Error al cargar la textura\n");// se notifica el error
        glfwTerminate();
        throw runtime_error("Error al inicializar la aplicaci�n.");
    }

    // Generar y enlazar la textura.
    GLuint texturaID;
    glGenTextures(1, &texturaID);// genera un �nico objeto de textura en OpenGL y almacena su identificador en texturaID.
    glBindTexture(GL_TEXTURE_2D, texturaID); // vincula esta textura a la unidad de textura 2D

    // Especificar los parametros de la textura (repetici�n, ubica�i�n y comportamiento).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Cargar los datos de la im�gen en la textura.
    if (ch == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (ch == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    stbi_image_free(data); // Liberamos la imagen de la memoria.
    return texturaID;
}

//Configurar su visualizaci�n, proyecci�n en perspectiva
void configFrustumParameter() {
    // Inicializar la matriz de proyecci�n en perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fov = 45.0f;
    float aspect = 640.0f / 480.0f;
    float nearClip = 0.1f;
    float farClip = 10.0f;
    float top = tan(fov * 3.1416 / 360.0) * nearClip;
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    glFrustum(left, right, bottom, top, nearClip, farClip); // establece una matriz de proyecci�n en perspectiva
    /*Este tipo de proyecci�n es com�nmente utilizada en gr�ficos 3D para simular la profundidad*/

    texturaID[0] = loadTextureFile("textures/textura.jpg");
    texturaID[1] = loadTextureFile("textures/cuerpo.jpg");
    texturaID[2] = loadTextureFile("textures/denmin_fabric_02_diff_4k.jpg");
    texturaID[3] = loadTextureFile("textures/cabeza.jpg");

}

void printVentanas() {

    //Crear ventana Pared izquierda
    glBindTexture(GL_TEXTURE_2D, texturaID[2]); // Cargar la textura de la ventana

    glBegin(GL_QUADS);

    // Ventana en la pared izquierda (ajusta las coordenadas seg�n el tama�o y posici�n deseada)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25f, 0.0f, -0.2f);  // inferior izquierda de la ventana
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.25f, 0.0f, 0.2f);   // inferior derecha de la ventana
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.25f, 0.4f, 0.2f);   // superior derecha de la ventana
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, 0.4f, -0.2f);  // superior izquierda de la ventana

    glEnd();

    // Crear ventana en la pared derecha
    glBindTexture(GL_TEXTURE_2D, texturaID[2]); // Cargar la textura de la ventana

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.25f, 0.0f, -0.2f);   // inferior izquierda de la ventana
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, 0.0f, 0.2f);    // inferior derecha de la ventana
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, 0.4f, 0.2f);    // superior derecha de la ventana
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.25f, 0.4f, -0.2f);   // superior izquierda de la ventana

    glEnd();
}

void printCuadro() {
    // Dibujamos el cuadro en la pared frontal
    glBindTexture(GL_TEXTURE_2D, texturaID[3]); // Cargar la textura para el cuadro

    glBegin(GL_QUADS);
    // Cuadro centrado en la pared frontal, ajustado al 50% de la superficie
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.416f, -0.06f, 0.5f);  // inferior izquierda del cuadro
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.416f, -0.06f, 0.5f);   // inferior derecha del cuadro
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.416f, 0.26f, 0.5f);    // superior derecha del cuadro
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.416f, 0.26f, 0.5f);   // superior izquierda del cuadro
    glEnd();
}

void printSquad() {

    //Funci�n para dibujar un estructura con textura
    glEnable(GL_TEXTURE_2D); //habilitamos el uso de texturas



    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  


    glBegin(GL_QUADS);
    // Cara frontal
    //glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    //glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    //glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    //glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // pared trasera
    // glColor3f(0.0f, 1.0f, 0.0f); //verde
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25, -0.5f, -0.5f);  // inferior izquierda
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -0.5f, -0.5f);; // inferior derecha
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, 0.5f, -0.5f);  // superior derecha
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, 0.5f, -0.5f); // superior izquierda

    glEnd();

    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared izquierda
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.25f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.25f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, 0.5f, -0.5f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared derecha
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.25f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.25f, 0.5f, -0.5f);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, texturaID[1]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // piso del establecimiento
    // glColor3f(0.0f, 0.0f, 1.0f); // azul
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, -0.5f, 0.5f);

    glEnd();
    //fin de la generaci�n de la estructura

    printVentanas();
    printCuadro();

    glDisable(GL_TEXTURE_2D); //deshabilitamos el uso de texturas para otros objetos
    //si los hubiera

}