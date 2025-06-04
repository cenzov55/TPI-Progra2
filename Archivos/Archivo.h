#pragma once
#include <string>

class Archivo {
    public:
        Archivo(std::string nombreArchivo);
        
    protected:    
        bool abrirLectura();
        bool abrirLecturaPlus();
        bool abrirEscritura();
        void cerrar();
        
        FILE *_pArchivo;

    private:
        bool abrir(std::string modo);
        std::string _nombreArchivo;

};