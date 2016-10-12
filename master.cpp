#include    <iostream>
#include    <vector>

#define MAX_COL    21
#define MAX_LEN    101

using namespace std;

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
        int     colCount[MAX_COL];
        int     cols,len,Sum,x,y,lastCheck   =   0;
        bool    First   =   1;
        short   Score[MAX_LEN];
        vector<int> prev_score;

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

            Sum     =   0;

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
                if(First)
                {
                    //if color count found
                    x   =   0;
                    y   =   x+1;

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
                    First   =   0;
                    prev_score  =   prev;
                    return  next;
                }
                else
                {
                    //Print score
                    /*
                    for(int i=0;    i<prev.size();  i++)
                    {
                        cout<<Score[i]  << " ";
                    }
                    */
                    //Start Guessing
                    int hit_change  =   (prev[0]    -   prev_score[0]);

                    if(hit_change   ==  2   ||  hit_change  ==  -2)
                    {
                        Score[x]    =   Score[y]    =   2;
                    }


                    while(Score[y]  ==  2   &&  y   <   prev.size())  y++;



                    /*
                    y++;
                    if( !(y    <   prev.size()) )
                    {
                        x++;
                        if(!(x  <   prev.size()) )
                        {
                            x   =   0;
                        }
                        y   =   0;
                    }
                    */

                    //swap
                    int tmp =   prev[x];
                    prev[x] =   prev[y];
                    prev[y] =   tmp;
                    cout    <<  x   <<" "   <<  y   <<'\t';
                    return  prev;
                }

            }

            return  vector<int>(len,lastCheck++);
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
        //cin.get();
        guess   =   myguess.nextGuess(guess,results);
    }

    return 0;
}
