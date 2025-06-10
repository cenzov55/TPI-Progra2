#include <iostream>
#include "rlutil.h"
using namespace std;

void imprimirFormulario(string titulo){

    rlutil::setBackgroundColor(rlutil::CYAN);
    rlutil::setColor(rlutil::BLACK);
    for (int x=1; x < 121; x++){
        rlutil::locate(x,8);
        cout << " ";
    }
    rlutil::locate(1,8);
    cout << titulo;

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);
    for (int y=9; y < 20; y++){
        for (int x=1; x < 121; x++){
            rlutil::locate(x,y);
            cout << " ";
        }
    }

    rlutil::resetColor();
    rlutil::setBackgroundColor(rlutil::BLACK);
}

void mensajeError(string mensaje){

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::RED);

    rlutil::locate(1, 25);
    cout << mensaje;
    system("pause>nul");
    rlutil::resetColor();
    rlutil::setBackgroundColor(rlutil::WHITE);
}

void mensajeFormulario(int posicion, string mensaje){

    rlutil::setBackgroundColor(rlutil::WHITE);
    rlutil::setColor(rlutil::BLACK);

    rlutil::locate(7, posicion+9);
    cout << mensaje;
}

void mensajeExito(string mensaje){

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::GREEN);

    rlutil::locate(1, 25);
    cout << mensaje;
    system("pause>nul");
    rlutil::resetColor();
    rlutil::setBackgroundColor(rlutil::WHITE);
}

void limpiarLinea(int posicion){

    for (int x=1; x < 121; x++){
        rlutil::locate(x,posicion+9);
        cout << " ";
    }
}

void limpiarError(){
    rlutil::setBackgroundColor(rlutil::BLACK);
    for (int x=1; x < 121; x++){
        rlutil::locate(x,25);
        cout << " ";
    }
    rlutil::setBackgroundColor(rlutil::WHITE);
}

string truncar(const string &str, int maximo) {
    if (str.length() > maximo) {
        return str.substr(0, maximo - 3) + "...";
        /// substr devuelve un string dependiendo el minimo y maximo de caracteres indicados
        /// en este caso de 0 al maximo - 3, para poder agregarle "..."
        /// esto para simbolizar que es mas largo, por si no entra en la tabla.
    }
    return str;
}


