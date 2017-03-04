#ifndef SUCCESSORS_H_
# define SUCCESSORS_H_
#include "boardDefinition.h"
#include "validPositionCheck.h"

vvvint successorStates(vvint &boardState, bool choice)
{

    int i,j,ii,jj,pos=0,temp,low,high,ctr;
    vvvint states,tempStates;
    map<vvint, bool> boardMap;

    if(choice)
    {
        low = 1;
        ctr = -1;
    }
    else
    {
        low = 3;
        ctr = 1;
    }
    high = low+1;

    //Perform capture moves if possible

    tempStates.push_back(boardState);

    while(pos < tempStates.size())
    {
        bool flag = false;

        for(i=1; i<=boardSz; i++)
        {
            for(j=1; j<=boardSz; j++)
            {
                if( !(tempStates[pos][i][j]==low || tempStates[pos][i][j]==high) )    //Ignoring positions occupied by oponent or unoccupied
                    continue;

                if(tempStates[pos][i][j]==low) //Unidirectional movement for non-king pieces
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+ctr,j+jj) && validPosition(i+ctr*2,j+jj*2) && tempStates[pos][i+ctr*2][j+jj*2]==0 && tempStates[pos][i+ctr][j+jj] )
                        {
                            if(tempStates[pos][i+ctr][j+jj]==low || tempStates[pos][i+ctr][j+jj]==high)
                                continue;

                            tempStates[pos][i][j] = 0;
                            temp = tempStates[pos][i+ctr][j+jj];
                            tempStates[pos][i+ctr][j+jj] = 0;

                            if( (choice && ( i+ctr*2 == 1)) || (!choice && ( i+ctr*2 == boardSz)) )
                                tempStates[pos][i+ctr*2][j+jj*2] = high;
                            else
                                tempStates[pos][i+ctr*2][j+jj*2] = low;

                            if(!boardMap[tempStates[pos]])   //For generating unique new states
                            {
                                flag=true;
                                tempStates.push_back(tempStates[pos]);
                                boardMap[tempStates[pos]]=true;
                            }

                            tempStates[pos][i][j] = low;
                            tempStates[pos][i+ctr][j+jj] = temp;
                            tempStates[pos][i+ctr*2][j+jj*2] = 0;
                        }
                    }
                }
                else    //Bidirectional movement for king pieces
                {
                    for(ii=-1; ii<=1; ii+=2)
                    {
                        for(jj=-1; jj<=1; jj+=2)
                        {
                            if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && tempStates[pos][i+ii*2][j+jj*2]==0 && tempStates[pos][i+ii][j+jj])
                            {
                                if( tempStates[pos][i+ii][j+jj]==low || tempStates[pos][i+ii][j+jj]==high )
                                    continue;

                                tempStates[pos][i][j] = 0;
                                temp = tempStates[pos][i+ii][j+jj];
                                tempStates[pos][i+ii][j+jj] = 0;
                                tempStates[pos][i+ii*2][j+jj*2] = high;

                                if(!boardMap[tempStates[pos]])   //For generating unique new states
                                {
                                    flag=true;
                                    tempStates.push_back(tempStates[pos]);
                                    boardMap[tempStates[pos]]=true;
                                }

                                tempStates[pos][i][j] = high;
                                tempStates[pos][i+ii][j+jj] = temp;
                                tempStates[pos][i+ii*2][j+jj*2] = 0;
                            }
                        }
                    }
                }
            }
        }

        if(!flag)   //No capture movements possible for the given board state
            states.push_back(tempStates[pos]);
        pos++;
    }

    if(!(states.size()==1 && states[0]==boardState) )
        return states;

    //This part is executed for only those positions in which a capture of opponent piece cannot be done

    states.clear();
    for(i=1; i<=boardSz; i++)
    {
        for(j=1; j<=boardSz; j++)
        {
            if( !(boardState[i][j]==low || boardState[i][j]==high) )    //Ignoring positions occupied by oponent or unoccupied
                continue;

            if(boardState[i][j]==low) //Unidirectional movement for non-king pieces
            {
                for(jj=-1; jj<=1; jj+=2)
                {
                    if(validPosition(i+ctr,j+jj) && boardState[i+ctr][j+jj]==0)
                    {
                        boardState[i][j] = 0;

                        if( (choice && (i+ctr == 1)) || (!choice && (i+ctr == boardSz)) )
                            boardState[i+ctr][j+jj] = high;
                        else
                            boardState[i+ctr][j+jj] = low;

                        states.push_back(boardState);
                        boardState[i][j] = low;
                        boardState[i+ctr][j+jj] = 0;
                    }
                }
            }
            else    //Bidirectional movement for king pieces
            {
                for(ii=-1; ii<=1; ii+=2)
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+ii,j+jj) && boardState[i+ii][j+jj]==0)
                        {
                            boardState[i][j] = 0;
                            boardState[i+ii][j+jj] = high;
                            states.push_back(boardState);
                            boardState[i][j] = high;
                            boardState[i+ii][j+jj] = 0;
                        }
                    }
                }
            }
        }
    }
    return states;
}

#endif
