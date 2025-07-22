#include <string>
#include <iostream>
#include "MenuSocios.h"
#include "Menu.h"
#include "../Entidades/Socio.h"

using namespace std;

MenuSocios::MenuSocios() {
    const int CANT_OPCIONES = 10;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Agregar",
        "Borrar",
        "Modificar",
        "Listar",
        "Buscar por apellido",
        "Buscar por edad",
        "Listar eliminados",
        "Buscar por id",
        "Dar de alta",
        "Volver"
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
                _managerSocios.agregar();
                break;
            case 2:
                _managerSocios.borrar();
                break;
            case 3:
                _managerSocios.modificar();
                break;
            case 4:
                _managerSocios.listar();
                break;
            case 5:
                _managerSocios.buscarPorApellido();
                break;
            case 6:
                _managerSocios.buscarPorEdad();
                break;
            case 7:
                _managerSocios.listarEliminados();
                break;
            case 8:
                _managerSocios.buscarPorId();
                break;
            case 9:
                _managerSocios.darDeAlta();
                break;
            case 10:
                return;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
