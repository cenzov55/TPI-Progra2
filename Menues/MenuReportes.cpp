#include <string>
#include <iostream>
#include "MenuReportes.h"
#include "../Managers/ManagerReportes.h"


using namespace std;

MenuReportes::MenuReportes(){
    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Recaudacion por meses",
        "Reporte Actividades",
        "Reporte Socios",
        "Reporte Inscripciones",
        "Volver"

    };

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Menu Reportes");
}


void MenuReportes::aparecer(){
    while(true){
        int opcion = seleccion();
        switch (opcion) {
            case 1:
                _managerReportes.recaudacionPorMes();
                break;
            case 2:
                _managerReportes.actividadMayorRecaudacion();
                break;
            case 3:
                _managerReportes.recaudacionPorSocio();
                break;
            case 4:
                _managerReportes.recaudacionPorInscripcion();
                break;
            case 5:
                return;
                break;
            default:
                cout << "Opción no valida. Intente nuevamente." << endl;
                system("pause>nul");
        }
    }
}
