#include <GLFW/glfw3.h>
#include <iostream>
#include "ventana.h"
#include "configuracion.h"
#include "oficina.h"

float lastMouseX = 0.0f;
float lastMouseY = 0.0f;
float objectX = 0.0f;
float objectY = 0.0f;
float sensibilidad = 0.01f;
bool isDragging = false;
float rotacionX = 0.0f;
float rotacionY = 0.0f;
float rotacionZ = 2.5f;
GLuint textura;
Mueble* muebleClickSelecionado = nullptr; // Inicializado como nulo por defecto


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Convertir las coordenadas de la ventana a coordenadas del mundo
        // Aquí debes ajustar según tu configuración de cámara y proyección
        float xworld = (float)xpos -535.0f; // Ajusta según tu configuración
        float yworld = (float)ypos + 172.5f; // Ajusta según tu configuración

        // Verificar si el clic ocurrió dentro de los límites del objeto
        for (auto& mueble : muebles) {
            if (xworld >= mueble.x - mueble.ancho / 2 && xworld <= mueble.x + mueble.ancho / 2 &&
                yworld >= mueble.y - mueble.alto / 2 && yworld <= mueble.y + mueble.alto / 2) {
                muebleClickSelecionado = &mueble;
                std::cout << "Objeto seleccionado!" << std::endl;
                break;
            }
        }
    }
}


void moverPantalla(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) rotacionX -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) rotacionX += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) rotacionY -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) rotacionY += 0.05f;
}


int main() {
    GLFWwindow* window;
    Ventana win = Ventana();
    Configuracion cfg = Configuracion();
    win.centrarPantallaPrincipal(window);

    // Registrar la función de callback para eventos de mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);

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
    cfg.inicializarOpenGL();
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla y el buffer de profundidad

        procesarEntrada(window,muebleClickSelecionado); // Procesar entrada del usuario
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
