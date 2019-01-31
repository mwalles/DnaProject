//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_DNADATA_H
#define DNA_DNADATA_H

#include "SharedPtr.h"
#include "DnaSequence.h"
#include <string>
#include <map>


class DNA
{
public:
    DNA(unsigned int dnaNumber, std::string dnaName, SharedPtr<IDnaSequence> dna, char stat);
    ~DNA();

    unsigned int dnaNumber;
    std::string dnaName;
    SharedPtr<IDnaSequence> sequence;
    char status;
};


class DnaData
{
public:
    DnaData();
    ~DnaData();
    void add(unsigned int dnaNumber, std::string dnaName, SharedPtr<IDnaSequence> dna, char stat);
    std::string getDnaAsString(unsigned int dnaNumber);
    std::string getDnaAsString(std::string dnaName);
    bool isExist(std::string dnaName);
    unsigned int getSize();

    SharedPtr<IDnaSequence> getDna(std::string &dnaName);
    SharedPtr<IDnaSequence> getDna(unsigned int dnaNumber);
    std::string getSequenceName(unsigned int seqNumber);
    void setStatus(std::string dnaName, char stat);
    void setSequence(std::string dnaName, SharedPtr<IDnaSequence> dna);



private:
    unsigned int m_size;

    std::map<unsigned int, DNA*> m_mapByID;
    std::map<std::string, DNA*> m_mapByName;

};


#endif //DNA_DNADATA_H
