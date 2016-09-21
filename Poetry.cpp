#include <bits/stdc++.h>
using namespace std;
class	Poetry
{
public:

    //return true if only spaces are present in the line
    bool isSpaces(string	s)
    {
        for(unsigned	int	index	=	0;	index	<	s.size();	index++	)
            if(s[index]	!=	' ')	return false;
        return	true;
    }

    //returns true if contains vowels
    bool containsVowel(string    s)
    {
        for(unsigned    int i=0;    i   <   s.size();i++)
        {
            if(s[i] ==  'a' ||  s[i]    ==  'e' ||  s[i] ==  'i' ||  s[i]    ==  'o'    ||  s[i] ==  'u')
                return true;
        }
        return false;
    }

    string	rhymeScheme(vector<string> poem)
    {
        string	rhyme	=	"";
        string	charSet	=	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        unsigned	int	symbolLocation	=	0;

        //loop through each line of the poem
        for(unsigned	int	i=0;	i	<	poem.size();	i++	)
        {
            //Add single space if the line is empty or only spaces are present
            if(poem[i].size()	==	0   ||  isSpaces(poem[i]) )
            {
                rhyme	+=	" "	;
            }
            //try to find the pattern of last word
            else
            {
                bool    pattern_found =   0;

                //If it is first line, there wont be any pattern already available
                //so add a alphabet to rhyme
                if(i    ==     0)
                {
                    rhyme   +=  charSet[symbolLocation++];
                    pattern_found   =   1;
                }

                //For each line x, compare x with all previous line for patterns
                for(int j=i-1;  j   >=   0;  j--)
                {
                    //if previuos lines are not empty or full of spaces
                    if(poem[j].size()   !=  0   &&  (!isSpaces(poem[j]))    )
                    {
                        int x   =   poem[i].size()-1;
                        int y   =   poem[j].size()-1;

                        //gets the location till which the last words match
                        while(x >=    0   &&  y   >=  0   &&  (poem[i][x] ==  poem[j][y])   &&  (poem[i][x] !=  ' ' &&  poem[j][y]  !=  ' '))
                        {
                            x--,y--;
                        }

                        //stored the matched patterns in separate variable
                        string  pattern1(poem[i],(x+1),poem[i].size());
                        string  pattern2(poem[j],(y+1),poem[j].size());

                        if(pattern1.size()  ==  0   &&  pattern2.size() ==  0)
                        {
                            continue;
                        }
                        else
                        {
                            pattern_found =   1;

                            string  start_letter(1,pattern1[0]);

                            string  nonvowel_start(poem[i],(x),poem[i].size());

                            //check if it is a legal word and has a non-vowel starting letter before pattern
                            if(containsVowel(pattern1)   &&  containsVowel(start_letter)  )
                            {
                                if(j    ==  0)
                                {
                                    rhyme   +=  charSet[symbolLocation++];
                                }
                                else
                                    rhyme   +=  rhyme[j];
                            }
                            else
                            {
                                rhyme   +=  charSet[symbolLocation++];
                            }
                        }
                    }
                }
                //when not patterns are found add an alphabet
                if(!pattern_found)  rhyme   +=  charSet[symbolLocation++];

            }

        }
        return  rhyme;
    }


};

int main(int    argc,char   *argv[])
{
    vector<string>  poem;
    poem.push_back("I hope this problem");
    poem.push_back("is a whole lot better than");
    poem.push_back("this stupid haiku");

    Poetry rhyme;
    std::cout << rhyme.rhymeScheme(poem)    <<  '\n';
    return 0;
}
