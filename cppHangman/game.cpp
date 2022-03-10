#include "game.h"
#include <iostream>

using namespace std;

Game::Game(string x){
    word = x;
    guesses = 0;
    stars = setStars();
}


string Game::getWord(){
    return word;
}

string Game::setStars(){
    string stars;
    for(const auto& i : word){
        stars.push_back('*');
    }
    return stars;
} 

string Game::getStars(){
    return stars;
}

void Game::addGuess(){
    char guess;
    unsigned int count=0;
    cout<< "Some letters remain: "<<getStars()<<endl;
    cout<<"What letter would you like to try?"<<endl;
    cout<<"Enter a letter: ";
    cin>>guess;

    for (int i = 0; i<word.size(); i++){
        if (word[i] == guess){
            stars[i]=guess;
            count++;
        }
    }
    cout<< guess <<" is in this word "<<count<<" times."<<endl;
}