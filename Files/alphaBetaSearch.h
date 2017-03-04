#ifndef ALPHABETASEARCH_H_
# define ALPHABETASEARCH_H_
#include <unistd.h>
#include "boardDefinition.h"
#include "terminalTest.h"
#include "successors.h"
#include "evaluationFunction.h"

long long int minValue(vvint &boardState, long long int alpha, long long int beta, int depth);
long long int maxValue(vvint &boardState, long long int alpha, long long int beta, int depth);

void timeUsage(float s)
{
    int sec = int(s*1000000);
    usleep(sec);
}

vvint alphaBetaSearch(vvint &boardState)
{
    long long int value = LLONG_MIN, temp;
    vvvint states = successorStates(boardState,true);
    vvint maxState;

    for(int i=0; i<states.size(); i++)
    {
        temp = minValue(states[i], LLONG_MIN, LLONG_MAX, 1);
        if(value <=  temp)
        {
            value = temp;
            maxState = states[i];
        }
    }
    //timeUsage(2);
    return maxState;
}

long long int maxValue(vvint &boardState, long long int alpha, long long int beta, int depth)
{
    if( terminalTest(boardState, true))
        return LLONG_MIN;

    if( depth == maxDepth)
        return evaluationFunction(boardState);

    long long int value = LLONG_MIN;
    vvvint states = successorStates(boardState,true);

    for(int i=0; i<states.size(); i++)
    {
        value = max( value, minValue(states[i], alpha, beta, depth+1));

        if(value >= beta)
            return value;
        alpha = max(alpha, value);
    }
    return value;
}

long long int minValue(vvint &boardState, long long int alpha, long long int beta, int depth)
{
    if( terminalTest(boardState, false))
        return LLONG_MAX;

    if( depth == maxDepth)
        return evaluationFunction(boardState);

    long long int value = LLONG_MAX;
    vvvint states = successorStates(boardState,false);

    for(int i=0; i<states.size(); i++)
    {
        value = min( value, maxValue(states[i], alpha, beta, depth+1));

        if(value <= alpha)
            return value;
        beta = min(beta, value);
    }
    return value;
}

#endif
