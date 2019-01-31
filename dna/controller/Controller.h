//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_CONTROLLER_H
#define DNA_CONTROLLER_H

#include "../model/DnaData.h"
#include "../view/UI.h"


class Controller
{
private:
    DnaData m_db;
    UI * m_ui;

public:
    Controller(DnaData db, UI * ui);
    void run();
};


#endif //DNA_CONTROLLER_H
