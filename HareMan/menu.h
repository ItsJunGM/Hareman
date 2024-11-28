#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> options; // Opciones del menú
    int selectedOption;               // Índice de la opción seleccionada

public:
    Menu();
    void draw();                      // Dibuja el menú
    void navigateUp();                // Mueve hacia arriba
    void navigateDown();              // Mueve hacia abajo
	void selectOption();              // Selecciona la opción actual
    int getSelectedOption() const;    // Devuelve la opción seleccionada
};

#endif
