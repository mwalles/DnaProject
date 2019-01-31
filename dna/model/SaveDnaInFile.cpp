//
// Created by mlevin on 12/30/18.
//

#include <iostream>
#include <fstream>
#include "SaveDnaInFile.h"


SaveDnaInFile::SaveDnaInFile(const char * path) :m_fileName(path)
{}

SaveDnaInFile::SaveDnaInFile(const SaveDnaInFile & other) : m_fileName(other.m_fileName)
{}

SaveDnaInFile::~SaveDnaInFile()
{}

void SaveDnaInFile::write(const SharedPtr<IDnaSequence> dna)
{
    std::ofstream myFile;
    myFile.open(m_fileName.c_str(), std::ostream::out);

    if (!myFile.is_open())
        throw std::logic_error("unable to open file");

    myFile << dna;
    myFile.close();
}