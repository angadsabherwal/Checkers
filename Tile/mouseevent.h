#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H
#include "Files/boardDefinition.h"
#include "Files/display.h"
#include "Files/player2CheckAndPlay.h"
#include "Files/alphaBetaSearch.h"
#include <QMessageBox>

extern Tile *tile[9][9];
extern QWidget *gameWidget;
extern vvint mainBoard;
//extern QMessageBox Msgbox;
vpp validCaptureMoves;
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

    bool flag2 = true;
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

        if(validCaptureMoves.size())
        {
            bool flag = false;
            for(int i=0; i < validCaptureMoves.size(); i++)
            {
                if(validCaptureMoves[i].first == pi(posx1,posy1) && validCaptureMoves[i].second == pi(posx2,posy2)  )
                {
                    flag = true;
                    break;
                }
            }

            if(flag)
            {
                mainBoard[posx2][posy2] = mainBoard[posx1][posy1];
                mainBoard[posx1][posy1] = mainBoard[(posx1+posx2)/2][(posy1+posy2)/2]=0;
                printBoard(gameWidget, tile, mainBoard);
                validCaptureMoves.clear();

                if(possibleCaptureMoves(mainBoard, validCaptureMoves, posx2, posy2))
                    return;
                chance = !chance;
                flag2 = false;
            }
            else
            {
                backToNormal();
                return;
            }
        }

        if(flag2)
        {
            if(!checkAndPlay(mainBoard, posx1, posx2, posy1, posy2, validCaptureMoves))
            {
                backToNormal();
                return;
            }
            printBoard(gameWidget, tile, mainBoard);

            chance = !chance;

            if(!chance)
                return;
        }

        if(terminalTest(mainBoard, chance) )
        {
            QMessageBox Msgbox;
            Msgbox.setText("Conratulations!!\nYou Won");
            Msgbox.exec();
            return;
        }

        mainBoard = alphaBetaSearch(mainBoard);
        printBoard(gameWidget, tile, mainBoard);
        chance = !chance;

        if(terminalTest(mainBoard, chance) )
        {
            QMessageBox Msgbox;
            Msgbox.setText("Oops!!\nYou Lost Nigga");
            Msgbox.exec();
            return;
        }
    }
}
#endif // MOUSEEVENT_H
