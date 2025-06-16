#include <string>
#include <iostream>
#include "MenuActividades.h"
#include "Menu.h"

using namespace std;

MenuActividades::MenuActividades(){
    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Agregar",
        "Borrar",
        "Modificar",
        "Listar",
        "Volver"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Actividades");
}


void MenuActividades::aparecer(){
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
