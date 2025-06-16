#pragma once
#include "Menu.h"
#include "../Managers/ManagerSocios.h"
#include "../Managers/ManagerInscripciones.h"
#include "../Managers/ManagerPagos.h"

class MenuExportar : public Menu {

public:
    MenuExportar();
    void aparecer();

private:
    ManagerSocios _managerSocios;
    ManagerInscripciones _managerInscripciones;
    ManagerPagos _managerPagos;

    ///faltan los demas managers

};
