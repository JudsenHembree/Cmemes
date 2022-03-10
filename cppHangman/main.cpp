#include "menu.h"
#include "game.h"
#include "word.h"

int main(){

    menu hangMenu;
    hangMenu.printIntro();
    string filename = hangMenu.reqFile();

    word wordBase(filename);
    string hangmanWord = wordBase.grabWord();
    
    Game game(hangmanWord);
    cout<<game.getWord()<<endl;
    hangMenu.preamble();
    cout<<game.getStars()<<endl;

    while(game.getWord()!=game.getStars()){
        game.addGuess();
    }

    return 0;
}