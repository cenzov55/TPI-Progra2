#include <iostream>
#include "ArchivoPagos.h"
using namespace std;

ArchivoPagos::ArchivoPagos(string nombre) : Archivo(nombre) {}

int ArchivoPagos::getCantidadRegistros()
{
    if (!abrirLecturaPlus())
        return -1;

    fseek(_pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(_pArchivo) / sizeof(Pago);
    cerrar();
    return cantidadRegistros;
}

bool ArchivoPagos::modificar(Pago pago, int posicion)
{
    if (!abrirLecturaPlus())
        return false;

    fseek(_pArchivo, sizeof(Pago) * posicion, SEEK_SET);
    bool ok = fwrite(&pago, sizeof(Pago), 1, _pArchivo);
    cerrar();
    return ok;
}

bool ArchivoPagos::guardar(Pago pago)
{
    if (!abrirEscritura())
        return false;
    bool ok = fwrite(&pago, sizeof(Pago), 1, _pArchivo);
    cerrar();
    return ok;
}

Pago ArchivoPagos::leer(int posicion)
{

    Pago pago;
    if (!abrirLectura())
    {
        cout << "Error al abrir el archivo para lectura." << endl;
        system("pause>nul");
        pago.setIdActividad(-1); // Indicador de error
        return pago;
    }

    fseek(_pArchivo, sizeof(Pago) * posicion, SEEK_SET);
    fread(&pago, sizeof(Pago), 1, _pArchivo);
    cerrar();
    return pago;
}

void ArchivoPagos::leerTodos(int cantidadRegistros, Pago *vec)
{
    if (!abrirLectura())
        return;
    fread(vec, sizeof(Pago), cantidadRegistros, _pArchivo);
    cerrar();
}

bool ArchivoPagos::exportarCSV()
{

    FILE *csv;
    csv = fopen("Pagos.csv", "w");
    if (csv == nullptr)
    {
        return false;
    }

    int cantRegistros = getCantidadRegistros();
    Pago *pagos = new Pago[cantRegistros];
    if (pagos == nullptr)
    {
        fclose(csv);
        return false;
    }
    leerTodos(cantRegistros, pagos);

    fprintf(csv, "ID Pago;DNI;Nombre;Apellido;Email;FechaNacimiento\n");

    for (int i = 0; i < cantRegistros; i++)
    {
        fprintf(csv, "%s\n", pagos[i].toCSV().c_str());
    }

    fclose(csv);

    delete[] pagos;
    return true;
}