#pragma once

void imprimirFormulario(std::string titulo);
void mensajeError(std::string mensaje);
void mensajeFormulario(int posicion, std::string mensaje);
void mensajeExito(std::string mensaje);
void limpiarLinea(int posicion);
void limpiarError();
std::string truncar(const std::string &str, int maximo);

