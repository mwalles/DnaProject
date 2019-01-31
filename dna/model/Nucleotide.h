//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_NUCLEOTIDE_H
#define DNA_NUCLEOTIDE_H

#include <iostream>


class Nucleotide
{
public:
    Nucleotide();
    Nucleotide(char c);

    Nucleotide& operator=(char nucleotide);
    Nucleotide& operator=(const Nucleotide &other);
    friend std::ostream& operator<<(std::ostream& os, const Nucleotide& nucleotide);
    bool operator==(const Nucleotide& nucleotide) const ;
    bool operator!=(const Nucleotide& nucleotide) const ;
    bool operator==(char nucleotide) const ;
    bool operator!=(char nucleotide) const ;
    friend std::ostream& operator<<(std::ostream& os, const Nucleotide& n);

    Nucleotide getPair() const ;
    char get() const ;
    char isValid(char nucleotide);

private:
    char m_nucleotide;
};

//// inline definition ////

inline char Nucleotide::isValid(char nucleotide)
{
    nucleotide = (char)toupper(nucleotide);

    if (nucleotide != 'T' && nucleotide != 'C' && nucleotide != 'G' && nucleotide != 'A')
        throw std::invalid_argument("invalid value for nucleotide");

    return nucleotide;
}

inline Nucleotide::Nucleotide() :m_nucleotide('A')
{}

inline Nucleotide::Nucleotide(char c)
{
    try
    {
        m_nucleotide = isValid(c);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::invalid_argument(e.what());
    }
}

inline char Nucleotide::get() const
{
    return m_nucleotide;
}

inline bool Nucleotide::operator==(const Nucleotide& nucleotide) const
{
    return m_nucleotide == nucleotide.m_nucleotide;
}

inline bool Nucleotide::operator!=(const Nucleotide& nucleotide) const
{
    return m_nucleotide != nucleotide.m_nucleotide;
}

inline bool Nucleotide::operator==(char nucleotide) const
{
    return m_nucleotide == nucleotide;
}

inline bool Nucleotide::operator!=(char nucleotide) const
{
    return m_nucleotide != nucleotide;
}


#endif //DNA_NUCLEOTIDE_H
