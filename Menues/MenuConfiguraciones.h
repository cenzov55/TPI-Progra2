#pragma once
#include "Menu.h"
#include "../Managers/ManagerSocios.h"
#include "../Managers/ManagerInscripciones.h"

class MenuConfiguraciones : public Menu {

public:
    MenuConfiguraciones();
    void aparecer();

private:
    ManagerSocios _managerSocios;
    ManagerInscripciones _managerInscripciones;
    ///faltan los demas managers

};

