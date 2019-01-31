//
// Created by mlevin on 12/30/18.
//

#include "Command.h"
#include "../model/LoadDnaFile.h"
#include "../model/SaveDnaInFile.h"
#include "../model/DnaSequencePair.h"
#include <list>
#include <iterator>
#include "Factory.h"


unsigned int ICommand::m_serialNumber = 0;

std::string handleException(std::exception_ptr expPtr)
{
    try
    {
        if(expPtr)
            std::rethrow_exception(expPtr);
    }
    catch(const std::exception& e)
    {
        return std::string(e.what());
    }
    return std::string("None");
}

std::string wrongVectorLenMessage(size_t len, std::string commandName)
{
    if (len < 2)
        return std::string("too few arguments for " + commandName + " command, at least 1 required");

    if (len > 3)
        return std::string("too many arguments for " + commandName + " command");

    return "";
}

std::string notExistDnaName(DnaData *data, std::string dnaName)
{
    if(data->isExist(dnaName))
    {
        int i = 1;
        while (data->isExist(dnaName + std::to_string(i)))
        {
            ++i;
        }
        dnaName += std::to_string(i);
    }

    return dnaName;
}

bool isNumber(std::string str)
{
    if (str.at(0) == '#')
        return true;
    return false;
}







// --- new ----

int New::registerNumber = Factory::registerCommand("new", new New);

std::string New::run(DnaData *data, std::vector<std::string> args)
{
    std::string dnaName;

    if (wrongVectorLenMessage(args.size(), args[0]) != "")
        return wrongVectorLenMessage(args.size(), args[0]);

    if (args.size() == 2)
        dnaName = "seq" + std::to_string(++nameSerialNumber);
    else
    {
        if (args[2].at(0) != '@')
            return std::string("name must start with @");
        dnaName = notExistDnaName(data, args[2].substr(1));
    }

    try
    {
        SharedPtr<IDnaSequence> dna(new DnaSequence(args[1]));

        data->add(++m_serialNumber, dnaName, dna, 'o');
    }
    catch (...)
    {
        --nameSerialNumber;
        return handleException(std::current_exception());
    }

    return data->getDnaAsString(m_serialNumber);
}


//--- load ----

int Load::registerNumber = Factory::registerCommand("load", new Load);

std::string Load::run(DnaData *data, std::vector<std::string> args)
{
    if (wrongVectorLenMessage(args.size(), args[0]) != "")
        return wrongVectorLenMessage(args.size(), args[0]);

    std::size_t pos = args[1].find(".");

    std::string dnaName = args[1].substr(0, pos);

    if (args.size() == 2)
    {
        dnaName = notExistDnaName(data, dnaName);
    }
    else
    {
        if (args[2].at(0) != '@')
            return std::string("name must start with @");

        dnaName = notExistDnaName(data, args[2].erase(0, 1));
    }

    try
    {
        LoadDnaFile d(args[1].c_str());
        SharedPtr<IDnaSequence> dna(new DnaSequence(d.read()));

        data->add(++m_serialNumber, dnaName, dna, '-');
    }
    catch (...)
    {
        return handleException(std::current_exception());
    }

    return data->getDnaAsString(m_serialNumber);
}


//--- save ----

int Save::registerNumber = Factory::registerCommand("save", new Save);

std::string Save::run(DnaData *data, std::vector<std::string> args)
{
    if (wrongVectorLenMessage(args.size(), args[0]) != "")
        return wrongVectorLenMessage(args.size(), args[0]);

    std::string dnaName;
    SharedPtr<IDnaSequence> dna;

    if (args[1].at(0) == '#')
    {
        unsigned int dnaNumber = std::stoi(args[1].erase(0, 1));
        dna = data->getDna(dnaNumber);
        dnaName = data->getSequenceName(dnaNumber);
    }
    else if (args[1].at(0) == '@')
    {
        dnaName = args[1].erase(0, 1);
        dna = data->getDna(dnaName);
    }
    else
        return std::string("please mark id with # and name with @");


    std::string fileName;
    if (args.size() == 2)
        fileName = dnaName + ".rawdna";
    else
        fileName = args[2] + ".rawdna";

    try
    {
        if (!dna)
            return std::string("no such dna in collection");

        SaveDnaInFile s(fileName.c_str());
        s.write(dna);

        data->setStatus(dnaName, '-');

        return std::string("dna " + args[1] + " saved to file " + fileName);
    }
    catch (...)
    {
        return handleException(std::current_exception());
    }
}


//--- list ----

int List::registerNumber = Factory::registerCommand("list", new List);

std::string List::run(DnaData *data, std::vector<std::string> args)
{
    std::string dataList = "";
    unsigned int nextDnaNumber = 0;

    for (unsigned int i = 0; i < data->getSize(); ++i)
    {
        std::string next = data->getDnaAsString(nextDnaNumber);

        while (next == "")
        {
            next = data->getDnaAsString(++nextDnaNumber);
        }

        std::size_t pos = next.find(":");

        std::string seq = next.substr(pos+2);
        if (seq.length() > 40)
            seq = seq.substr(0, 40);

        next = next.substr(0, pos+1);

        dataList += next;
        dataList += ' ';
        dataList += seq;
        dataList += "\n";

        ++nextDnaNumber;
    }

    return dataList;
}


//--- show ----

int Show::registerNumber = Factory::registerCommand("show", new Show);

std::string Show::run(DnaData *data, std::vector<std::string> args)
{
    if (wrongVectorLenMessage(args.size(), args[0]) != "")
        return wrongVectorLenMessage(args.size(), args[0]);

    std::string dna;
    size_t seqLen = (args.size() > 2) ? std::stoi(args[2]) : 99;

    if (args[1].at(0) == '#')
    {
        unsigned int dnaNumber = std::stoi(args[1].substr(1));
        dna = data->getDnaAsString(dnaNumber);
    }
    else if (args[1].at(0) == '@')
    {
        std::string dnaName = args[1].substr(1);
        dna = data->getDnaAsString(dnaName);
    }
    else
        return std::string("plese mark id with # and name with @");

    if (dna == "")
        return "no such dna name in the collection";

    char stat = dna.at(0);
    std::string seq = dna.substr(dna.find(':') + 2);
    if (seq.length() > seqLen)
        seq = seq.substr(0, seqLen);
    dna = dna.substr(2, dna.find(':') - 1);

    switch (stat)
    {
        case 'o': dna += " new\n";
            break;
        case '-': dna += " up-to-date\n";
            break;
        case '*': dna += " modified\n";
            break;
        default:
            break;
    }

    dna += seq;

    return dna;

}


//--- pair ----

int Pair::registerNumber = Factory::registerCommand("pair", new Pair);

std::string Pair::run(DnaData *data, std::vector<std::string> args)
{
    if (args.size() != 4 && args.size() != 2)
        return "too few arguments for pair command";

    std::string dnaName;
    SharedPtr<IDnaSequence> dna;

    if (args[1].at(0) == '#')
    {
        unsigned int dnaNumber = std::stoi(args[1].erase(0, 1));
        dna = data->getDna(dnaNumber);
        dnaName = data->getSequenceName(dnaNumber);
    }
    else if (args[1].at(0) == '@')
    {
        dnaName = args[1].erase(0, 1);
        dna = data->getDna(dnaName);
    }
    else
        return std::string("please mark id with # and name with @");


    if (!dna)
        return "no such dna sequence";


    if (args.size() > 2)
    {
        if (args[2] != ":")
            return "syntax op this operation : pair <seq> [: @<name> | @@]";

        if (args[3] == "@@")
        {
            int i = 0;
            dnaName += "_p";
            dnaName += std::to_string(++i);
            if (data->isExist(dnaName))
            {
                while (data->isExist(dnaName))
                {
                    dnaName.replace(dnaName.end() - 1, dnaName.end(), std::to_string(++i));
                }
            }
        }
        else
        {
            dnaName = args[3].substr(1);
        }
    }


    try
    {
        SharedPtr<IDnaSequence> Idna(new DnaSequencePair(dna));

        if (args.size() == 2)
            data->setSequence(dnaName, Idna);
        else
            data->add(++m_serialNumber, dnaName, Idna, '*');
    }
    catch (...)
    {
        return handleException(std::current_exception());
    }

    return data->getDnaAsString(dnaName);
}


//--- dup ----

//int Dup::registerNumber = Factory::registerCommand("dup", new Dup);
//
//std::string Pair::run(DnaData *data, std::vector<std::string> args)
//{
//    if (args.size() > 4 || args.size() < 4)
//        return "too few arguments for pair command";
//
//
//    std::string dnaName;
//    SharedPtr<IDnaSequence> dna;
//
//    if (args[1].at(0) == '#')
//    {
//        unsigned int dnaNumber = std::stoi(args[1].erase(0, 1));
//        dna = data->getDna(dnaNumber);
//        dnaName = data->getSequenceName(dnaNumber);
//    }
//    else if (args[1].at(0) == '@')
//    {
//        dnaName = args[1].erase(0, 1);
//        dna = data->getDna(dnaName);
//    }
//    else
//        return std::string("please mark id with # and name with @");
//
//
//    if (!dna)
//        return "no such dna sequence";
//
//    if (args[3] == "@@")
//    {
//        int i = 0;
//        dnaName += "_p";
//        dnaName += std::to_string(++i);
//        if(data->isExist(dnaName))
//        {
//            while (data->isExist(dnaName))
//            {
//                dnaName.replace(dnaName.end()-1, dnaName.end(), std::to_string(++i));
//            }
//        }
//    }
//    else
//    {
//        dnaName = args[3].substr(1);
//    }
//
//    try
//    {
//        SharedPtr<IDnaSequence> Idna(new DnaSequencePair(dna));
//
//        data->add(++m_serialNumber, dnaName, Idna, '*');
//    }
//    catch (...)
//    {
//        return handleException(std::current_exception());
//    }
//
//    return data->getDnaAsString(m_serialNumber);
//}


