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

bool ArchivoSocios::exportarCSV(){

    FILE *csv;
    csv = fopen("Socios.csv", "w");
    if (csv == nullptr){
        return false;
    }

    int cantRegistros = getCantidadRegistros();
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
    return true;
}






