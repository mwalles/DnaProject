//
// Created by mlevin on 12/30/18.
//

#ifndef DNA_UI_H
#define DNA_UI_H

#include <string>

class UI
{
public:
    virtual std::string get() = 0;
    virtual void display(std::string message) = 0;
};

class CLI : public UI
{
public:
    CLI(std::string prompt = "> cmd >>> ");
    std::string get();
    void display(std::string message);

private:
    std::string m_prompt;
};


#endif //DNA_UI_H
