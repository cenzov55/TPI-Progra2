#pragma once
#include "Menu.h"
#include "../Managers/ManagerSocios.h"
#include "../Managers/ManagerInscripciones.h"
#include "../Managers/ManagerPagos.h"
#include "../Managers/ManagerActividades.h"

class MenuConfiguraciones : public Menu {

public:
    MenuConfiguraciones();
    void aparecer();

private:
    ManagerSocios _managerSocios;
    ManagerInscripciones _managerInscripciones;
    ManagerActividades _managerActividades;
    ManagerPagos _managerPagos;

};

