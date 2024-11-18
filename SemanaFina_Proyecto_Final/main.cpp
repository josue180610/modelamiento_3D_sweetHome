#include <GLFW/glfw3.h>
#include "oficina.h"
#include "configuracion.h"
int main() {
    GLFWwindow* window;
    Configuracion cfg = Configuracion();
    cfg.centrarPantallaPrincipal(window);
    cfg.inicializarOpenGL();

    inicializarMuebles(); // Inicializar los muebles en la oficina
    // Configurar la proyección en perspectiva
    configurarProyeccion();

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla y el buffer de profundidad

        procesarEntrada(window); // Procesar entrada del usuario

        // Configurar la matriz de modelo-vista
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, -1.0f, -10.0f); // Posicionar la cámara para ver el espacio de la oficina

        dibujarSuelo(); // Dibujar el suelo de la oficina
        dibujarParedIzquierda();
        dibujarParedDerecha();
        dibujarParedFrontal();

        // Dibujar cada mueble en su posición
        for (const auto& mueble : muebles) {
            dibujarMueble(mueble);
        }

        glfwSwapBuffers(window); // Intercambiar los buffers para mostrar el contenido en pantalla
        glfwPollEvents(); // Procesar eventos de la ventana
    }

    glfwTerminate(); // Liberar los recursos de GLFW
    return 0;
}
