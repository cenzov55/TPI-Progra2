#pragma once
#include <string>

class Menu
{
    public:
        Menu();
        ~Menu();
        int seleccion();
        
    protected:
        bool setCantidadOpciones(int cantOpciones);
        void setOpciones(const std::string opciones[]);
        void setAncho();
        void setAlto();
        void setPosicionCentro();
        void setTitulo(const std::string &titulo);
        
    private:
        void imprimirMarco();
        int getTamanioOpcionMasLarga();
        int getCantidadOpciones();

        int _ancho;
        int _alto;
        int _x;
        int _y;

        int _cantOpciones;	
        std::string *_opciones;
        std::string _titulo;    
};

