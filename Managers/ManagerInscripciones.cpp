#include <iostream>
#include "ManagerInscripciones.h"
#include "../funcionesConsola.h"
using namespace std;

ManagerInscripciones::ManagerInscripciones()
    : _archivoInscripciones("Inscripciones.dat") {}










void ManagerInscripciones::exportarCSV(){

    system("cls");
    imprimirFormulario("Socios CSV");
    mensajeFormulario(3, "Se exportaran los datos de las inscripciones en un archivo .csv");
    mensajeFormulario(4, "en la carpeta donde se encuentra el programa");

    int codigo = _archivoInscripciones.exportarCSV();

    if (codigo == -1)
    {
        mensajeError("Error al exportar en csv.");
        system("pause>nul");
        return;
    }

    if (codigo == -2)
    {
        mensajeError("No hay registros para exportar en csv.");
        system("pause>nul");
        return;
    }

    mensajeExito("Inscripciones exportadas correctamente");
    system("pause>nul");
}




