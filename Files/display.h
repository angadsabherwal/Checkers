#ifndef DISPLAY_H_
# define DISPLAY_H_
#include<vector>
#include "boardDefinition.h"
#include "Tile/tileclass.h"

void displayGreen(Tile *tmp){
    tmp->setStyleSheet("QLabel {background-color: green;}");
}

void setBorder(QWidget *gameWidget){
    vector<QLabel*> border(4);

    for(int i = 0; i < 4; i++)
        border[i] = new QLabel(gameWidget);

    border[0]->setGeometry(0, 0, 720, 20);

    border[0]->setStyleSheet("QLabel { background-color: rgb(170, 170, 127); color: black;}");

    border[1]->setGeometry(0, 700, 720, 20);

    border[1]->setStyleSheet("QLabel { background-color: rgb(170, 170, 127); color: black;}");

    border[2]->setGeometry(0, 20, 20, 680);

    border[2]->setStyleSheet("QLabel { background-color: rgb(170, 170, 127); color: black;}");

    border[3]->setGeometry(700, 20, 20, 680);

    border[3]->setStyleSheet("QLabel { background-color: rgb(170, 170, 127); color: black;}");
}

void printBoard(QWidget *gameWidget, Tile *tile[9][9], vvint &mainBoard){

    for(int i = 1; i <= boardSz; i++){
        for(int j = 1; j <= boardSz; j++){
            tile[i][j]->piece = mainBoard[i][j];
            tile[i][j]->tileDisplay();
        }
    }

    for(int i = 1; i <= boardSz; i++)
        for(int j = 1; j <= 8; j++)
            tile[i][j]->display();
}

void createBoard(QWidget *gameWidget, Tile *tile[9][9], vvint &mainBoard){
    //Set Border's
    setBorder(gameWidget);
    int ver = 20;

    for(int i = 1; i <= boardSz; i++){
        int hor = 20;
        for(int j = 1; j <= boardSz; j++){
            tile[i][j] = new Tile(gameWidget);
            tile[i][j]->tileColor = (i + j) % 2;
            tile[i][j]->position = make_pair(i, j);
            tile[i][j]->setGeometry(hor, ver, 85, 85);
            hor += 85;
        }
        ver += 85;
    }
    printBoard(gameWidget, tile, mainBoard);
}

#endif
