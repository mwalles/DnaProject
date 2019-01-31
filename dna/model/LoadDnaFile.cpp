//
// Created by mlevin on 12/30/18.
//

#include "LoadDnaFile.h"

#include <fstream>
#include <iostream>

LoadDnaFile::LoadDnaFile(const char * path)
{
    std::ifstream myfile(path);
    if (!myfile.is_open())
        throw std::logic_error("unable to open file");

    while (!myfile.eof())
    {
        myfile >> m_fileData;
    }
    myfile.close();
}

LoadDnaFile::LoadDnaFile(LoadDnaFile const & other) :m_fileData(other.m_fileData)
{}

LoadDnaFile::~LoadDnaFile()
{}

DnaSequence LoadDnaFile::read()
{
    DnaSequence DNA(m_fileData);
    return DNA;
}