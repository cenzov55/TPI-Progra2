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
                _managerSocios.backup();
                break;
            case 2:
                //_managerActividades.backup();
                break;
            case 3:
                _managerInscripciones.backup();
                break;
            case 4:
                _managerPagos.backup();
                break;
            case 5:
                return;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
