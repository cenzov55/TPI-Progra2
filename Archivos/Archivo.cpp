#include <string>
#include "Archivo.h"
using namespace std;

Archivo::Archivo(string nombreArchivo) 
: _nombreArchivo(nombreArchivo) {
    _pArchivo = nullptr;
}   

bool Archivo::abrir(string modo) {
    
    _pArchivo = fopen(_nombreArchivo.c_str(), modo.c_str());
    if (_pArchivo == nullptr) {
        return false; // Error al abrir el archivo
    }
    
    return true; // Archivo abierto con éxito
}

bool Archivo::abrirLectura(){
    return abrir("rb");
}

bool Archivo::abrirLecturaPlus(){
    return abrir("rb+");
}

bool Archivo::abrirEscritura(){
    return abrir("ab");
}

void Archivo::cerrar(){
    if (_pArchivo != nullptr) {
        fclose(_pArchivo);
    }
}