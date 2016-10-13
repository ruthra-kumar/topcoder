#include    <iostream>
#include    <vector>

#define MAX_COL    21
#define MAX_LEN    101

using namespace std;

int colCount[MAX_COL];
int Score[MAX_LEN];

enum    Mode
{
    GUESS_COLOR,
    GUESS_PATTERN,
    VERIFY
};

void    Print(vector<int>   a)
{
    for(auto &x:a)
    {
        cout    <<  x   << " ";
    }
}


class MasterMind
{
    public:
        Mode state;
        int     cols,len,colorCheck   =   0,totalHits   =   0;
        vector<int> base;

        vector<int> init(int    k,int   l)
        {
            for(int i=0;i<MAX_COL;i++)
            {
                colCount[i] =   0;
            }
            for(int i=0;i<MAX_LEN;i++)
            {
                Score[i]    =   0;
            }

            totalHits =   0;
            state   =   GUESS_COLOR;

            cols    =   k;
            len     =   l;

            return  vector<int>(len,colorCheck++);
        }

        /*
        void    next_pos(vector<int>    prev)
        {
            do
            {
                y++;
                if(y    >=  prev.size())
                {
                    do
                    {
                        x++;
                        if(x    >=  prev.size())
                        {
                            x   =   0;
                        }
                    }while(Score[x] ==  2);
                    y   =   0;
                }
            }while(Score[y] ==  2);

        }
        */

        vector<int> Verify(vector<int> prev,vector<int>  results)
        {
            return  prev;
        }

        vector<int> guessPattern(vector<int> pr,vector<int>  rs)
        {
            vector<int> next(0,len);

            return  next;
        }

        vector<int> guessColor(vector<int> pre,vector<int>  res)
        {
            cout    <<  totalHits   <<  "   "   <<  len <<  '\n';
            if(totalHits    ==  len)
            {
                state   =   GUESS_PATTERN;
                cout    <<  "Generating base"   <<  '\n';
                cout    <<  colCount[0] <<  '\n' ;
                cout    <<  "Base Generated"    <<  '\n';

                return  guessPattern(pre, res);
            }
            totalHits   +=   res[0];
            return  vector<int>(len,colorCheck++);
        }

        vector<int> nextGuess(vector<int> prev,vector<int>  results)
        {
            vector<int> next(cols,0);

            if(state    ==  GUESS_COLOR)
            {
                next    =   guessColor(prev,results);
            }
            else    if(state ==  GUESS_PATTERN)
            {
                next    =   guessPattern(prev,results);
            }
            else    if(state    ==  VERIFY)
            {
                next    =   Verify(prev,results);
            }

            return  next;
        }
};

int main()
{
    vector<int> code{4,3,0,1,2,5,9,7,8,6};

    int l   =  code.size();

    MasterMind  myguess;
    vector<int> used(l,0);
    vector<int> results(2,0);
    vector<int> guess   =   myguess.init(l,l);

    for(int i=0;i<40;i++)
    {
        //Print(guess);

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

        //cout    <<" || "    <<  results[0]  << " "  <<  results[1]  <<  '\n';
        //cin.get();
        guess   =   myguess.nextGuess(guess,results);
    }

    return 0;
}
