#include <string>
#include <iostream>
#include "Menu.h"
#include "MenuReportes.h"

using namespace std;

MenuReportes::MenuReportes()
{
    const int CANT_OPCIONES = 2;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Actividad con mas socios",
        "Actividad con mayor recaudacion"};

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Reportes");
}

void MenuReportes::aparecer()
{
    while (true)
    {
        int opcion = seleccion();
        switch (opcion)
        {
        case 1:
            _managerReportes.actividadMasInscriptos();
            break;
        case 2:
            _managerReportes.actividadMayorRecaudacion();
            break;
        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
            system("pause>nul");
        }
    }
}
