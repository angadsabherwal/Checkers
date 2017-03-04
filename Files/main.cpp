#include<bits/stdc++.h>
#include "printBoard.cpp"
#include "initialiseBoard.cpp"
#include "player2CheckAndPlay.cpp"
#include "alphaBetaSearch.cpp"

using namespace std;

vvint mainBoard(boardSz+1, vector<int>(boardSz+1,0));

int main()
{
    int x1,x2,y1,y2;

    initialiseBoard(mainBoard);
    printBoard(mainBoard);
    cout<<endl<<endl;

    chance=!chance;
    while(1)
    {
        if(chance)  //Red's Turn
        {
            if(terminalTest(mainBoard,chance))
                break;
            cout<<"Computer's Turn:\n";

            mainBoard = alphaBetaSearch(mainBoard);
            chance = !chance;
        }
        else    //White's Turn
        {
            if(terminalTest(mainBoard,chance))
                break;

            cout<<"Your Turn:\n";
            cout<<"Enter position of piece to be moved: ";
            cin>>x1>>y1;
            cout<<"Enter new position: ";
            cin>>x2>>y2;

            if(!checkAndPlay(mainBoard,x1,x2,y1,y2))
            {
                cout<<"Invalid Move!!"<<endl<<endl;
                continue;
            }
            chance = !chance;
        }

        printBoard(mainBoard);
        cout<<endl<<endl;
    }

    if(chance)
        cout<<endl<<"White Wins"<<endl;
    else
        cout<<endl<<"Red Wins"<<endl;

    return 0;
}
