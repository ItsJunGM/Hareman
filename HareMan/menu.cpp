#include "menu.h"

// Constructor
Menu::Menu() : selectedOption(0) {
    options = { "Iniciar Juego", "Salir"}; // Opciones del men�
}

// Dibujar el men�
void Menu::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar t�tulo del juego
    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco
    glRasterPos2f(400, 500);     // Posici�n centrada del t�tulo
    std::string title = "HareMan";
    for (char c : title) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Texto grande
    }

    // Dibujar opciones del men�
    for (int i = 0; i < options.size(); i++) {
        if (i == selectedOption)
            glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para la opci�n seleccionada
        else
            glColor3f(1.0f, 1.0f, 1.0f); // Blanco para las dem�s

        glRasterPos2f(450, 300 - i * 100); // Ajuste de posici�n para las opciones
        for (char c : options[i]) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c); // Texto m�s grande
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

// Obtener la opci�n seleccionada
int Menu::getSelectedOption() const {
    return selectedOption;
}
