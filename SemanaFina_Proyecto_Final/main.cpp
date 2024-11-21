#include <GLFW/glfw3.h>
#include "oficina.h"
#include "configuracion.h"
#include <iostream>

float lastMouseX = 0.0f;
float lastMouseY = 0.0f;
float objectX = 0.0f;
float objectY = 0.0f;
float sensibilidad = 0.01f;
bool isDragging = false;
float rotacionX = 0.0f;
float rotacionY = 0.0f;
float rotacionZ = 2.5f;



void moverPantalla(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotacionX -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotacionX += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) rotacionY -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) rotacionY += 0.05f;
}

GLuint textura;
void obtenerPosicionUltimaMouse(GLFWwindow* window, double xCurrentpos, double yCurrentpos) {
    if (isDragging) {
        /*Procedemos a calcular la diferencia entre la posición final y actual*/
        float deltaX = static_cast<float>(xCurrentpos - lastMouseX);
        float deltaY = static_cast<float>(yCurrentpos - lastMouseY);

        objectX += deltaX * sensibilidad; // 0.01f es la sensibilidad de movimiento del mouse en la posición X
        objectY -= deltaY * sensibilidad;

        /*Actualizar la nueva posición final*/
        lastMouseX = static_cast<float>(xCurrentpos);
        lastMouseY = static_cast<float>(yCurrentpos);

    }
}

void activarMovimientoPorMouse(GLFWwindow* window, int buttonActive, int actionPress, int mods) {
    /*Validar si tenemos apretado el click izquierdo*/
    if (buttonActive == GLFW_MOUSE_BUTTON_LEFT && actionPress == GLFW_PRESS) {
        isDragging = true;
        // Obtener la posición inicial del mouse al presionar
        double xLastMouseX = static_cast<double>(lastMouseX);
        double yLastMouseY = static_cast<double>(lastMouseY);
        glfwGetCursorPos(window, &xLastMouseX, &yLastMouseY);
        lastMouseX = static_cast<float>(xLastMouseX);
        lastMouseY = static_cast<float>(yLastMouseY);
    }
    else if (actionPress == GLFW_RELEASE) {
        isDragging = false;
    }
}

int main() {
    GLFWwindow* window;
    Configuracion cfg = Configuracion();
    cfg.centrarPantallaPrincipal(window);

    glfwSetCursorPosCallback(window, obtenerPosicionUltimaMouse);
    glfwSetMouseButtonCallback(window, activarMovimientoPorMouse);

    cfg.inicializarOpenGL();

    inicializarMuebles(); // Inicializar los muebles en la oficina
    // Configurar la proyección en perspectiva
    configurarProyeccion();
    float positionH = 1.75f;
    float positionW = 0.5f;
    float positionX = 2.5f;
    float positionY = 1.25f;
    float positionZ = 3.5f;
    // Bucle principal de renderizado
    bool tieneTextura = false;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla y el buffer de profundidad

        procesarEntrada(window); // Procesar entrada del usuario
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
        cfg.dibujarVentana(tieneTextura);
        dibujarParedFrontal();
        
        tieneTextura = true;
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
