#ifndef SUCCESSORS_H_
# define SUCCESSORS_H_
#include "boardDefinition.h"
#include "validPositionCheck.h"

vvvint successorStates(vvint &boardState, bool choice)
{
    int i,j,ii,jj,pos=0,temp,low,high,ctr;
    vvvint states;
    vector<pair<vvint,pi> > tempStates;
    map<vvint, bool> captureStates;
    map<pair<vvint,pi>,bool> boardMap;

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

    //Collecting board states and positions from where capture moves are possible
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
                    if(validPosition(i+ctr,j+jj) && validPosition(i+ctr*2,j+jj*2) && boardState[i+ctr*2][j+jj*2]==0 && boardState[i+ctr][j+jj] )
                    {
                        if(boardState[i+ctr][j+jj]==low || boardState[i+ctr][j+jj]==high)
                            continue;
                        tempStates.push_back(pair<vvint,pi>(boardState,pi(i,j)));
                    }
                }
            }
            else    //Bidirectional movement for king pieces
            {
                for(ii=-1; ii<=1; ii+=2)
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && boardState[i+ii*2][j+jj*2]==0 && boardState[i+ii][j+jj])
                        {
                            if( boardState[i+ii][j+jj]==low || boardState[i+ii][j+jj]==high )
                                continue;
                            tempStates.push_back(pair<vvint,pi>(boardState,pi(i,j)));
                        }
                    }
                }
            }
        }
    }

    //If board states with capture moves available, perform all capture moves to produce final states
    if( tempStates.size() )
    {
        int initsz = tempStates.size();

        while(pos < tempStates.size())
        {
            i = tempStates[pos].second.first;
            j = tempStates[pos].second.second;

            if(tempStates[pos].first[i][j]==low) //Unidirectional movement for non-king pieces
            {
                for(jj=-1; jj<=1; jj+=2)
                {
                    if(validPosition(i+ctr,j+jj) && validPosition(i+ctr*2,j+jj*2) && tempStates[pos].first[i+ctr*2][j+jj*2]==0 && tempStates[pos].first[i+ctr][j+jj] )
                    {
                        if(tempStates[pos].first[i+ctr][j+jj]==low || tempStates[pos].first[i+ctr][j+jj]==high)
                        {
                            if( pos >= initsz && !captureStates[tempStates[pos].first])
                            {
                                captureStates[tempStates[pos].first] = true;
                                states.push_back(tempStates[pos].first);
                            }
                            continue;
                        }

                        tempStates[pos].first[i][j] = 0;
                        temp = tempStates[pos].first[i+ctr][j+jj];
                        tempStates[pos].first[i+ctr][j+jj] = 0;

                        if( (choice && ( i+ctr*2 == 1)) || (!choice && ( i+ctr*2 == boardSz)) )
                            tempStates[pos].first[i+ctr*2][j+jj*2] = high;
                        else
                            tempStates[pos].first[i+ctr*2][j+jj*2] = low;

                        tempStates[pos].second = pi(i+ctr*2, j+jj*2);

                        if(!boardMap[tempStates[pos]])   //For generating unique new states
                        {
                            tempStates.push_back(tempStates[pos]);
                            boardMap[tempStates[pos]]=true;
                        }

                        tempStates[pos].first[i][j] = low;
                        tempStates[pos].first[i+ctr][j+jj] = temp;
                        tempStates[pos].first[i+ctr*2][j+jj*2] = 0;
                        tempStates[pos].second = pi(i,j);
                    }
                    else
                    {
                        if( pos >= initsz && !captureStates[tempStates[pos].first])
                        {
                            captureStates[tempStates[pos].first] = true;
                            states.push_back(tempStates[pos].first);
                        }
                    }
                }
            }
            else    //Bidirectional movement for king pieces
            {
                for(ii=-1; ii<=1; ii+=2)
                {
                    for(jj=-1; jj<=1; jj+=2)
                    {
                        if(validPosition(i+ii,j+jj) && validPosition(i+ii*2,j+jj*2) && tempStates[pos].first[i+ii*2][j+jj*2]==0 && tempStates[pos].first[i+ii][j+jj])
                        {
                            if( tempStates[pos].first[i+ii][j+jj]==low || tempStates[pos].first[i+ii][j+jj]==high )
                            {
                                if( pos >= initsz && !captureStates[tempStates[pos].first])
                                {
                                    captureStates[tempStates[pos].first] = true;
                                    states.push_back(tempStates[pos].first);
                                }
                                continue;
                            }

                            tempStates[pos].first[i][j] = 0;
                            temp = tempStates[pos].first[i+ii][j+jj];
                            tempStates[pos].first[i+ii][j+jj] = 0;
                            tempStates[pos].first[i+ii*2][j+jj*2] = high;
                            tempStates[pos].second = pi(i+ii*2, j+jj*2);

                            if(!boardMap[tempStates[pos]])   //For generating unique new states
                            {
                                tempStates.push_back(tempStates[pos]);
                                boardMap[tempStates[pos]]=true;
                            }

                            tempStates[pos].first[i][j] = high;
                            tempStates[pos].first[i+ii][j+jj] = temp;
                            tempStates[pos].first[i+ii*2][j+jj*2] = 0;
                            tempStates[pos].second = pi(i,j);
                        }
                        else
                        {
                            if( pos >= initsz && !captureStates[tempStates[pos].first])
                            {
                                captureStates[tempStates[pos].first] = true;
                                states.push_back(tempStates[pos].first);
                            }
                        }
                    }
                }
            }
            pos++;
        }
        return states;
    }


    //This part is executed for only those positions in which a capture of opponent piece cannot be done

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
