#include <iostream>
#include "MenuInscripciones.h"
#include "Menu.h"

using namespace std;

MenuInscripciones::MenuInscripciones(){
    const int CANT_OPCIONES = 4;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Inscribir Socio a Actividad",
        "Borrar Inscripcion",
        "Listar",
        "Volver"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Inscripciones ABML");
}


void MenuInscripciones::aparecer(){
    while(true){
        int opcion = seleccion();
        switch (opcion) {
            case 1:
                _managerInscripciones.agregar();
                break;
            case 2:
                _managerInscripciones.borrar();
                break;
            case 3:
                _managerInscripciones.listar();
                break;
            case 4:
            return;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
