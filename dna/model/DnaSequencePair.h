//
// Created by mlevin on 1/5/19.
//

#ifndef DNA_DNASEQUENCEPAIR_H
#define DNA_DNASEQUENCEPAIR_H

#include "DnaSequence.h"
#include "SharedPtr.h"


class DnaSequencePair : public IDnaSequence
{
public:
    DnaSequencePair(SharedPtr<IDnaSequence> dna);
    const Nucleotide operator[](size_t index) const ;

    size_t getLength() const;

private:
    SharedPtr<IDnaSequence> m_dnaSequence;
};


#endif //DNA_DNASEQUENCEPAIR_H
