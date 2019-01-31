//
// Created by mlevin on 12/30/18.
//

#include "UI.h"
#include <iostream>

CLI::CLI(std::string prompt):m_prompt(prompt)
{}

std::string CLI::get()
{
    std::string command = "";
    while (command == "")
    {
        std::cout << m_prompt;
        std::getline(std::cin, command);
    }
    return command;
}

void CLI::display(std::string message)
{
    std::cout << message << std::endl;
}