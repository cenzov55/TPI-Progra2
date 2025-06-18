#pragma once

class Fecha{

    public:

        Fecha();  ///Se genera en 0/0/0
        Fecha(int dia, int mes, int anio);
        Fecha(bool fechaHoy);  ///Constructor que inicializa con la fecha actual

        // Operadores de comparacion
        bool operator>(const Fecha& otra);
        bool operator<(const Fecha& otra);
        bool operator==(const Fecha& otra);

        int getDiasDelMes(int mes);
        bool esBisiesto();
        void agregarDia();
        void restarDia();
        void agregarDias(int dias);
        std::string toString();

        ///GETTERS
        int getDia();
        int getMes();
        int getAnio();

        ///SETTERS
        bool setDia(int dia);
        bool setMes(int mes);
        bool setAnio(int anio);

    private:
        int _dia;
        int _mes;
        int _anio;

        bool esBisiesto(int anio);
        bool esFechaValida(int dia, int mes, int anio);
};
