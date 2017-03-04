#ifndef PLAYER2CHECKANDPLAY_H_
# define PLAYER2CHECKANDPLAY_H_
#include "boardDefinition.h"
#include "validPositionCheck.h"

bool possibleCaptureMoves(vvint &mainBoard, vpp &validCaptureMoves, int x1, int y1);

bool checkAndPlay(vvint &boardState, int x1, int x2, int y1, int y2, vpp &validCaptureMoves)
{
    int i,j,ii,jj,temp=abs(x2-x1)+abs(y2-y1);
    bool flag = false;

    if(!validPosition(x1,y1) || !validPosition(x2,y2))  //Given positions should be within the board
        return false;
    if( boardState[x1][y1]<=2 || boardState[x2][y2]!=0) //Old position should have white piece and new position should be empty
        return false;
    if(abs(x1-x2) != abs(y1-y2))    //Only diagonal moves allowed
        return false;
    if( temp!=2 && temp!=4) //Only two types of moves allowed
        return false;
    if( boardState[x1][y1]==3 && x2<=x1)
        return false;
    if( boardState[x1][y1]==3 && x1>=x2)
            return false;

    //Checking for case when white captures an opponent piece
    if(temp==4)
    {
        int x3 = (x1+x2)/2, y3 = (y1+y2)/2;

        if(boardState[x3][y3]<=2 && boardState[x3][y3]!=0)
        {
            if(x2 == boardSz)
                boardState[x2][y2] = 4;
            else
                boardState[x2][y2]=boardState[x1][y1];
            boardState[x1][y1]=boardState[x3][y3]=0;

            if( possibleCaptureMoves(boardState, validCaptureMoves, x2, y2))   //Player needs to move again in case more capture moves possible
                chance = !chance;

            return true;
        }
        return false;
    }

    //Checking when white moves by a single step
    //A check has to be performed for any possible capture move which may make given move illegal
    for(i=1; i<=boardSz; i++)
    {
        for(j=1; j<=boardSz; j++)
        {
            if(boardState[i][j]<=2)    //Ignoring positions unoccupied
                continue;

            if(boardState[i][j]==3) //Unidirectional movement for non-king pieces
            {
                for(jj=-1; jj<=1; jj+=2)
                {
                    if(validPosition(i+1,j+jj) && validPosition(i+2,j+jj*2) && boardState[i+1][j+jj] && boardState[i+2][j+jj*2]==0)
                    {
                        if(boardState[i+1][j+jj]<=2)
                            flag = true;
                    }
                }
            }
            else    //Bidirectional movement for king pieces
            {
                for(ii=-1; ii<=1; ii+=2)
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && boardState[i+ii][j+jj] && boardState[i+ii*2][j+jj*2]==0)
                        {
                            if(boardState[i+ii][j+jj] <=2)
                                flag = true;
                        }
                    }
                }
            }
        }
    }

    if(flag)    //A capture move is possible hence given non-capture move is illegal
        return false;

    if(x2 == boardSz)
        boardState[x2][y2] = 4;
    else
        boardState[x2][y2] = boardState[x1][y1];
    boardState[x1][y1] = 0;

    return true;
}

bool possibleCaptureMoves(vvint &mainBoard, vpp &validCaptureMoves, int x1, int y1)
{
    int j=1,k;

    if(mainBoard[x1][y1] == 4)
        j = -1;

    for( ; j<=1; j+=2)
    {
        for( k=-1; k<=1; k+=2)
        {
            if(validPosition(x1+j,y1+k) && validPosition(x1+2*j,y1+2*k))
            {
                if(mainBoard[x1+j][y1+k] <=2 && mainBoard[x1+j][y1+k] && mainBoard[x1+2*j][y1+2*k] ==0 )
                {
                    validCaptureMoves.push_back(pair<pi,pi>(pi(x1,y1),pi(x1+2*j,y1+2*k)) );
                }
            }
        }
    }

    if(validCaptureMoves.size())
        return true;
    return false;
}

#endif
