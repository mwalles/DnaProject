//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_FACTORY_H
#define DNA_FACTORY_H

#include "Command.h"

class Factory
{
public:
    ~Factory();
    static std::map<std::string, ICommand*>& getCommandMap();
    static int registerCommand(std::string key, ICommand* command);
    static ICommand* getCommand(std::string commandName);
};

#endif //DNA_FACTORY_H
