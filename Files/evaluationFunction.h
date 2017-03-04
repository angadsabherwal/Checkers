#ifndef EVALUATIONFUNCTION_H_
# define EVALUATIONFUNCTION_H_
#include "boardDefinition.h"

long long int evaluationFunction2(vvint &boardState)
{
    long long int value=0, i, j;

    for( i=1; i<=boardSz; i++)
    {
        for( j=1; j<=boardSz; j++)
        {
            if(boardState[i][j] == 1)
                value += 1;
            if(boardState[i][j] == 2)
                value += 2;
            if(boardState[i][j] == 3)
                value -= 1;
            if(boardState[i][j] == 4)
                value -= 2;
        }
    }
    return value;
}

long long int evaluationFunction(vvint &boardState)
{
    long long int value=0,value1=0, value2=0, value3=9, i, j;

    for( i=1; i<=boardSz; i++)
    {
        for( j=1; j<=boardSz; j++)
        {
            if(boardState[i][j] == 1)
            {
                value1 += 1;
                if(i == boardSz-1 || i == boardSz-2)
                {
                    value2 += 1;
                }
                if(j==1 || j==boardSz)
                    value3 += 1;
            }
            if(boardState[i][j] == 3)
            {
                value1 -= 1;
                if(i == 2 || i == 3)
                {
                    value2 -= 1;
                }
                if(j==1 || j==boardSz)
                    value3 -= 1;
            }
            if(boardState[i][j] == 2)
            {
                value1 += 2;
                if(j==1 || j==boardSz)
                    value3 += 1;
            }
            if(boardState[i][j] == 4)
            {
                value1 -= 2;
                if(j==1 || j==boardSz)
                    value3 -= 1;
            }
        }
    }

    value = value1;
    value = value*10 + value1;
    value = value*10 + value2;
    value = value*10 + value3;

    return value;
}

#endif
