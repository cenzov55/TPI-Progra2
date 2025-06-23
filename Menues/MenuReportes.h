#pragma once
#include "Menu.h"
#include "../Managers/ManagerReportes.h"

class MenuReportes : public Menu
{
    public:
        MenuReportes();
        void aparecer();
    private:
        ManagerReportes _managerReportes;
};
