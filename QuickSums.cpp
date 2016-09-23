//Problem is of Dynamic Programming type and Hard Category
#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class QuickSums
{
  public:
    
    int minSums(string  numbers,int num)
    {
        queue<vector<string> >   buffer;
        vector<string>  start;
        start.push_back(numbers);
        buffer.push(start);
        
        while(!buffer.empty())
        {
            vector<string>  cur =   buffer.front();
            
            //Check if sum is same as required
            long Sum =   0;
            for(unsigned    int i=0;    i<cur.size();   i++)
            {
                if(cur[i].size()    !=  0)
                    Sum +=  stol(cur[i]);
            }
            //if found return no of numbers-1 which gives + operator count
            if(Sum  ==  num)    return  (cur.size()-1);
            
            //Make a copy of last number
            string  last_string =   cur.back();
            vector<string>  cur_copy(cur.begin(),cur.end()-1);
            
            //splitting last number to two numbers at various index positions
            // and add it to buffer
            for(unsigned    int i=0;    i<last_string.size(); i++)
            {
                vector<string>  next(cur_copy);
                
                next.push_back(string(last_string.begin(),last_string.begin()+(i+1)));
                next.push_back(string(last_string.begin()+(i+1),last_string.end()));
                
                buffer.push(next);
                
            }
            
            buffer.pop();
        }
        
        return  -1;
    }
};
