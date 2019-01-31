//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_LOADDNAFILE_H
#define DNA_LOADDNAFILE_H


#include <string>
#include "DnaSequence.h"

class LoadDnaFile
{
private:
    std::string m_fileData;
public:
    LoadDnaFile(const char * path);
    LoadDnaFile(LoadDnaFile const & other);
    ~LoadDnaFile();
    DnaSequence read();
};



#endif //DNA_LOADDNAFILE_H
