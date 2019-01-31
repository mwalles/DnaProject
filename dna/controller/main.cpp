//
// Created by mlevin on 12/30/18.
//

#include "Controller.h"
#include "../model/DnaData.h"
#include "../view/UI.h"

#include "../model/DnaData.cpp"
#include "../model/DnaSequence.cpp"
#include "../model/Nucleotide.cpp"
#include "../model/SaveDnaInFile.cpp"
#include "../model/LoadDnaFile.cpp"
#include "../model/DnaSequencePair.cpp"

#include "../view/UI.cpp"

#include "Command.cpp"
#include "Controller.cpp"
#include "Factory.cpp"
#include "Parser.cpp"


int main()
{
    DnaData db;
    UI * ui = new CLI;

    Controller cntrl(db, ui);
    cntrl.run();

    return 0;
}

