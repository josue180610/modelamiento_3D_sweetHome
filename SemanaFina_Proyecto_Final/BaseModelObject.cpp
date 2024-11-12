#include "BaseModelObject.h"


#include<GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes
#include <stdexcept>

using namespace std;

BaseModelObject::BaseModelObject(float _y, float _z, float _xrl, float _rotacionX, float _rotacionY) {
	y = _y;
	z = _z;
	xrl = _xrl;
    rotacionX = _rotacionX;
    rotacionY = _rotacionY;
    rotacionZ = 3.0f;
}

void BaseModelObject::procesarEntrada(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) rotacionX -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) rotacionX += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) rotacionY -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) rotacionY += 0.05f;
    // if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) rotacionZ += 0.001f; // retroceder objeto
    // if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) rotacionZ -= 0.001f; // avanzar objeto
}

GLuint BaseModelObject::loadTextureFile(const char* path) {
    // Cargar la imagen utilizando la librería stb_image
    int w, h, ch; // ancho, alto y canales
    unsigned char* data = stbi_load(path, &w, &h, &ch, 0);
    if (!data) {
        printf("Error al cargar la textura\n");// se notifica el error
        glfwTerminate();
        throw runtime_error("Error al inicializar la aplicación.");
    }

    // Generar y enlazar la textura.
    GLuint texturaID;
    glGenTextures(1, &texturaID);// genera un único objeto de textura en OpenGL y almacena su identificador en texturaID.
    glBindTexture(GL_TEXTURE_2D, texturaID); // vincula esta textura a la unidad de textura 2D

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
    return texturaID;
}

void BaseModelObject::loadTextureForWindows(int n, char* path) {
    texturaID[n] = loadTextureFile(path);
}

void BaseModelObject ::enableTexture() {
    //Función para dibujar un estructura con textura
    glEnable(GL_TEXTURE_2D); //habilitamos el uso de texturas

}

void BaseModelObject::disableTexture() {
    glDisable(GL_TEXTURE_2D); //deshabilitamos el uso de texturas para otros objetos
    //si los hubiera   
}

void BaseModelObject:: printSquad() {
    glBindTexture(GL_TEXTURE_2D, texturaID[2]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // piso del establecimiento
    // glColor3f(0.0f, 0.0f, 1.0f); // azul

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-xrl, -y, -z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xrl, -y, -z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xrl, -y, (z - 1.0f));
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-xrl, -y, (z - 1.0f));

    glEnd();
    //fin de la generación de la estructura

}



void BaseModelObject::printLeftWindowAndWall() {
    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared izquierda
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-xrl, -y, -z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-xrl, -y, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-xrl, y, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-xrl, y, -z);
    glEnd();
}
void BaseModelObject::printRightWindowAndWall() {
    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared derecha
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo

    glTexCoord2f(0.0f, 0.0f); glVertex3f(xrl, -y, -z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(xrl, -y, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(xrl, y, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(xrl, y, -z);
    glEnd();
}


void BaseModelObject::printRearWallAndAnyObjects() {

    glBindTexture(GL_TEXTURE_2D, texturaID[1]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // Cara frontal
    //glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    //glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    //glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    //glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // pared trasera
    // glColor3f(0.0f, 1.0f, 0.0f); //verde
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.35, -y, -1.5f);  // inferior izquierda
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.35f, -y, -1.5f);; // inferior derecha
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.35f, y, -1.5f);;  // superior derecha
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.35f, y, -1.5f); // superior izquierda
    glEnd();


}

