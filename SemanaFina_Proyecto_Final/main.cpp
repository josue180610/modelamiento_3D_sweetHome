#include <GLFW/glfw3.h>
#include <iostream>
#include "ventana.h"
#include "configuracion.h"
#include "oficina.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;

int selectedObjectIndex = -1;
float movimientoVelocidad = 0.001f;
float rotacionVelocidad = 0.05f;

float objectX = 0.0f;
float objectY = 0.0f;
float rotacionX = 0.0f;
float rotacionY = 0.0f;
float rotacionZ = 2.5f;
bool muebleClickSelecionado = false; // Inicializado como nulo por defecto
Ventana win = Ventana();
int selectedID = -1;

//Metodo para mover la estructura que hace referencia a la sala
void moverPantalla(GLFWwindow* window) {
    float pantallaSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        rotacionX -= pantallaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        rotacionX += pantallaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        rotacionY -= pantallaSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        rotacionY += pantallaSpeed;
    }
}

//Metodo para asignarle numeros a los objetos
void manejarSeleccion(GLFWwindow* window) {
    for (int i = 0; i < muebles.size(); i++) {
        if (glfwGetKey(window, GLFW_KEY_0 + i) == GLFW_PRESS) {
            selectedObjectIndex = i;
            //mostrarInformacionObjeto();
        }
    }
}
//Metodo para realizar el movimiento de los objetos
void manejarMovimiento(GLFWwindow* window) {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < muebles.size()) {
        // Permite realizar el movimiento de un mueble, en base al indice de su posición.
        // El mueble solo se puede mover hasta cierto límite, respetando su entorno.
        procesarEntrada(window, selectedObjectIndex); 

    }
}


int main() {
    GLFWwindow* window;
    Configuracion cfg = Configuracion();
    // Inicializar la variable windows y centrar dicha pantalla
    win.centrarPantallaPrincipal(window); 
    // Inicializar los muebles en la oficina
    inicializarMuebles(); 
    // Configurar la proyección en perspectiva
    configurarProyeccion();
    cfg.inicializarOpenGL();


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla y el buffer de profundidad

        manejarSeleccion(window);
        manejarMovimiento(window);

        // Configurar la matriz de modelo-vista
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -10.0f); // Posicionar la cámara para ver el espacio de la oficina
        moverPantalla(window);
        glRotatef(rotacionX, 1.0f, 0.0f, 0.0f); //rotar el cubo para una mejor visualizaciòn
        glRotatef(rotacionY, 0.0f, 1.0f, 0.0f);

        dibujarSuelo(); // Dibujar el suelo de la oficina
        dibujarParedIzquierda();
        dibujarParedDerecha();
        dibujarParedFrontal();

        // Dibujar cada mueble en su posición
        for (const auto& mueble : muebles) {
            dibujarMueble(mueble, objectX, objectY);
        }

        glfwSwapBuffers(window); // Intercambiar los buffers para mostrar el contenido en pantalla
        glfwPollEvents(); // Procesar eventos de la ventana
    }

    glfwTerminate(); // Liberar los recursos de GLFW
    return 0;

}
