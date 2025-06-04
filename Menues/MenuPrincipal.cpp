#include <string>
#include <iostream>
#include "MenuPrincipal.h"
#include "Menu.h"

using namespace std;

MenuPrincipal::MenuPrincipal(){
    const int CANT_OPCIONES = 7;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "1. Socios ABML",
        "2. Actividades ABML",
        "3. Inscripciones ABML",
        "4. Informes",
        "5. Exportar datos",
        "6. Configuracion",
        "7. Salir"
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
                system("cls");
                _menuSocios.aparecer();
                break;
            case 2:
                system("cls");
                _menuActividades.aparecer();
                break;
            case 3:
                system("cls");
                _menuInscripciones.aparecer();
                break;
            case 4:

                break;
            case 5:

                break;
            case 6:
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
