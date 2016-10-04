#include    <iostream>
#include    <vector>

#define MAX_COL    21
#define MAX_LEN    101

using namespace std;

class MasterMind
{
    public:
        int colCount[MAX_COL];
        int cols,len,Sum;
        int lastCheck   =   0;

        vector<int> init(int    k,int   l)
        {
            for(int i=0;i<MAX_COL;i++)
            {
                colCount[i] =   0;
            }

            cols    =   k;
            len     =   l;

            return  vector<int>(len,lastCheck++);
        }

        vector<int> nextGuess(vector<int> prev,vector<int>  results)
        {

            if(Sum  !=  len)
            {
                colCount[lastCheck-1]   =   results[0];

                Sum =   0;
                for(int i=0;    i<MAX_COL;  i++)
                {
                    Sum +=  colCount[i];
                }
            }
            else    if(Sum  ==  len)
            {
                vector<int> next;

                for(int i=0;i<MAX_COL;i++)
                {
                    if(colCount[i]  !=  0)
                    {
                        for(int j=0;    j<colCount[i];  j++)
                        {
                            next.push_back(i);
                        }
                    }
                }

                return  next;
            }

            return  vector<int>(len,lastCheck++);
        }
};

void    Print(vector<int>   a)
{
    for(auto &x:a)
    {
        cout    <<  x   << " ";
    }
}

int main()
{
    MasterMind  myguess;
    int l   =   5;
    vector<int> used(l,0);
    vector<int> code{4,3,0,1,2};
    vector<int> results(2,0);
    vector<int> guess   =   myguess.init(l,l);

    for(int i=0;i<30;i++)
    {
        Print(guess);

        for(int i=0;    i<l  ;i++)
        {
            used[i] =   0;
        }
        results[0]  =   results[1]  =   0;

        for(int i = 0;i<l;i++)
        {
            if(guess[i] == code[i])
            {
                results[0]++;
            }
            else
            {
                for(int j = 0;  j<l;j++)
                {
                    if(guess[i] == code[j] && guess[j] != code[j] && !used[j])
                    {
                        used[j] = true;
                        results[1]++;
                        break;
                    }
                }
            }
        }

        cout    <<" || "    <<  results[0]  << " "  <<  results[1]  <<  '\n';
        cin.get();
        guess   =   myguess.nextGuess(guess,results);
    }

    return 0;
}
