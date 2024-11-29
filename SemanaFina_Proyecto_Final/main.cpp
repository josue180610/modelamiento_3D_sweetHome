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

int selectedObjectIndex = -1; // Índice del objeto seleccionado (-1 = ninguno)
float movimientoVelocidad = 0.001f;
float rotacionVelocidad = 0.05f;

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
bool muebleClickSelecionado = false; // Inicializado como nulo por defecto
Ventana win = Ventana();
int selectedID = -1;

// Proyección y vista globales
glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

/*Permite normalizar las coordenadas del trazo del click en un entorno 3D para validar si existe o no, 
la intercepción con el cubo 3D*/
glm::vec3 normalizarPosicionVentana(double xpos, double ypos, int screenWidth, int screenHeight,
    const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // Normaliza las coordenadas de pantalla
    float x = (2.0f * xpos) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * ypos) / screenHeight; // Invertir el eje Y
    glm::vec4 rayClip(x, y, -1.0f, 1.0f);

    // Transforma a espacio de vista
    glm::vec4 rayEye = glm::inverse(projectionMatrix) * rayClip;
    rayEye.z = -1.0f; // Ajusta la dirección del rayo
    rayEye.w = 0.0f;

    // Transforma a espacio mundial
    glm::vec3 rayWorld = glm::vec3(glm::inverse(viewMatrix) * rayEye);
    return glm::normalize(rayWorld);
}

//bool intercepcionRayoCubo(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
//    const glm::vec3& boxMin, const glm::vec3& boxMax) {
//    float tMin = (boxMin.x - rayOrigin.x) / rayDirection.x;
//    float tMax = (boxMax.x - rayOrigin.x) / rayDirection.x;
//
//    if (tMin > tMax) std::swap(tMin, tMax);
//
//    float tyMin = (boxMin.y - rayOrigin.y) / rayDirection.y;
//    float tyMax = (boxMax.y - rayOrigin.y) / rayDirection.y;
//
//    if (tyMin > tyMax) std::swap(tyMin, tyMax);
//
//    if ((tMin > tyMax) || (tyMin > tMax)) return false;
//
//    if (tyMin > tMin) tMin = tyMin;
//    if (tyMax < tMax) tMax = tyMax;
//
//    float tzMin = (boxMin.z - rayOrigin.z) / rayDirection.z;
//    float tzMax = (boxMax.z - rayOrigin.z) / rayDirection.z;
//
//    if (tzMin > tzMax) std::swap(tzMin, tzMax);
//
//    if ((tMin > tzMax) || (tzMin > tMax)) return false;
//
//    return true;
//}

//int obtenerPosicionCubo(double xpos, double ypos) {
//
//    /*Proyección en perspectiva*/
//    /*projectionMatrix: Define cómo se proyectan las coordenadas en la pantalla desde la perspectiva de la cámara.*/
//    float fov = glm::radians(45.0f); // Campo de visión en grados
//    float aspectRatio = static_cast<float>(win.screenWidth) / win.screenHeight; // Relación de aspecto
//    float nearPlane = 0.1f; // Distancia mínima visible
//    float farPlane = 100.0f; // Distancia máxima visible
//    glm::mat4 projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
//
//    /*Proyección global de la camara*/
//    /*variables para posición de la cámara*/
//    glm::vec3 cameraPosition = glm::vec3(0.0f, -1.0f, -10.0f); // Cámara en la posición inicial
//    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Punto hacia el que la cámara está mirando
//    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Vecto hacia arriba
//    /*viewMatrix: Define dónde está la cámara y hacia dónde mira en el mundo*/
//    glm::mat4 camaraMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
//
//    glm::vec3 rayOrigin = cameraPosition; // La posición de tu cámara
//    glm::vec3 rayDirection = normalizarPosicionVentana(xpos, ypos, win.screenWidth, win.screenHeight, camaraMatrix, projectionMatrix);
//
//    int selectedID = -1;
//    float closestDistance = FLT_MAX;
//
//    for (const auto& mueble : muebles) {
//
//        // Calcula las esquinas del mueble en base a su posición y dimensiones
//        glm::vec3 boxMin = glm::vec3(mueble.x - (mueble.ancho * 0.55f),
//            mueble.y - (mueble.alto * 0.55f),
//            mueble.z - (mueble.profundidad * 0.55f));
//        glm::vec3 boxMax = glm::vec3(mueble.x + (mueble.ancho * 0.55f),
//            mueble.y + (mueble.alto * 0.55f),
//            mueble.z + (mueble.profundidad * 0.55f));
//
//      
//
//        if (intercepcionRayoCubo(rayOrigin, rayDirection, boxMin, boxMax)) {
//            float distance = glm::length(rayOrigin - boxMin);
//            if (distance < closestDistance) {
//                closestDistance = distance;
//                selectedID = mueble.id;
//            }
//        }
//    }
//
//    return selectedID;
//}

//void obtenerClickDelMouse(GLFWwindow* window, int button, int action, int mods) {
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//        double xpos, ypos;
//        glfwGetCursorPos(window, &xpos, &ypos);
//        cout << "xpos :" << xpos << "ypos :" << ypos << endl;
//        selectedID = obtenerPosicionCubo(xpos, ypos);
//        if (selectedID != -1) {
//            std::cout << "Cubo seleccionado con ID: " << selectedID << std::endl;
//            muebleClickSelecionado = true;
//        }
//        else {
//            std::cout << "No se seleccionó ningún cubo." << std::endl;
//            muebleClickSelecionado = false;
//        }
//    }
//}

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

//void mostrarInformacionObjeto() {
//    if (selectedObjectIndex >= 0 && selectedObjectIndex < muebles.size()) {
//        const Mueble& mueble = muebles[selectedObjectIndex];
//        std::cout << "Objeto seleccionado: " << selectedObjectIndex
//            << " | Posición: (" << mueble.x << ", " << mueble.y << ", " << mueble.z << ")"
//            << " | Dimensiones: (" << mueble.ancho << ", " << mueble.alto << ", " << mueble.profundidad << ")"
//            << std::endl;
//    }
//    else {
//        std::cout << "Ningún objeto seleccionado." << std::endl;
//    }
//}

//Metodo para asignarle numeros a los objetos
void manejarSeleccion(GLFWwindow* window) {
    for (int i = 0; i < 8; i++) {
        if (glfwGetKey(window, GLFW_KEY_1 + i) == GLFW_PRESS) {
            selectedObjectIndex = i;
            //mostrarInformacionObjeto();
        }
    }
}
void manejarMovimiento(GLFWwindow* window) {
    if (selectedObjectIndex >= 0 && selectedObjectIndex < muebles.size()) {
        Mueble& mueble = muebles[selectedObjectIndex];

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) mueble.z -= movimientoVelocidad;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) mueble.z += movimientoVelocidad;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) mueble.x -= movimientoVelocidad;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) mueble.x += movimientoVelocidad;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) mueble.anguloRotacion += rotacionVelocidad;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) mueble.anguloRotacion -= rotacionVelocidad;
    }
}


int main() {
    GLFWwindow* window;
    Configuracion cfg = Configuracion();
    win.centrarPantallaPrincipal(window);

    // Registrar la función de callback para eventos de mouse
    //glfwSetMouseButtonCallback(window, obtenerClickDelMouse);

    inicializarMuebles(); // Inicializar los muebles en la oficina
    // Configurar la proyección en perspectiva
    configurarProyeccion();
    // Bucle principal de renderizado

    // Configurar matrices de proyección y vista
    projectionMatrix = glm::perspective(glm::radians(45.0f), (float)win.screenWidth / (float)win.screenHeight, 0.1f, 100.0f);
    viewMatrix = glm::lookAt(glm::vec3(0.0f, -1.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    bool tieneTextura = false;
    cfg.inicializarOpenGL();


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla y el buffer de profundidad

        manejarSeleccion(window);
        manejarMovimiento(window);

        procesarEntrada(window,muebleClickSelecionado,selectedID); // Procesar entrada del usuario
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
