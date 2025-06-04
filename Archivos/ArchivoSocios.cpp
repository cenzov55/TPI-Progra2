#include "ArchivoSocios.h"

ArchivoSocios::ArchivoSocios(std::string nombre) : Archivo(nombre) {}

int ArchivoSocios::getCantidadRegistros()
{
    if(abrirLecturaPlus()) return -1;

    fseek(_pArchivo, 0, SEEK_END);
    int cantidadRegistros = ftell(_pArchivo) / sizeof(Socio);
    cerrar();
    return cantidadRegistros;
}


bool ArchivoSocios::modificar(Socio Socio, int posicion)
{
    if(abrirLecturaPlus()) return false;

    fseek(_pArchivo, sizeof(Socio) * posicion, SEEK_SET);
    bool ok = fwrite(&Socio, sizeof(Socio), 1, _pArchivo);
    cerrar();
    return ok;
}


bool ArchivoSocios::guardar(Socio socio)
{
    if(abrirEscritura()) return false;
    bool ok = fwrite(&socio, sizeof(Socio), 1, _pArchivo);
    cerrar();
    return ok;
}

int ArchivoSocios::buscar(int IDSocio)
{

    if(abrirLectura()) return false;

    Socio socio;
    int i=0;
    while(fread(&socio,sizeof(Socio),1,_pArchivo))
        {
        if(socio.getIdSocio() == IDSocio)
            {
                cerrar();
                return i;
            }
            i++;
        }
    cerrar();
    return -1;
}
