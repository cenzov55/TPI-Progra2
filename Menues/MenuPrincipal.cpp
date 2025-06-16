#include <iostream>
#include "MenuPrincipal.h"
#include "Menu.h"
#include <string>
#include "../funcionesConsola.h"

using namespace std;

MenuPrincipal::MenuPrincipal()
{
    const int CANT_OPCIONES = 8;
    setCantidadOpciones(CANT_OPCIONES);

    const string opciones[CANT_OPCIONES] = {
        "Socios ABML",
        "Actividades ABML",
        "Inscripciones ABML",
        "Registro de Pagos",
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

void MenuPrincipal::aparecer()
{
    while (true)
    {
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
            system("cls");
            _menuPagos.aparecer();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            system("cls");
            if (salir())
            {
                cout << "Saliendo del menu..." << endl;
                system("pause>nul");
                return;
            }
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            system("pause>nul");
        }
    }
}
    

    bool MenuPrincipal::salir(){
    string respuesta;
        do {
            limpiarError();
            mensajeFormulario(1, "Seguro que desea salir? (s/n): ");
            getline(cin, respuesta);

            if (respuesta == "s" || respuesta == "S") return true;

            else if (respuesta == "n" || respuesta == "N") return false;
            else  mensajeError("Respuesta invalida. Ingrese 's' o 'n'.");

        } while (true);
    }
