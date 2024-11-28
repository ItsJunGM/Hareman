#include <GL/glut.h>
#include "nivel1.h"
#include <cmath>  // Para funciones matemáticas como cos y sin
#include <vector> 

void drawPacMan(float x, float y);  

// Definir variables para Pac-Man
float pacmanPosX = 500, pacmanPosY = 300;  // Posición inicial del PacMan
float pacmanSpeed = 10.0f;  // Velocidad de movimiento del PacMan

// Estructura para manejar puntos
struct Point {
    float x, y;
    bool eaten; // Indica si el punto ya fue comido
};

// Lista de puntos para comer
std::vector<Point> points = {
    {200, 200, false}, {250, 200, false}, {300, 200, false}, {350, 200, false}, {400, 200, false},
    {200, 250, false}, {250, 250, false}, {300, 250, false}, {350, 250, false}, {400, 250, false},
    {200, 300, false}, {250, 300, false}, {300, 300, false}, {350, 300, false}, {400, 300, false}
};

// Estructura para paredes
struct Wall {
    float x1, y1, x2, y2; // Coordenadas de las esquinas (x1, y1) a (x2, y2)
};

// Lista de paredes
std::vector<Wall> walls = {
    {100, 100, 900, 120}, // Pared horizontal superior
    {100, 100, 120, 500}, // Pared vertical izquierda
    {880, 100, 900, 500}, // Pared vertical derecha
    {400, 400, 600, 420}  // Pared horizontal central
};

// Dibujar un punto
void drawPoint(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Centro del punto
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + cos(angle) * 5, y + sin(angle) * 5); // Radio de 5
    }
    glEnd();
}

// Dibujar una pared
void drawWall(float x1, float y1, float x2, float y2) {
    glColor3f(0.0f, 0.0f, 1.0f);  // Color azul
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Detección de colisiones entre Pac-Man y un punto
bool checkCollision(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < 15; // Radio de Pac-Man (20) y radio del punto (5)
}

// Función para dibujar el nivel 1
void drawLevel1() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar paredes
    for (const auto& wall : walls) {
        drawWall(wall.x1, wall.y1, wall.x2, wall.y2);
    }

    // Dibujar puntos
    for (auto& point : points) {
        if (!point.eaten) { // Solo dibujamos puntos no comidos
            drawPoint(point.x, point.y);
        }
    }

    // Dibujar Pac-Man
    drawPacMan(pacmanPosX, pacmanPosY);

    glutSwapBuffers(); // Actualizamos la pantalla
}

// Función para manejar el teclado en el nivel 1
void keyboardLevel1(int key, int x, int y) {
    float oldX = pacmanPosX, oldY = pacmanPosY; // Guardar posición anterior para verificar colisiones

    switch (key) {
    case GLUT_KEY_UP:
        pacmanPosY += pacmanSpeed;
        break;
    case GLUT_KEY_DOWN:
        pacmanPosY -= pacmanSpeed;
        break;
    case GLUT_KEY_LEFT:
        pacmanPosX -= pacmanSpeed;
        break;
    case GLUT_KEY_RIGHT:
        pacmanPosX += pacmanSpeed;
        break;
    }

    // Verificar colisiones con paredes
    for (const auto& wall : walls) {
        if (pacmanPosX + 20 > wall.x1 && pacmanPosX - 20 < wall.x2 &&
            pacmanPosY + 20 > wall.y1 && pacmanPosY - 20 < wall.y2) {
            pacmanPosX = oldX; // Revertir posición
            pacmanPosY = oldY;
            break;
        }
    }

    // Verificar si Pac-Man come algún punto
    for (auto& point : points) {
        if (!point.eaten && checkCollision(pacmanPosX, pacmanPosY, point.x, point.y)) {
            point.eaten = true; // Marcar el punto como comido
        }
    }

    glutPostRedisplay(); // Volver a dibujar la pantalla
}


// Función para dibujar a PacMan con orejas y camiseta
void drawPacMan(float x, float y) {
    // Cuerpo de Pac-Man
    glColor3f(1.0f, 1.0f, 0.0f);  // Color amarillo
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);  // Centro del círculo
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;  // Convertir a radianes
        glVertex2f(x + cos(angle) * 20, y + sin(angle) * 20);  // Radio del círculo
    }
    glEnd();

    // Orejas de liebre
    glColor3f(1.0f, 1.0f, 1.0f);

    // Oreja izquierda
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 8, y + 25); // Base izquierda
    glVertex2f(x - 12, y + 40); // Punto superior izquierdo
    glVertex2f(x - 4, y + 35);  // Base derecha
    glEnd();

    // Oreja derecha
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 8, y + 25);  // Base derecha
    glVertex2f(x + 12, y + 40); // Punto superior derecho
    glVertex2f(x + 4, y + 35);  // Base izquierda
    glEnd();

    // Camisa roja
    glColor3f(1.0f, 0.0f, 0.0f);  // Color rojo para la camisa
    glBegin(GL_QUADS);
    glVertex2f(x - 16, y - 10);  // Esquina inferior izquierda
    glVertex2f(x + 16, y - 10);  // Esquina inferior derecha
    glVertex2f(x + 16, y - 20);  // Esquina superior derecha
    glVertex2f(x - 16, y - 20);  // Esquina superior izquierda
    glEnd();
}