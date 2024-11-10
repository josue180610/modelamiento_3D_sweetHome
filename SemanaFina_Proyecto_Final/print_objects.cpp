
#include<GLFW/glfw3.h>
#include<cmath>
#define STB_IMAGE_IMPLEMENTATION // constante utilizada para implementar texturas
#include "include/stb_image.h" // incluimos la libreria de la carga de imágenes
#include <stdexcept>

using namespace std;

GLuint texturaID[3];
GLuint windowsWall;
float y = 1.0f;
float z = 1.5f;
GLuint loadTextureFile(const char* path) {
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

void loadTextureForWindows() {
    texturaID[0] = loadTextureFile("textures/ventanas/textura-ventana-02.jpg");

}
void loadTextureForWall() {
    texturaID[1] = loadTextureFile("textures/paredes/textura-pared-01.jpg");
}
void loadTextureForFloor() {
    texturaID[2] = loadTextureFile("textures/pisos/textura-piso-03.jpg");
}
void loadTextureImageWallWindows() {
    windowsWall = loadTextureFile("image/ventanas/ventana02.png");
}

//Configurar su visualización, proyección en perspectiva
void configFrustumParameter() {
    // Inicializar la matriz de proyección en perspectiva
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
    glFrustum(left, right, bottom, top, nearClip, farClip); // establece una matriz de proyección en perspectiva
    /*Este tipo de proyección es comúnmente utilizada en gráficos 3D para simular la profundidad*/
 
    loadTextureForWindows();
    loadTextureForWall();
    loadTextureForFloor();
    loadTextureImageWallWindows();

}

void enableTexture() {
    //Función para dibujar un estructura con textura
    glEnable(GL_TEXTURE_2D); //habilitamos el uso de texturas

}

void disableTexture() {
    glDisable(GL_TEXTURE_2D); //deshabilitamos el uso de texturas para otros objetos
    //si los hubiera   
}

void printSquad() {
        glBindTexture(GL_TEXTURE_2D, texturaID[2]); // enlaza la presente textura (de la estructura)
        // con la que hemos cargado, es decir, "texturaID"  
        glBegin(GL_QUADS);
        // piso del establecimiento
        // glColor3f(0.0f, 0.0f, 1.0f); // azul
        
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25f, -y, -z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -y, -z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, -y, (z - 1.0f));
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, -y, (z - 1.0f));

        glEnd();
        //fin de la generación de la estructura
      
}

void printLeftWindowAndWall() {
    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared izquierda
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25f, -y, -z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.25f, -y, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.25f, y, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, y, -z);
    glEnd();
}
void printRightWindowAndWall() {
    glBindTexture(GL_TEXTURE_2D, texturaID[0]); // enlaza la presente textura (de la estructura)
    // con la que hemos cargado, es decir, "texturaID"  
    glBegin(GL_QUADS);
    // pared derecha
    // glColor3f(1.0f, 0.0f, 0.0f); // rojo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.25f, -y, -z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -y, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, y, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.25f, y, -z);
    glEnd();
}


void printRearWallAndAnyObjects() {
    
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
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.25, -y, -1.5f);  // inferior izquierda
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.25f, -y, -1.5f);; // inferior derecha
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.25f, y, -1.5f);;  // superior derecha
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.25f, y, -1.5f); // superior izquierda
    glEnd();

    
}


