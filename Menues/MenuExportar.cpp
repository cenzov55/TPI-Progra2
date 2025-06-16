#include <iostream>
#include "MenuExportar.h"
using namespace std;

MenuExportar::MenuExportar() {

    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Socios en CSV",
        "Actividades en CSV",
        "Inscripciones en CSV",
        "Pagos en CSV",
        "Salir"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Exportar");

}

void MenuExportar::aparecer() {
    while(true){
        int opcion = seleccion();
        switch (opcion) {
            case 1:
                _managerSocios.exportarCSV();
                break;
            case 2:
                break;
            case 3:
                _managerInscripciones.exportarCSV();
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

