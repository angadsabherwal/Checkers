#ifndef TILECLASS_H
#define TILECLASS_H

#include <QLabel>
#include <QDebug>
#include <QPainter>

class Tile: public QLabel{
public:
    int tileColor;
    pair<int, int> position;
    int piece;

    Tile(QWidget* pParent = 0, Qt::WindowFlags f = 0): QLabel(pParent, f){};

    Tile(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0): QLabel(text, pParent, f){};


    void mousePressEvent(QMouseEvent *ev);

    void display(){
        this->setAlignment(Qt::AlignCenter);
        if(this->piece != 0){
            if(this->piece == 1)
                this->setPixmap(QPixmap("/home/angad/QtProjects/Checkers/Images/red.png"));
            if(this->piece == 2)
                this->setPixmap(QPixmap("/home/angad/QtProjects/Checkers/Images/redking.png"));
            if(this->piece == 3)
                this->setPixmap(QPixmap("/home/angad/QtProjects/Checkers/Images/white.png"));
            if(this->piece == 4)
                this->setPixmap(QPixmap("/home/angad/QtProjects/Checkers/Images/whiteking.png"));
        }
        else
            this->setPixmap(QPixmap());
    }

    void tileDisplay(){
        if(this->tileColor)
            this->setStyleSheet("QLabel {background-image: url(\"/home/angad/QtProjects/Checkers/Images/marble-piece-white.png\"); border: 1px;}");
         else
            this->setStyleSheet("QLabel {background-image: url(\"/home/angad/QtProjects/Checkers/Images/marble-piece-black.png\"); border: 1px;}");
    }
};

#endif // TILECLASS_H
