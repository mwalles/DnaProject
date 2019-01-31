//
// Created by mlevin on 12/30/18.
//

#include "Parser.h"
#include <cstring>

std::vector<std::string> Parser::parse(std::string command)
{
    std::vector<std::string> commandVector;

    char *token;

    char *commandStr = strdup(command.c_str());
    char delimiters[1] = {' '};

    token = strtok(commandStr, delimiters);

    while( token != NULL )
    {
        std::string stringToken(token);
        commandVector.push_back(stringToken);
        token = strtok(NULL, delimiters);
    }

    return commandVector;
}