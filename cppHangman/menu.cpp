#include "menu.h"

using namespace std;

void menu::printIntro(){
    cout<<"Welcome to hangman."<<endl;
}

void menu::preamble(){
    cout<<"A word has been selected. Your word is ..."<<endl;
}

string menu::reqFile(){
    string fileName;
    cout<<"Enter a word library as a .txt file:";
    cin>>fileName;
    return fileName;
}