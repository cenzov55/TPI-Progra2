#include <iostream>
#include "ArchivoSocios.h"
using namespace std;

ArchivoSocios::ArchivoSocios(string nombre) : Archivo(nombre) {}

int ArchivoSocios::getCantidadRegistros()
{
    if(!abrirLecturaPlus()) return -1;

    fseek(_pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(_pArchivo) / sizeof(Socio);
    cerrar();
    return cantidadRegistros;
}


bool ArchivoSocios::modificar(Socio socio, int posicion)
{
    if(!abrirLecturaPlus()) return false;

    fseek(_pArchivo, sizeof(Socio) * posicion, SEEK_SET);
    bool ok = fwrite(&socio, sizeof(Socio), 1, _pArchivo);
    cerrar();
    return ok;
}


bool ArchivoSocios::guardar(Socio socio)
{
    if(!abrirEscritura()) return false;
    bool ok = fwrite(&socio, sizeof(Socio), 1, _pArchivo);
    cerrar();
    return ok;
}

int ArchivoSocios::buscar(int idSocio)
{
    if(!abrirLectura()) return false;
    int posicion = 0;
    Socio socio;
    while(fread(&socio,sizeof(Socio),1,_pArchivo)){
        if(socio.getIdSocio() == idSocio){
            cerrar();
            return posicion;
        }
        posicion++;
    }
    cerrar();
    return -1;
}

Socio ArchivoSocios::leer(int posicion){

    Socio socio;
    if(!abrirLectura()){
        socio.setIdSocio(-1);
        return socio;
    }


    fseek(_pArchivo, sizeof(Socio) * posicion, SEEK_SET);
    fread(&socio, sizeof(Socio), 1, _pArchivo);
    cerrar();
    return socio;
}

void ArchivoSocios::leerTodos(int cantidadRegistros, Socio *vec){

    if(!abrirLectura()) return;
    fread(vec, sizeof(Socio), cantidadRegistros, _pArchivo);
    cerrar();
}

int ArchivoSocios::getNuevoId(){

    ///Por si es el primer id
    if (getCantidadRegistros() == -1){
        abrirEscritura();
        cerrar();
    }

    return getCantidadRegistros() + 1;
}

int ArchivoSocios::exportarCSV(){

    FILE *csv;
    csv = fopen("Socios.csv", "w");
    if (csv == nullptr){
        return -1; /// -1 error al crear el archivo
    }

    int cantRegistros = getCantidadRegistros();

    if (cantRegistros == -1){
        return -2; /// -2 no hay registros
    }
    Socio *socios = new Socio[cantRegistros];
    leerTodos(cantRegistros, socios);

    fprintf(csv, "ID Socio;DNI;Nombre;Apellido;Email;FechaNacimiento\n");

    for (int i=0; i < cantRegistros; i++){
        if (!socios[i].getEliminado()){
            fprintf(csv, "%s\n", socios[i].toCSV().c_str());
        }
    }

    fclose(csv);

    delete[] socios;
    return 0; /// 0 codigo exitoso
}

bool ArchivoSocios::crearBackup(){

    FILE *copia;
    copia = fopen("SociosCopia.dat", "wb");
    if (copia == nullptr){
        return false;
    }

    int cantRegistros = getCantidadRegistros();

    if (cantRegistros <= 0){
        return false;
    }
    Socio *socios = new Socio[cantRegistros];
    leerTodos(cantRegistros, socios);

    ///Escribo todos los registros del vector de una sola vez en la copia
    ///y comparo con la cantidad de registros para saber si se escribieron todos bien
    bool ok = (fwrite(socios, sizeof(Socio), cantRegistros, copia) == cantRegistros);
    fclose(copia);
    delete[] socios;
    return ok;
}

bool ArchivoSocios::usarBackup(){
    ArchivoSocios copia("SociosCopia.dat");

    if (copia.getCantidadRegistros() <= 0){
        return false;
        /// por si da error o no hay registros en la copia
        /// nos vamos antes de borrar el archivo original
    }

    _pArchivo = fopen("Socios.dat", "wb"); ///Borro lo que hay en el archivo original
    if (_pArchivo == nullptr){
        return false;
    }

    int cantRegistros = copia.getCantidadRegistros();
    Socio *socios = new Socio[cantRegistros];
    copia.leerTodos(cantRegistros, socios);


    bool ok = (fwrite(socios, sizeof(Socio), cantRegistros, _pArchivo) == cantRegistros);


    cerrar(); //cierra el puntero del archivo normal
    delete[] socios;
    return ok;
}






