#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include "Files/boardDefinition.h"
//#include "Files/display.h"
//#include "Files/initialiseBoard.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //virtual ~MainWindow();

    QStatusBar *sBar;

    void setStatusBar(QString *string);

    protected:
        void contextMenuEvent(QContextMenuEvent *event);
    private slots:
        void newGame();
        void about();

        void gameResult();

    private:
        //Ui::MainWindow *ui;
        void createActions();
        void createMenus();

        QWidget *centralWidget;
        QMenu *fileMenu;
        QMenu *helpMenu;
        QActionGroup *alignmentGroup;
        QAction *newAct;
        QAction *aboutAct;

        QAction *gameResultAct;
};

#endif // MAINWINDOW_H
