#pragma once

#include "Menu.h"
#include "../Managers/ManagerInscripciones.h"


class MenuInscripciones : public Menu
{
    public:
        MenuInscripciones();
        void aparecer();

    private:
        ManagerInscripciones _managerInscripciones;
};
