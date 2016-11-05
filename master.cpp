
#include    <iostream>
#include    <vector>
#include    <cstdlib>

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

void PrintScore(int l)
{
    for(int i=0;    i   <   l;    i++)
    {
        cout    <<  Score[i]    << " ";
    }
    cout    <<  '\n';
}

void    Print(vector<int>   a)
{
    for(auto &x:a)
    {
        cout    <<  x   << " ";
    }
    cout    <<  '\n';
}


class MasterMind
{
    public:
        bool    firstGuess  =   0;
        Mode state;
        int     x,y,Twoloc,cols,len,verifyHitChange,colorCheck   =   0,totalHits   =   0;
        vector<int> base,lastScore;

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

            x   =   y   =   Twoloc  =   verifyHitChange =   0;
            totalHits =   0;
            state   =   GUESS_COLOR;

            cols    =   k;
            len     =   l;

            return  vector<int>(len,colorCheck++);
        }

        void moveX()
        {
            do
            {
                x++;
                if(x    >=  base.size())
                {
                    x   =   0;
                }
            }while(Score[x] ==  2   ||  (x  ==  y));
        }

        void moveY()
        {
            do
            {
                y++;
                if(y    >=  base.size())
                {
                    y   =   0;
                }
            }while(Score[y] ==  2   ||  (x  ==  y));
        }

        void    nextPos()
        {
            do
            {
                y++;
                if(y    >=  base.size())
                {
                    moveX();
                    y   =   0;
                }
            }while(Score[y] ==  2   ||  (x  ==  y));
        }

        bool Score2()
        {
            for(int i=0;i<len;i++)
            {
                if(Score[i] ==  2)
                    return  true;
            }
            return false;
        }

        int getScore2()
        {
            int loc =   0;
            for(int i=0;i<len;i++)
            {
                if(Score[i] ==  2)
                {
                    loc =   i;
                    break;
                }
            }
            return loc;
        }

        vector<int> Verify(vector<int> prev,vector<int>  results)
        {
            vector<int> nxt;

            //cancel state
            state   =   GUESS_PATTERN;

            int hit_cng =   (results[0]  -   lastScore[0]);

            if(hit_cng  ==  -1)
            {
                Score[y]    =   2;
            }
            else    if(hit_cng  ==  -2)
            {
                Score[x]    =   2;
                moveX();
            }

            nextPos();

            //swap
            nxt =   base;
            int tmp =   nxt[x];
            nxt[x]  =   nxt[y];
            nxt[y]  =   tmp;

            return  nxt;
        }

        vector<int> guessPattern(vector<int> pr,vector<int>  rs)
        {
            vector<int> nxt;

            //on First guess
            if(firstGuess)
            {
                //Clear firstGuess
                firstGuess  =   false;

                //Save score
                lastScore   =   rs;

                nextPos();

                //Swap
                nxt =   base;
                int tmp =   nxt[x];
                nxt[x]  =   nxt[y];
                nxt[y]  =   tmp;

            }
            else
            {
                int hit_change  =   (rs[0]   -   lastScore[0]);

                if(hit_change   ==  2   ||  hit_change  ==  -2)
                {
                    if(hit_change   ==  2)
                    {
                        //Record score
                        Score[x]    =   Score[y]    =   2;

                        //record the base state
                        base    =   pr;
                        lastScore   =   rs;

                        //move x now
                        moveX();
                    }
                    else
                    {
                        //Record score
                        Score[x]    =   Score[y]    =   2;

                        //move x now
                        moveX();
                    }
                }
                else    if(hit_change  ==  -1   ||  hit_change  ==  1)
                {
                    if(Score2())
                    {
                        if(hit_change   ==  -1)
                        {
                            //Set state
                            state   =   VERIFY;

                            int Twoloc =   getScore2();

                            //Always swap score 2 with x
                            nxt =   base;
                            int tmp =   nxt[x];
                            nxt[x]  =   nxt[Twoloc];
                            nxt[Twoloc] =   tmp;

                            //now return
                            return  nxt;
                        }
                        else
                        {
                            //set base
                            base        =   pr;
                            lastScore   =   rs;

                            //set state
                            state       =   VERIFY;

                            int Twoloc  =   getScore2();

                            nxt =   base;
                            int tmp =   nxt[x];
                            nxt[x]  =   nxt[Twoloc];
                            nxt[Twoloc] =   tmp;

                            //now return
                            return  nxt;
                        }
                    }
                    else
                    {
                        if(hit_change   ==  1)
                        {
                            //make it base
                            base    =   pr;
                            lastScore   =   rs;
                        }
                    }
                }

                nextPos();

                //Swap
                nxt =   base;
                int tmp =   nxt[x];
                nxt[x]  =   nxt[y];
                nxt[y]  =   tmp;
            }

            return  nxt;
        }

        vector<int> guessColor(vector<int> pre,vector<int>  res)
        {
            if(totalHits    ==  len)
            {
                state   =   GUESS_PATTERN;
                for(int i=0;    i   <   MAX_COL ;i++)
                {
                    for(int j=0;    j   <   colCount[i];   j++)
                    {
                        base.push_back(i);
                    }
                }

                state   =   GUESS_PATTERN;
                firstGuess  =   true;
                return  base;
            }
            colCount[colorCheck-1]  =   res[0];
            totalHits   +=   res[0];
            return  vector<int>(len,colorCheck++);
        }

        vector<int> nextGuess(vector<int> prev,vector<int>  results)
        {
            if(results[0]   ==  len)    exit(0);
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
    //vector<int> code{11,9,3,11,5,2,1,5,5,11,11,8,7,9,11,7,7,7,7,7,11,6,5,11,7,2,9,9,12,3,9,1,5,9,2,3,3,3,5,9,0,12,6,7,9,6,9,5,11,7,6,11,3,9,7,9,3,3,7,4,5,3,6,2,7,11,6,12,4,3,4,12,9,5,3,3,5,7,8,8,2,7,11,7,4,12,5,0,1,2,6};
    vector<int> code{4,3,3,3,0};

    int l   =  code.size();

    MasterMind  myguess;
    vector<int> used(l,0);
    vector<int> results(2,0);
    vector<int> guess   =   myguess.init(l,l);

    for(int i=0;i<3000;i++)
    {

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

        //cin.get();
        cout    << "Guess: "    <<  i   <<  '\t';
        guess   =   myguess.nextGuess(guess,results);
        Print(guess);
    }

    return 0;
}
