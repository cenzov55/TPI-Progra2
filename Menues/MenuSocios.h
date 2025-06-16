#pragma once
#include "Menu.h"
#include "../Managers/ManagerSocios.h"

class MenuSocios : public Menu
{
    public:
        MenuSocios();
        void aparecer();
    private:
        ManagerSocios _managerSocios;
};
