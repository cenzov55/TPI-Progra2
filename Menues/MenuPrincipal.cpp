#include <string>
#include <iostream>
#include "MenuPrincipal.h"
#include "Menu.h"

using namespace std;

MenuPrincipal::MenuPrincipal(){
    const int CANT_OPCIONES = 7;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Socios ABML",
        "Actividades ABML",
        "Inscripciones ABML",
        "Informes",
        "Exportar datos",
        "Configuracion",
        "Salir"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Principal");
}


void MenuPrincipal::aparecer(){
    while(true){
        int opcion = seleccion();
        switch (opcion) {
            case 1:
                _menuSocios.aparecer();
                break;
            case 2:
                _menuActividades.aparecer();
                break;
            case 3:
                _menuInscripciones.aparecer();
                break;
            case 4:

                break;
            case 5:
                _menuExportar.aparecer();
                break;
            case 6:
                _menuConfiguraciones.aparecer();
                break;
            case 7:
                system("cls");
                cout << "Saliendo del menu..." << endl;
                system("pause>nul");
                return;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
