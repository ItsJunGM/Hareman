#ifndef MENU_H
#define MENU_H

#include <GL/glut.h>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> options; // Opciones del men�
    int selectedOption;               // �ndice de la opci�n seleccionada

public:
    Menu();
    void draw();                      // Dibuja el men�
    void navigateUp();                // Mueve hacia arriba
    void navigateDown();              // Mueve hacia abajo
	void selectOption();              // Selecciona la opci�n actual
    int getSelectedOption() const;    // Devuelve la opci�n seleccionada
};

#endif
