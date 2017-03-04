#ifndef INITIALISEBOARD_H_
# define INITIALISEBOARD_H_
#include "boardDefinition.h"
#include<bits/stdc++.h>

void initialiseBoard( vvint &mainBoard)
{
    int i,j;
    bool flag;

    flag = true;
    for(i=boardSz; i> (1+boardSz/2); i-- )  //Initialising red pieces
    {
        flag = !flag;
        for(j=1; j<=boardSz; j++)
        {
            if(flag)
                mainBoard[i][j] = 1;
            flag = !flag;
        }
    }

    flag = false;
    for(i=1; i<boardSz/2; i++)  //Initialising white pieces
    {
        flag = !flag;
        for(j=1; j<=boardSz; j++)
        {
            if(flag)
                mainBoard[i][j] = 3;
            flag = !flag;
        }
    }
}


void testInitialiseBoard(vvint &mainBoard)
{
    vvint tmp = {
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,3,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0},
                };
    mainBoard = tmp;
}

#endif
