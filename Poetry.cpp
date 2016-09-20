#include <bits/stdc++.h>
using namespace std;
class	Poetry
{
public:
    
    bool isSpaces(string	s)
    {
        for(unsigned	int	index	=	0;	index	<	s.size();	index++	)
            if(s[index]	!=	' ')	return false;
        return	true;
    }
    
    string	rhymeScheme(vector<string> poem)
    {
        string	rhyme	=	"";
        string	charSet	=	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        unsigned	int	symbolLocation	=	0;
        
        for(unsigned	int	i=0;	i	<	poem.size();	i++	)
        {
            //If empty string
            if(poem[i].size()	==	0)
            {
                rhyme	+=	" ";
            }
            else	if(isSpaces(poem[i]))   //if only spaces are present
            {
                rhyme	+=	" "	;
            }
            else    //Finding pattern
            {
                for(unsigned    int j=i-1;  j   >   =   0;  j--)
                {
                    
                }
            }
        }
    }
};
