//
// Created by mlevin on 12/30/18.
//

#include "DnaData.h"

DNA::DNA(unsigned int dnaNum, std::string dnaNam, SharedPtr<IDnaSequence> dna, char stat)
:dnaNumber(dnaNum),dnaName(dnaNam),sequence(dna),status(stat)
{
}


DnaData::DnaData():m_size(0){}

DnaData::~DnaData()
{
    m_mapByName.clear();
    m_mapByID.clear();
}

void DnaData::add(unsigned int dnaNumber, std::string dnaName, SharedPtr<IDnaSequence> dna, char stat)
{
    DNA *dnaSequence = new DNA(dnaNumber, dnaName, dna, stat);

    m_mapByID.insert(std::pair<unsigned int, DNA*>(dnaNumber, dnaSequence));

    m_mapByName.insert(std::pair<std::string, DNA*>(dnaName, dnaSequence));

    ++m_size;
}

bool DnaData::isExist(std::string dnaName)
{
    std::map<std::string, DNA*>::iterator it;
    it = m_mapByName.find(dnaName);

    return it != m_mapByName.end();
}

unsigned int DnaData::getSize() { return m_size; }

std::string DnaData::getDnaAsString(unsigned int dnaNumber)
{
    std::map<unsigned int, DNA*>::iterator it =
            m_mapByID.find(dnaNumber);

    if (it == m_mapByID.end())
        return "";

    std::string dnaAsString = "";
    dnaAsString += it->second->status;
    dnaAsString += " [" + std::to_string(dnaNumber) + "] ";
    dnaAsString += it->second->dnaName;
    dnaAsString += ": ";


    for (size_t i = 0; i < it->second->sequence->getLength(); ++i)
        dnaAsString += it->second->sequence->operator[](i).get();

    return dnaAsString;

}

std::string DnaData::getDnaAsString(std::string dnaName)
{
    std::map<std::string, DNA*>::iterator it =
            m_mapByName.find(dnaName);

    if (it == m_mapByName.end())
        return "";

    std::string dnaAsString = "";
    dnaAsString += it->second->status;
    dnaAsString += " [" + std::to_string(it->second->dnaNumber) + "] ";
    dnaAsString += it->second->dnaName;
    dnaAsString += ": ";

    for (size_t i = 0; i < it->second->sequence->getLength(); ++i)
        dnaAsString += it->second->sequence->operator[](i).get();

    return dnaAsString;

}

SharedPtr<IDnaSequence> DnaData::getDna(std::string &dnaName)
{
    std::map<std::string, DNA*>::iterator it;
    it = m_mapByName.find(dnaName);

    if(it == m_mapByName.end())
        return SharedPtr<IDnaSequence>(NULL);

    return it->second->sequence;
}

SharedPtr<IDnaSequence> DnaData::getDna(unsigned int dnaNumber)
{
    std::map<unsigned int, DNA*>::iterator it;
    it = m_mapByID.find(dnaNumber);

    if(it == m_mapByID.end())
        return SharedPtr<IDnaSequence>(NULL);

    return it->second->sequence;
}

std::string DnaData::getSequenceName(unsigned int seqNumber)
{
    std::map<unsigned int, DNA*>::iterator it;
    it = m_mapByID.find(seqNumber);

    if(it == m_mapByID.end())
        return "";

    return it->second->dnaName;
}

void DnaData::setStatus(std::string dnaName, char stat)
{
    if (stat != 'o' && stat != '-' && stat != '*')
        throw std::invalid_argument("invalid argument for status");

    std::map<std::string, DNA*>::iterator it;
    it = m_mapByName.find(dnaName);

    if(it != m_mapByName.end())
        it->second->status = stat;
}

void DnaData::setSequence(std::string dnaName, SharedPtr<IDnaSequence> dna)
{
    std::map<std::string, DNA*>::iterator it;
    it = m_mapByName.find(dnaName);

    if(it != m_mapByName.end())
        it->second->sequence = dna;
}
