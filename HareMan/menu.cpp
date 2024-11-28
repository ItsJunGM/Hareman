#include "menu.h"

// Constructor
Menu::Menu() : selectedOption(0) {
    options = { "Iniciar Juego", "Salir"}; // Opciones del menú
}

// Dibujar el menú
void Menu::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar título del juego
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    glRasterPos2f(400, 500);     // Posición centrada del título
    std::string title = "HareMan";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Texto grande
    }

    // Dibujar opciones del menú
    for (int i = 0; i < options.size(); i++) {
        if (i == selectedOption)
            glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para la opción seleccionada
        else
            glColor3f(1.0f, 1.0f, 1.0f); // Blanco para las demás

        glRasterPos2f(450, 300 - i * 100); // Ajuste de posición para las opciones
        for (char c : options[i]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Texto más grande
        }
    }

    glutSwapBuffers();
}

// Mover hacia arriba
void Menu::navigateUp() {
    selectedOption = (selectedOption - 1 + options.size()) % options.size();
}

// Mover hacia abajo
void Menu::navigateDown() {
    selectedOption = (selectedOption + 1) % options.size();
}

// Obtener la opción seleccionada
int Menu::getSelectedOption() const {
    return selectedOption;
}
