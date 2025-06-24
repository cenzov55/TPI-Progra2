#include <iostream>
#include "ArchivoInscripciones.h"
using namespace std;


ArchivoInscripciones::ArchivoInscripciones(string nombre) : Archivo(nombre) { }

int ArchivoInscripciones::getCantidadRegistros()
{
    if(!abrirLecturaPlus()) return -1;

    fseek(_pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(_pArchivo) / sizeof(Inscripcion);
    cerrar();
    return cantidadRegistros;
}


bool ArchivoInscripciones::modificar(Inscripcion inscripcion, int posicion)
{
    if(!abrirLecturaPlus()) return false;

    fseek(_pArchivo, sizeof(Inscripcion) * posicion, SEEK_SET);
    bool ok = fwrite(&inscripcion, sizeof(Inscripcion), 1, _pArchivo);
    cerrar();
    return ok;
}


bool ArchivoInscripciones::guardar(Inscripcion inscripcion)
{
    if(!abrirEscritura()) return false;
    bool ok = fwrite(&inscripcion, sizeof(Inscripcion), 1, _pArchivo);
    cerrar();
    return ok;
}

int ArchivoInscripciones::buscar(int idActividad, int idSocio)
{
    if(!abrirLectura()) return -1;
    int posicion = 0;
    Inscripcion inscripcion;

    while(fread(&inscripcion,sizeof(Inscripcion),1,_pArchivo)){
        if(inscripcion.getIdActividad() == idActividad && inscripcion.getIdSocio() == idSocio){
            cerrar();
            return posicion;
        }
        posicion++;
    }
    cerrar();
    return -1;
}

Inscripcion ArchivoInscripciones::leer(int posicion){

    Inscripcion inscripcion;
    if(!abrirLectura()){
        inscripcion.setIdActividad(-1);
        inscripcion.setIdSocio(-1);
        return inscripcion;
    }


    fseek(_pArchivo, sizeof(Inscripcion) * posicion, SEEK_SET);
    fread(&inscripcion, sizeof(Inscripcion), 1, _pArchivo);
    cerrar();
    return inscripcion;
}


void ArchivoInscripciones::leerTodos(int cantidadRegistros, Inscripcion *vec){

    if(!abrirLectura()) return;
    fread(vec, sizeof(Inscripcion), cantidadRegistros, _pArchivo);
    cerrar();
}

int ArchivoInscripciones::getNuevoId(){

    ///Por si es el primer id
    if (getCantidadRegistros() == -1){
        abrirEscritura();
        cerrar();
    }

    return getCantidadRegistros() + 1;
}

int ArchivoInscripciones::exportarCSV(){

    FILE *csv;
    csv = fopen("Inscripciones.csv", "w");
    if (csv == nullptr){
        return -1; /// -1 error al intentar crear el archivo
    }

    int cantRegistros = getCantidadRegistros();

    if(cantRegistros == -1){
        return -2;  ///-2 no hay registros
    }

    Inscripcion *inscripciones = new Inscripcion[cantRegistros];
    leerTodos(cantRegistros, inscripciones);

    fprintf(csv,"ID Actividad;ID Socio;Fecha de Pago");

    for (int i=0; i < cantRegistros; i++){
        if (!inscripciones[i].getEliminado()){
            fprintf(csv, "%s\n", inscripciones[i].toCSV().c_str());
        }
    }

    fclose(csv);

    delete[] inscripciones;
    return 0; /// 0 codigo exitoso
}

bool ArchivoInscripciones::crearBackup(){

    FILE *copia;
    copia = fopen("InscripcionesCopia.dat", "wb");
    if (copia == nullptr){
        return false;
    }

    int cantRegistros = getCantidadRegistros();

    if (cantRegistros <= 0){
        return false;
    }

    Inscripcion *inscripciones = new Inscripcion[cantRegistros];
    leerTodos(cantRegistros, inscripciones);

    ///Escribo todos los registros del vector de una sola vez en la copia
    ///y comparo con la cantidad de registros para saber si se escribieron todos bien
    bool ok = (fwrite(inscripciones, sizeof(Inscripcion), cantRegistros, copia) == cantRegistros);
    fclose(copia);
    delete[] inscripciones;
    return ok;
}

bool ArchivoInscripciones::usarBackup(){
    ArchivoInscripciones copia("InscripcionesCopia.dat");

    if (copia.getCantidadRegistros() <= 0){
        return false;
        /// por si da error o no hay registros en la copia
        /// nos vamos antes de borrar el archivo original
    }

    _pArchivo = fopen("Inscripciones.dat", "wb"); ///Borro lo que hay en el archivo original
    if (_pArchivo == nullptr){
        return false;
    }

    int cantRegistros = copia.getCantidadRegistros();
    Inscripcion *inscripciones = new Inscripcion[cantRegistros];
    copia.leerTodos(cantRegistros, inscripciones);


    bool ok = (fwrite(inscripciones, sizeof(Inscripcion), cantRegistros, _pArchivo) == cantRegistros);


    cerrar(); //cierra el puntero del archivo normal
    delete[] inscripciones;
    return ok;
}

