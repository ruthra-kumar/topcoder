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
        int     Mode    =   0;                  //  0   -   GuessColor  ,   1   -   GuessPattern,   2   -   Verify
        int     cols,len,colorCheck   =   0,totalHits   =   0;
        int     colCount[MAX_COL];
        short   Score[MAX_LEN];

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
            Mode    =   0;
            
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
        
        vector<int> guessPattern(vector<int> prev,vector<int>  results)
        {
            vector<int> next;
            
            for(int i=0;    i   <   MAX_COL;    i++)
            {
                for(int j   =   0;  j   <   colCount[i];j++)
                {
                    next.push_back(i);                    
                }
            }
            Print(next);
            return  next;
        }
        
        vector<int> guessColor(vector<int> prev,vector<int>  results)
        {
            cout    <<  totalHits <<  '\n';
            if(totalHits    ==  len)
            {
                Mode    =   1;
                return  guessPattern(prev, results);
            }
            totalHits   +=   results[0];
            return  vector<int>(len,colorCheck++);
        }
        
        vector<int> nextGuess(vector<int> prev,vector<int>  results)
        {
            vector<int> next(cols,0);
            guessColor();
            switch(Mode)
            {
                case    0:
                //next    =   guessColor(prev,results);
                //  Print(next);
                break;
                
                case    1:
                //next    =   guessPattern(prev,results);
                break;
                
                case    2:
                //next    =   Verify(prev,results);
                break;
                
                default:break;
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
