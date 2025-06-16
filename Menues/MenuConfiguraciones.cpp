#include <iostream>
#include "MenuConfiguraciones.h"
using namespace std;

MenuConfiguraciones::MenuConfiguraciones() {

    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Copia de seguridad Socios",
        "Copia de seguridad Actividades",
        "Copia de seguridad Inscripciones",
        "Copia de seguridad Pagos",
        "Salir"
    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Configuraciones");

}

void MenuConfiguraciones::aparecer() {
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
