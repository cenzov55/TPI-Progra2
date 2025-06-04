#pragma once
#include "Menu.h"
#include "MenuSocios.h"
#include "MenuActividades.h"
#include "MenuInscripciones.h"

class MenuPrincipal : public Menu
{
    public:
        MenuPrincipal();

        void aparecer();

    private:
        MenuSocios _menuSocios;

        MenuActividades _menuActividades;

        MenuInscripciones _menuInscripciones;



};
