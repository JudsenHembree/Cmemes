#ifndef WORD_H
#define WORD_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class word{
    public:
        unsigned int generate();
        string grabWord();
        ifstream& GotoLine(ifstream&, unsigned int);
        word(string);

    private:
        ifstream wordList;
};

#endif