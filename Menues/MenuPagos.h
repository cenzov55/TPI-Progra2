#pragma once
#include "Menu.h"
#include "../Managers/ManagerPagos.h"

class MenuPagos : public Menu
{
    public:
        MenuPagos();
        void aparecer();

    private:
        ManagerPagos _managerPagos;
};
