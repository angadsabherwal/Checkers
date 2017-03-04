#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "Files/boardDefinition.h"
#include "Files/display.h"
#include "Files/player2CheckAndPlay.h"
#include "Files/alphaBetaSearch.h"

extern Tile *tile[9][9];
extern QWidget *gameWidget;
extern vvint mainBoard;
vector<pair<int, int> > validCaptureMoves;

extern int countClicks;

void validateMouseEvent(Tile *tmp);

void Tile::mousePressEvent(QMouseEvent *event){
    countClicks += 1;
    validateMouseEvent(this);
}

void backToNormal(){
    for(int i = 1; i <= boardSz; i++){
        for(int j = 1; j <= boardSz; j++){
            tile[i][j]->tileDisplay();
        }
    }
}

int posx1, posx2, posy1, posy2;

void validateMouseEvent(Tile *tmp){

    if(chance == true){
        countClicks = 0;
        return;
    }

    if(countClicks == 1){
        if(tmp->piece <= 2){
            countClicks = 0;
            return;
        }
        posx1 = tmp->position.first;
        posy1 = tmp->position.second;
        displayGreen(tile[tmp->position.first][tmp->position.second]);
        countClicks++;
    }
    else{
        countClicks = 0;

        if(tmp->piece != 0){
            backToNormal();
            return;
        }
        posx2 = tmp->position.first;
        posy2 = tmp->position.second;

        if(!checkAndPlay(mainBoard, posx1, posx2, posy1, posy2))
        {
            backToNormal();
            return;
        }
        printBoard(gameWidget, tile, mainBoard);

        if(chance)
        {
            chance = !chance;
            return;
        }
        chance = !chance;
        mainBoard = alphaBetaSearch(mainBoard);
        printBoard(gameWidget, tile, mainBoard);
        chance = !chance;
    }
}
#endif // MOUSEEVENT_H
