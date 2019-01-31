//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_DNASEQUENCE_H
#define DNA_DNASEQUENCE_H

#include "Nucleotide.h"
#include <cstddef>


class IDnaSequence
{
public:
    virtual ~IDnaSequence(){};

    virtual const Nucleotide operator[](size_t index) const = 0;
    virtual size_t getLength() const = 0;
};


class DnaSequence : public IDnaSequence
{
public:
    explicit DnaSequence() {}
    explicit DnaSequence(const char* sequence);
    explicit DnaSequence(const std::string& sequence);
    DnaSequence(const DnaSequence &other);
    ~DnaSequence();

    Nucleotide& operator[](size_t index);
    const Nucleotide operator[](size_t index) const;

    bool operator==(const IDnaSequence *other) const ;
    bool operator!=(const IDnaSequence *other) const ;

    IDnaSequence* operator=(const std::string& sequence);
    IDnaSequence* operator=(const char* sequence);

    size_t getLength() const;
    Nucleotide* get() const;

private:

    Nucleotide* m_sequence;
    size_t m_length;

    bool isValid(size_t len);
    void initSequence(const char *sequence);
};



#endif //DNA_DNASEQUENCE_H
