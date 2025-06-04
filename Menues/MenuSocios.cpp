#include <string>
#include <iostream>
#include "MenuSocios.h"
#include "Menu.h"

using namespace std;

MenuSocios::MenuSocios(){
    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "1. Agregar",
        "2. Borrar",
        "3. Modificar",
        "4. Listar",
        "5. Salir"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Socios ABML");
}


void MenuSocios::aparecer(){
    while(true){
        int opcion = seleccion();
        switch (opcion) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                break;
            case 5:
                return;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
