//
// Created by mlevin on 1/16/19.
//

#ifndef DNA_DNASEQUENCESLICE_H
#define DNA_DNASEQUENCESLICE_H

class DnaSequenceSlice
{
public:
    DnaSequencePair(SharedPtr<IDnaSequence> dna, size_t fromIndex, size_t toIndex = 0);
    const Nucleotide operator[](size_t index) const ;


    size_t getLength() const;

private:
    SharedPtr<IDnaSequence> m_dnaSequence;

    size_t startIndex;
    size_t endIndex;
};


#endif //DNA_DNASEQUENCESLICE_H
