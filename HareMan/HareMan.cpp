#include <GL/glut.h>
#include <windows.h>  // Para reproducir sonido con PlaySound
#include <string>
#include "menu.h"
#include "nivel1.h"

Menu menu;  // Instancia del menú

bool loadingScreen = false;   // Bandera para saber si estamos mostrando la pantalla de carga
bool freezePlayer = false;    // Bandera para congelar el jugador mientras suena la música
int dotCount = 0;             // Contador de puntos
int dotDirection = 1;         // Dirección de los puntos de "Cargando"

// Función para dibujar la pantalla de carga
void drawLoadingScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco para el texto
    glRasterPos2f(400, 300);      // Posición centrada en la ventana

    std::string loadingMessage = "Cargando";

    glPushMatrix();
    glScalef(2.0f, 2.0f, 1.0f);  // Escalar el texto
    for (int i = 0; i < dotCount; i++) {
        loadingMessage += ".";
    }

    for (char c : loadingMessage) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
    glPopMatrix();

    glutSwapBuffers();
}

// Función de actualización para la animación de la pantalla de carga
void updateLoadingScreen(int value) {
    dotCount += dotDirection;
    if (dotCount == 3) dotDirection = -1;
    else if (dotCount == 0) dotDirection = 1;

    glutPostRedisplay();
    glutTimerFunc(200, updateLoadingScreen, 0);
}

// Función para mostrar la pantalla de carga
void showLoadingScreen(int value) {
    loadingScreen = true;
    glutTimerFunc(200, updateLoadingScreen, 0);  // Iniciar la animación

    // Después de 3 segundos, cambiar al nivel 1 y reproducir la música de Pac-Man
    glutTimerFunc(3000, [](int value) {
        loadingScreen = false;
        glutDisplayFunc(drawLevel1);  // Cambiar a la función de nivel 1
        glutSpecialFunc(keyboardLevel1);  // Cambiar la función de teclado
        PlaySound(TEXT("pacman_theme.wav"), NULL, SND_ASYNC | SND_SYNC); 


        // prueba de congelamiento
        freezePlayer = true;
        glutTimerFunc(5000, [](int value) {
            freezePlayer = false;  // Descongelar al jugador después de 5 segundos
            }, 0);

        glutPostRedisplay();  
        }, 0);
}

// Función para dibujar el menú principal
void display() {
    if (loadingScreen) {
        drawLoadingScreen();  // Si estamos en pantalla de carga
    }
    else {
        menu.draw();  // Si estamos en el menú, dibujamos el menú
    }
}

// Función para manejar las teclas en el menú
void keyboard(int key, int, int) {
    if (freezePlayer) return;  // Si el jugador está congelado, no hacer nada con las teclas

    switch (key) {
    case GLUT_KEY_UP:    // Navegar hacia arriba
        menu.navigateUp();
        break;
    case GLUT_KEY_DOWN:  // Navegar hacia abajo
        menu.navigateDown();
        break;
    }
    glutPostRedisplay();  // Actualizar la pantalla
}

// Función para manejar las teclas normales (Enter)
void keyboardNormal(unsigned char key, int x, int y) {
    //if (freezePlayer) return;  // Si el jugador está congelado, no hacer nada con las teclas

    if (key == 13) {  // Si presionamos Enter
        if (menu.getSelectedOption() == 0) {
            PlaySound(NULL, 0, SND_PURGE);  // Detener música
            showLoadingScreen(0);  // Mostrar la pantalla de carga
        }
        else if (menu.getSelectedOption() == 1) {
            exit(0);  // Salir del juego
        }
    }
    glutPostRedisplay();  // Actualizar la pantalla
}


// Función de inicialización de OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Fondo negro
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1000.0, 0.0, 600.0);   // Ventana 1000x600
}

// Función para centrar la ventana en la pantalla
void centerWindow() {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int windowX = (screenWidth - 1000) / 2;
    int windowY = (screenHeight - 600) / 2;
    glutInitWindowPosition(windowX, windowY);
}

int main(int argc, char** argv) {
    PlaySound(TEXT("fondo.wav"), NULL, SND_ASYNC | SND_LOOP);  // Reproducir música de fondo del menú

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 600);
    centerWindow();
    glutCreateWindow("Menu Principal");

    initOpenGL();

    glutDisplayFunc(display);       // Función para mostrar el contenido
    glutSpecialFunc(keyboard);      // Función para las teclas especiales
    glutKeyboardFunc(keyboardNormal); // Función para la tecla Enter

    glutMainLoop();
    return 0;
}
