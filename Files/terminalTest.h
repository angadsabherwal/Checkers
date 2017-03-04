#ifndef TERMINALTEST_H_
# define TERMINALTEST_H_
#include "boardDefinition.h"
#include "validPositionCheck.h"

bool terminalTest(vvint &boardState, bool choice)
{
    int i,j,ii,jj;

    for(i=1; i<=boardSz; i++)
    {
        for(j=1; j<=boardSz; j++)
        {
            if(boardState[i][j]==0)    //Ignoring positions unoccupied
                continue;

            if(choice)  //Considering red pieces
            {
                if(boardState[i][j]>=3)
                    continue;

                if(boardState[i][j]==1) //Unidirectional movement for non-king pieces
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i-1,j+jj) && boardState[i-1][j+jj]==0)
                            return false;
                        if(validPosition(i-1,j+jj) && validPosition(i-2,j+jj*2) && boardState[i-1][j+jj]>=3 && boardState[i-2][j+jj*2]==0)
                            return false;
                    }
                }
                else    //Bidirectional movement for king pieces
                {
                    for(ii=-1; ii<=1; ii+=2)
                    {
                        for(jj=-1; jj<=1; jj+=2)
                        {
                            if(validPosition(i+ii,j+jj) && boardState[i+ii][j+jj]==0)
                                return false;
                            if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && boardState[i+ii][j+jj]>=3 && boardState[i+ii*2][j+jj*2]==0)
                                return false;
                        }
                    }
                }
            }
            else    //Considering white pieces
            {
                 if(boardState[i][j]<=2)
                    continue;

                if(boardState[i][j]==3) //Unidirectional movement for non-king pieces
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+1,j+jj) && boardState[i+1][j+jj]==0)
                            return false;
                        if(validPosition(i+1,j+jj) && validPosition(i+2,j+jj*2) && boardState[i+1][j+jj] && boardState[i+1][j+jj]<=2 && boardState[i+2][j+jj*2]==0)
                            return false;
                    }
                }
                else    //Bidirectional movement for king pieces
                {
                    for(ii=-1; ii<=1; ii+=2)
                    {
                        for(jj=-1; jj<=1; jj+=2)
                        {
                            if(validPosition(i+ii,j+jj) && boardState[i+ii][j+jj]==0)
                                return false;
                            if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && boardState[i+ii][j+jj] && boardState[i+ii][j+jj]<=2 && boardState[i+ii*2][j+jj*2]==0)
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

#endif
