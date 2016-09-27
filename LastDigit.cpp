#include <iostream>
using namespace std;
 
class LastDigit
{
 
public:
    long    long    getDigitsSum(long   long    n)
    {
        long    long    Sum =   n;
        while(n)
        {
            Sum +=  n/10;
            n/=10;
        }
        return  Sum;
    }
    long long findX(long long S)
    {
        long    long    tmp =   0;
        for(long    long    i=S;    i>=1;   i--)
        {
            tmp    =    getDigitsSum(i);
            if(tmp  ==  S)
                return  i;
        }
        return -1;
    }
 
};
