#ifndef GAME_H
#define GAME_H

#include <string>
#include <ostream>

using namespace std;


class Game{
    public:
        Game(string);
        string getWord();
        string getStars();
        string asStars();
        void addGuess();
        string setStars();
    private:
        string word;
        string stars;
        unsigned int guesses;

};

#endif