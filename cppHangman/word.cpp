#include "word.h"
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

word::word(string x){
    wordList.open(x,ios::in);
}

ifstream& word::GotoLine(ifstream& file, unsigned int num){
    file.seekg(ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    return file;
}

unsigned int word::generate(){
    int seed = chrono::system_clock::now().time_since_epoch().count();
    uniform_int_distribution<> distr(1,12972);
    default_random_engine engine;
    engine.seed(seed);
    auto randomNum = distr(engine);
    return randomNum;
}

string word::grabWord(){
    string word;
    auto wordLine = generate();
    GotoLine(wordList, wordLine);
    getline(wordList,word);

    return word;
}