//
// Created by mlevin on 1/5/19.
//

#include "DnaSequencePair.h"

DnaSequencePair::DnaSequencePair(SharedPtr<IDnaSequence> dna):m_dnaSequence(dna)
{}

const Nucleotide DnaSequencePair::operator[](size_t index) const
{
    return m_dnaSequence->operator[](index).getPair();
}

size_t DnaSequencePair::getLength() const
{
    return m_dnaSequence->getLength();
}