#include <iostream>
#include "ManagerReportes.h"
#include "../funcionesConsola.h"
#include "../rlutil.h"
#include <iomanip>

using namespace std;

ManagerReportes::ManagerReportes()
    : _archivoInscripciones("Inscripciones.dat"),
      _archivoSocios("Socios.dat"),
      _archivoActividades("Actividades.dat"),
      _archivoPagos("Pagos.dat")
{
}

void ManagerReportes::actividadMasInscriptos()
{
}

void ManagerReportes::actividadMayorRecaudacion()
{
}

void ManagerReportes::recaudacionPorMes()
{
  system("cls");
  cout << "Recaudacion por mes" << endl;
  cout << "---------------------" << endl;
  int meses[12] = {0};
  int cantidadRegistros = _archivoPagos.getCantidadRegistros();
  if (cantidadRegistros <= 0)
  { /// si es 0 no hay pagos, pero puede ser -1 que significa error
    mensajeError("No hay pagos registrados.");
    system("pause>nul");
    return;
  }

  Pago *pagos = new Pago[cantidadRegistros];
  _archivoPagos.leerTodos(cantidadRegistros, pagos);

  for (int i = 0; i < cantidadRegistros; i++)
  {
    int mes = pagos[i].getFechaDePago().getMes() - 1;
    meses[mes] += pagos[i].getImporte();
  }

  // ENCABEZADO
  rlutil::setBackgroundColor(rlutil::CYAN);
  rlutil::setColor(rlutil::BLACK);
  cout << (char)179 << left << setw(12) << "MES" << (char)179;
  cout << left << setw(12) << "RECAUDACION" << (char)179;
  cout << endl;
  // FIN ENCABEZADO

  string nombreMeses[12] = {
      "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
      "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

  for (int i = 0; i < 12; i++)
  {
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    cout << (char)179 << left << setw(12) << nombreMeses[i] << (char)179;
    cout << left << setw(12) << meses[i] << (char)179;
    cout << endl;
  }
  rlutil::setBackgroundColor(rlutil::BLACK);
  rlutil::resetColor();
  system("pause>nul");

  delete[] pagos;
}