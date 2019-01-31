//
// Created by mlevin on 12/30/18.
//

#include "Controller.h"
#include "Parser.h"
#include "Factory.h"
#include <string>

Controller::Controller(DnaData db, UI *ui)
{
    m_db = db;
    m_ui = ui;
}

void Controller::run()
{
    while (true)
    {
        std::string command = m_ui->get();

        std::vector<std::string> parsedCommand = Parser::parse(command);

        if(parsedCommand[0] == "quit")
            break;

        ICommand * runCommand = Factory::getCommand(parsedCommand[0]);

        if(runCommand)
            m_ui->display(runCommand->run(&m_db, parsedCommand));

        else
            m_ui->display("command " + parsedCommand[0] + " not found");
    }
}
