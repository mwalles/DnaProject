//
// Created by mlevin on 12/30/18.
//

#include "DnaSequence.h"
#include "SharedPtr.h"
#include <cstring>

DnaSequence::DnaSequence(const char* sequence)
{
    try
    {
        initSequence(sequence);
    }
    catch (const std::invalid_argument &ex)
    {
        throw std::invalid_argument(ex.what());
    }
    catch (const std::bad_alloc &ex)
    {
        throw std::bad_alloc();
    }
}

DnaSequence::DnaSequence(const std::string& sequence)
{
    try
    {
        initSequence(sequence.c_str());
    }
    catch (const std::invalid_argument &ex)
    {
        throw std::invalid_argument(ex.what());
    }
    catch (const std::bad_alloc &ex)
    {
        throw std::bad_alloc();
    }

}

DnaSequence::DnaSequence(const DnaSequence &other)
{
    try
    {
        m_sequence = new Nucleotide[other.m_length];
    }
    catch (const std::bad_alloc &ex)
    {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < other.m_length; ++i)
        m_sequence[i] = other.m_sequence[i];

    m_length = other.m_length;
}

DnaSequence::~DnaSequence()
{
    delete [] m_sequence;
}

void DnaSequence::initSequence(const char *sequence)
{
    m_length = strlen(sequence);
    if (!isValid(m_length))
        throw std::invalid_argument("The resulting sequence length is incorrect");
    m_sequence = new Nucleotide[m_length];
    for (size_t i = 0; i < m_length; ++i)
        m_sequence[i] = sequence[i];
}

Nucleotide& DnaSequence::operator[](size_t index)
{
    if (index > m_length || index < 0)
        throw std::invalid_argument("index out of range, Nucleotide& DnaSequence::operator[](int index)");

    return m_sequence[index];
}

const Nucleotide DnaSequence::operator[](size_t index) const
{
    if (index > m_length || index < 0)
        throw std::invalid_argument("index out of range, Nucleotide& DnaSequence::operator[](int index)");

    return m_sequence[index];
}

bool DnaSequence::operator==(const IDnaSequence *other) const
{
    for (size_t i = 0; i < m_length; ++i)
        if (m_sequence[i] != (*other)[i])
            return false;
    return true;
}

bool DnaSequence::operator!=(const IDnaSequence *other) const
{
    for (size_t i = 0; i < m_length; ++i)
        if (m_sequence[i] != (*other)[i])
            return true;
    return false;
}

IDnaSequence* DnaSequence::operator=(const std::string& sequence)
{
    if (!isValid(strlen(sequence.c_str())))
        throw std::invalid_argument("The resulting sequence length is incorrect");

    delete[] m_sequence;
    m_length = strlen(sequence.c_str());

    try
    {
        m_sequence = new Nucleotide[m_length];
    }
    catch (const std::bad_alloc &ex)
    {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < m_length; ++i)
        m_sequence[i] = sequence[i];

    return this;
}

IDnaSequence* DnaSequence::operator=(const char* sequence)
{
    if (!isValid(strlen(sequence)))
        throw std::invalid_argument("The resulting sequence length is incorrect");

    delete[] m_sequence;
    m_length = strlen(sequence);

    try
    {
        m_sequence = new Nucleotide[m_length];
    }
    catch (const std::bad_alloc &ex)
    {
        throw std::bad_alloc();
    }

    for (size_t i = 0; i < m_length; i++)
        m_sequence[i] = sequence[i];

    return this;
}

size_t DnaSequence::getLength() const
{
    return m_length;
}

Nucleotide* DnaSequence::get() const
{
    return m_sequence;
}

bool DnaSequence::isValid(size_t len)
{
    return len % 3 == 0;
}


std::ostream& operator<<(std::ostream& os, SharedPtr<IDnaSequence> dna)
{
    for (size_t i = 0; i < dna->getLength(); ++i)
    {
        os << dna->operator[](i).get();
    }

    return os;
}
