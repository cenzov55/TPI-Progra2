#include <iostream>
#include "Menu.h"
#include "MenuPagos.h"

using namespace std;

MenuPagos::MenuPagos()
{
    const int CANT_OPCIONES = 5;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Registrar pago",
        "Listar",
        "Listar pagos del socio",
        "Listar pagos de actividad",
        "Volver"};

    setOpciones(opciones);
    setAncho();
    setAlto();
    setPosicionCentro();
    setTitulo("Pagos ABML");
}

void MenuPagos::aparecer()
{
    while (true)
    {
        int opcion = seleccion();
        switch (opcion)
        {
        case 1:
            _managerPagos.agregar();
            break;
        case 2:
            _managerPagos.listar();
            break;
        case 3:
            _managerPagos.listarPagosSocio();
            break;
        case 4:
            _managerPagos.listarPagosActividad();
            break;
        case 5:
            return;
        default:
            cout << "Opcion no valida. Intente nuevamente." << endl;
            system("pause>nul");
        }
    }
}
