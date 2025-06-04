#include <iostream>
#include "Fecha.h"
#include <cstring>
#include <ctime>
using namespace std;


Fecha::Fecha()
: _dia(0), _mes(0), _anio(0){
}

Fecha::Fecha(int dia, int mes, int anio){

    if (esFechaValida(dia, mes, anio)){
        _dia = dia;
        _mes = mes;
        _anio = anio;
    }
    else{
        _anio = 0;
        _mes = 0;
        _dia = 0;
    }
}

Fecha::Fecha(bool fechaHoy) {
    if (fechaHoy) {
        time_t tiempoActual = time(nullptr);
        tm *tiempoLocal = localtime(&tiempoActual);
        
        _anio = tiempoLocal->tm_year + 1900;  // tm_year cuenta desde 1900
        _mes = tiempoLocal->tm_mon + 1;       // tm_mon va de 0 a 11
        _dia = tiempoLocal->tm_mday;
    } else {
        _dia = 0;
        _mes = 0;
        _anio = 0;
    }
}

void Fecha::agregarDia(){
    int proximoDia = _dia + 1;

    if (esBisiesto() && _mes == 2 && proximoDia == 29){
        _dia = 29;
        return;
    }

    if (proximoDia > getDiasDelMes(_mes)){
        _mes++;
        _dia = 1;

        if (_mes > 12){
            _anio++;
            _mes = 1;
        }
        return;
    }

    _dia++;
}


void Fecha::restarDia(){

    int diaAnterior = _dia - 1;

    if (esBisiesto() && _mes == 3 && diaAnterior == 0){
        _mes = 2;
        _dia = 29;
        return;
    }

    if (diaAnterior < 1){

        _mes--;

        if (_mes < 1){
            _anio--;
            _mes = 12;
            _dia = 31;
            return;
        }

        _dia = getDiasDelMes(_mes);
        return;
    }

    _dia--;
}

void Fecha::agregarDias(int dias){

    if (dias > 0){
        for (int i=0; i<dias; i++){
            agregarDia();
        }
    }
    else if (dias < 0){
        dias = dias * -1; //si es negativo lo invierto para el for
        for (int i=0; i<dias; i++){
            restarDia();
        }
    }
}

string Fecha::toString(){
    return to_string(_dia) + "/" + to_string(_mes) + "/" + to_string(_anio);
}

bool Fecha::esFechaValida(int dia, int mes, int anio){

    if(anio < 0 ){
        return false;
    }

    if (mes < 1 || mes > 12){
        return false;
    }

    if (dia < 1){
        return false;
    }

    if (mes == 2) {
        if (dia > 29 || (dia == 29 && !esBisiesto(anio))) {
            return false;
        }
    }
    else if (dia > getDiasDelMes(mes)) {
        return false;
    }

    return true;
}

bool Fecha::esBisiesto(){

    if (_anio%4 != 0){
        return false;
    }

    if (_anio%100 == 0 && _anio%400 != 0){
        return false;
    }

    return true;
}

bool Fecha::esBisiesto(int anio){

    if (anio%4 != 0){
        return false;
    }

    if (anio%100 == 0 && anio%400 != 0){
        return false;
    }

    return true;
}

///SETTERS

void Fecha::setDia(int dia){

    if (dia > getDiasDelMes(_mes) && !esBisiesto()){
        return;
    }
    _dia = dia;
}

void Fecha::setMes(int mes){

    if (mes < 1 || mes > 12){
        return;
    }
    _mes = mes;
}

void Fecha::setAnio(int anio){

    if(anio < 0 ){
        return;
    }
    _anio = anio;
}


///GETTERS
int Fecha::getDia(){
    return _dia;
}
int Fecha::getMes(){
    return _mes;
}
int Fecha::getAnio(){
    return _anio;
}

int Fecha::getDiasDelMes(int mes){
    const int diasMeses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (esBisiesto() && mes == 2){
        return diasMeses[mes] + 1;
    }
    
    return diasMeses[mes-1];
}

bool Fecha::operator>(const Fecha& otra) {
    if (_anio > otra._anio) return true;
    if (_anio < otra._anio) return false;
    
    if (_mes > otra._mes) return true;
    if (_mes < otra._mes) return false;
    
    return _dia > otra._dia;
}

bool Fecha::operator<(const Fecha& otra){
    if (_anio < otra._anio) return true;
    if (_anio > otra._anio) return false;
    
    if (_mes < otra._mes) return true;
    if (_mes > otra._mes) return false;
    
    return _dia < otra._dia;
}

bool Fecha::operator==(const Fecha& otra){
    return (_anio == otra._anio && _mes == otra._mes && _dia == otra._dia);
}


string Fecha::toStringConHoraHoy(){
    time_t t = time(nullptr);             // Obtener tiempo actual
    tm *pTm = localtime(&t);            // Convertir a hora local

    char texto[100];
    strftime(texto, sizeof(texto), "%Y-%m-%d_%H-%M-%S", pTm);

    return texto;
}

