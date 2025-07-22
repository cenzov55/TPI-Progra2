#include <iostream>
#include "MenuInscripciones.h"
#include "Menu.h"

using namespace std;

MenuInscripciones::MenuInscripciones(){
    const int CANT_OPCIONES = 8;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Inscribir Socio a Actividad",
        "Borrar Inscripcion",
        "Listar",
        "Listar eliminadas",
        "Buscar inscripciones de socio",
        "Socios inscriptos a actividad",
        "Dar de alta",
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
                _managerInscripciones.listarEliminados();
                break;
            case 5:
                _managerInscripciones.listarActividadesInscriptas();
                break;
            case 6:
                _managerInscripciones.listarSociosInscriptos();
                break;
            case 7:
                _managerInscripciones.darDeAlta();
                break;
            case 8:
                return;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                system("pause");
        }
    }
}
