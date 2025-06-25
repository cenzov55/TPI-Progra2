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

int ArchivoPagos::exportarCSV()
{
    FILE *csv;
    csv = fopen("Pagos.csv", "w");
    if (csv == nullptr)
    {
        return -1; /// -1 error al crear el archivo
    }

    int cantRegistros = getCantidadRegistros();

    if (cantRegistros == -1)
    {
        return -2; /// -2 no hay registros
    }
    Pago *pagos = new Pago[cantRegistros];
    leerTodos(cantRegistros, pagos);

    fprintf(csv, "ID Socio;ID Actividad;Fecha de Pago;Importe\n");

    for (int i = 0; i < cantRegistros; i++)
    {
        fprintf(csv, "%s\n", pagos[i].toCSV().c_str());
    }

    fclose(csv);

    delete[] pagos;
    return 0; /// 0 codigo exitoso
}

bool ArchivoPagos::crearBackup()
{

    FILE *copia;
    copia = fopen("PagosCopia.dat", "wb");
    if (copia == nullptr)
    {
        return false;
    }

    int cantRegistros = getCantidadRegistros();

    if (cantRegistros <= 0)
    {
        return false;
    }

    Pago *pagos = new Pago[cantRegistros];
    leerTodos(cantRegistros, pagos);

    /// Escribo todos los registros del vector de una sola vez en la copia
    /// y comparo con la cantidad de registros para saber si se escribieron todos bien
    bool ok = (fwrite(pagos, sizeof(Pago), cantRegistros, copia) == cantRegistros);
    fclose(copia);
    delete[] pagos;
    return ok;
}

bool ArchivoPagos::usarBackup()
{
    ArchivoPagos copia("PagosCopia.dat");

    if (copia.getCantidadRegistros() <= 0)
    {
        return false;
        /// por si da error o no hay registros en la copia
        /// nos vamos antes de borrar el archivo original
    }

    _pArchivo = fopen("Pagos.dat", "wb"); /// Borro lo que hay en el archivo original
    if (_pArchivo == nullptr)
    {
        return false;
    }

    int cantRegistros = copia.getCantidadRegistros();
    Pago *pagos = new Pago[cantRegistros];
    copia.leerTodos(cantRegistros, pagos);

    bool ok = (fwrite(pagos, sizeof(Pago), cantRegistros, _pArchivo) == cantRegistros);

    cerrar(); // cierra el puntero del archivo normal
    delete[] pagos;
    return ok;
}

int ArchivoPagos::buscar(int idSocio, int idActividad)
{
    if (!abrirLectura())
        return -1;

    Pago pago;
    int posicion = 0;

    while (fread(&pago, sizeof(Pago), 1, _pArchivo) == 1)
    {
        if (pago.getIdSocio() == idSocio && pago.getIdActividad() == idActividad)
        {
            cerrar();
            return posicion;
        }
        posicion++;
    }

    cerrar();
    return -1; // No encontrado
}
