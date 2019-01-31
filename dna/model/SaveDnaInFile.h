//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_SAVEDNAINFILE_H
#define DNA_SAVEDNAINFILE_H

#include "DnaSequence.h"
#include "SharedPtr.h"

class SaveDnaInFile
{
private:
    std::string m_fileName;

public:
    SaveDnaInFile(const char * path);
    SaveDnaInFile(SaveDnaInFile const & other);
    ~SaveDnaInFile();
    void write(const SharedPtr<IDnaSequence> dna);
};

#endif //DNA_SAVEDNAINFILE_H
