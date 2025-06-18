#pragma once
#include "Menu.h"
#include "../Managers/ManagerActividades.h"

class MenuActividades : public Menu
{
    public:
        MenuActividades();
        void aparecer();

    private:
        ManagerActividades _managerActividades;
};
