#include <QtGui>
#include <QMainWindow>
#include <QWidget>
#include <QStatusBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QMenuBar>

using namespace std;

#include "mainwindow.h"

QWidget *gameWidget;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    gameWidget = new QWidget();
    gameWidget->setAttribute(Qt::WA_Hover);
    gameWidget->setGeometry(0, 0, 720, 720);

    centralWidget = gameWidget;
    setCentralWidget(centralWidget);

    createActions();
    createMenus();

    setWindowTitle(tr("Checkers"));
    this->setFixedSize(720, 720);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.exec(event->globalPos());
}

void MainWindow::newGame() {

//    initialiseBoard(mainBoard);
//    createBoard(gameWidget, tile, mainBoard);

//    //Forcing first move by computer
//    mainBoard = alphaBetaSearch(mainBoard);
//    printBoard(gameWidget, tile, mainBoard);
//    chance = false;

}

void MainWindow::about() {
    QMessageBox::about(this, tr("Checkers"),
            tr("<table>"
                    "<tr><td>Checkers</td></tr> "
                    "<tr><td>Created by Angad Sabherwal</td></tr>"
               "</table>"));
}

void MainWindow::gameResult()
{

}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("New Game"));
    QObject::connect(newAct, SIGNAL(triggered()), this, SLOT(newGame()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

//    gameResultAct = new QAction();
//    QObject::connect(gameResultAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&Game"));
    fileMenu->addAction(newAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::setStatusBar (QString *string){
    statusBar()->showMessage(*string);
}
