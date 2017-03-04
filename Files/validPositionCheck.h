#ifndef VALIPOSITIONCHECK_H_
# define VALIPOSITIONCHECK_H_

bool validPosition(int i, int j)
{
    if(i>=1 && i<=boardSz && j>=1 && j<=boardSz)
        return true;
    return false;
}
#endif
