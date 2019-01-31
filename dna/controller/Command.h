//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_COMMAND_H
#define DNA_COMMAND_H

#include "../model/DnaData.h"
#include <vector>


class ICommand
{
public:
    virtual std::string run(DnaData *data, std::vector<std::string> args) = 0;
    static unsigned int m_serialNumber;
};


class New : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    unsigned int nameSerialNumber;
    static int registerNumber;
};


class Load : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    static int registerNumber;
};


class Save : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    static int registerNumber;
};



class List : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    static int registerNumber;
};


class Show : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    static int registerNumber;
};



class Pair : public ICommand
{
public:
    std::string run(DnaData *data, std::vector<std::string> args);

private:
    static int registerNumber;
    unsigned int nameSerialNumber;
};


//class Dup : public ICommand
//{
//public:
//    std::string run(DnaData *data, std::vector<std::string> args);
//
//private:
//    static int registerNumber;
//    unsigned int nameSerialNumber;
//};

#endif //DNA_COMMAND_H
