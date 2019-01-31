//
// Created by mlevin on 12/30/18.
//

#include <assert.h> //getPair assert
#include "Nucleotide.h"


Nucleotide Nucleotide::getPair() const
{
    char pair;

    switch (m_nucleotide) {
        case 'A':
            pair = 'T';
            break;
        case 'C':
            pair = 'G';
            break;
        case 'G':
            pair = 'C';
            break;
        case 'T':
            pair = 'A';
        default:
            assert(this->m_nucleotide);
    }

    return Nucleotide(pair);
}

Nucleotide& Nucleotide::operator=(char nucleotide)
{
    try
    {
        m_nucleotide = isValid(nucleotide);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument(e.what());
    }

    return *this;
}

Nucleotide& Nucleotide::operator=(const Nucleotide &other)
{
    m_nucleotide = other.m_nucleotide;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Nucleotide& n)
{
    os << n.m_nucleotide;

    return os;
}