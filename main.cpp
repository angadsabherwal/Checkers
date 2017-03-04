#include <QApplication>
#include <QMouseEvent>
#include <vector>
#include <QLabel>
#include <cstring>
#include <utility>
#include <map>
#include <QMessageBox>

using namespace std;

#include "mainwindow.h"
#include "Files/boardDefinition.h"
#include "Files/display.h"
#include "Files/initialiseBoard.h"
#include "Tile/tileclass.h"
#include "Tile/mouseevent.h"

int countClicks = 0;

Tile *tile[9][9];
vvint mainBoard(boardSz+1, vector<int>(boardSz+1,0));

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;

    initialiseBoard(mainBoard);
    createBoard(gameWidget, tile, mainBoard);

    //Forcing first move by computer
    mainBoard = alphaBetaSearch(mainBoard);
    printBoard(gameWidget, tile, mainBoard);
    chance = false;

    window.show();

    return a.exec();
}
