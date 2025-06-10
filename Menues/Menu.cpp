#include <iostream>
#include <string>
#include "Menu.h"
#include "../rlutil.h"

using namespace std;

Menu::Menu()
: _cantOpciones(0), _opciones(nullptr) {
    // Constructor por defecto
}

Menu::~Menu(){
    delete[] _opciones;
}

int Menu::seleccion(){
    rlutil::setBackgroundColor(rlutil::BLACK);
    system("cls");

    char tecla;
    int opcion = 0;
    rlutil::locate(_x, _y-1);
    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    cout << _titulo << endl;
    imprimirMarco();
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);

    while(true){
        for(int i=0; i<_cantOpciones; i++){
            rlutil::locate(_x + 1, _y + (i + 1));

            if (i == opcion){
                cout << " > " << _opciones[i] << " < " << endl;
            }
            else{
                cout << "   " << _opciones[i] << "   " << endl;
            }
        }

        tecla = rlutil::getkey();
        if (tecla == rlutil::KEY_UP) {
            opcion--;
            if (opcion < 0) opcion = _cantOpciones - 1;
        }
        else if (tecla == rlutil::KEY_DOWN) {
            opcion++;
            if (opcion >= _cantOpciones) opcion = 0;
        }
        else if (tecla == rlutil::KEY_ENTER) {
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::GREY);
            return opcion + 1;
        }
    }

}

int Menu::getTamanioOpcionMasLarga(){
    int tamanio = 0;
    for(int i=0; i<_cantOpciones; i++){
        if (_opciones[i].size() > tamanio){
            tamanio = _opciones[i].size();
        }
    }
    return tamanio;
}

int Menu::getCantidadOpciones(){
    return _cantOpciones;
}

bool Menu::setCantidadOpciones(int cantOpciones){
    if (cantOpciones <= 0){
        return false;
    }

    _cantOpciones = cantOpciones;
    return true;
}

void Menu::setOpciones(const string opciones[]){
    _opciones = new string[_cantOpciones];
    for(int i=0; i < _cantOpciones; i++){
        _opciones[i] = opciones[i];
    }
}

void Menu::setAlto(){
    _alto = _cantOpciones + 2;
}

void Menu::setAncho(){
    _ancho = getTamanioOpcionMasLarga() + 8;
}

void Menu::setPosicionCentro(){
    _x = (120 - _ancho) / 2;
    _y = (30 - _alto) / 2;
}

void Menu::setTitulo(const string& titulo){
    int espacios = _ancho - titulo.size();

    if (espacios <= 0) {
        _titulo = "error"; /// Error porque el titulo es mas largo que el ancho
        return;
    }

    int izquierda = espacios / 2;
    int derecha = espacios - izquierda;
    _titulo = string(izquierda, ' ') + titulo + string(derecha, ' ');
}

void Menu::imprimirMarco(){
    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    rlutil::locate(_x, _y);
    for (int i = 0; i < _ancho; i++) {
        for (int j = 0; j < _alto; j++) {
            rlutil::locate(_x + i, _y + j);
            cout << " "; // Espacio en blanco para el marco
        }
    }

    //Reseteo el color
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::GREY);
}
