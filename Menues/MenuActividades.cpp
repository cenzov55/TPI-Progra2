#include <string>
#include <iostream>
#include "MenuActividades.h"
#include "Menu.h"

using namespace std;

MenuActividades::MenuActividades(){
    const int CANT_OPCIONES = 6;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Agregar",
        "Borrar",
        "Modificar",
        "Listar",
        "Dar de alta",
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
                _managerActividades.agregar();
                break;
            case 2:
                _managerActividades.borrar();
                break;
            case 3:
                _managerActividades.modificar();
                break;
            case 4:
                _managerActividades.listar();
                break;
            case 5:
                _managerActividades.darDeAlta();
                break;
            case 6:
                return;
            default:
                cout << "Opción no valida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
