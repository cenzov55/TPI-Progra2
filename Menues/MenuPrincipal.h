#pragma once
#include "Menu.h"
#include "MenuSocios.h"
#include "MenuActividades.h"
#include "MenuInscripciones.h"
#include "MenuReportes.h"
#include "MenuPagos.h"
#include "MenuExportar.h"
#include "MenuConfiguraciones.h"

class MenuPrincipal : public Menu
{
    public:
        MenuPrincipal();

        void aparecer();

    private:
        MenuSocios _menuSocios;
        MenuActividades _menuActividades;
        MenuInscripciones _menuInscripciones;
        MenuExportar _menuExportar;
        MenuConfiguraciones _menuConfiguraciones;
        MenuPagos _menuPagos;
        MenuReportes _menuReportes;
        bool salir();
};
