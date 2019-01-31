//
// Created by mlevin on 12/30/18.
//

#include "Factory.h"

std::map<std::string, ICommand*>& Factory::getCommandMap()
{
    static std::map<std::string, ICommand*> commandMap;

    return commandMap;
}

int Factory::registerCommand(std::string key, ICommand* command)
{
    std::pair<std::map<std::string, ICommand*>::iterator, bool> ret;
    ret = getCommandMap().insert(std::pair<std::string, ICommand*>(key, command));

    return (ret.second)? 1:0;
}

ICommand* Factory::getCommand(std::string commandName)
{
    std::map<std::string, ICommand*>::iterator it;
    it = getCommandMap().find(commandName);

    if (it == getCommandMap().end())
        return NULL;

    return it->second;
}