//Problem is of Simulation type and Hard Category

#include <iostream>
using namespace std;

class   BuffingPixie
{
  public:
  int fastestVictory(int HP, int normalAttack, int buffedAttack)
  {
      int   total_attacks   =   0;
      bool  Focused =   0;
      while(HP  >   0)
      {
          //if enemy can be defeated in single normal attack  or
          //if previous step was focues                       or
          //if normal attack for two consecutive steps is same as focued attack 
          //the if block executes
          if(normalAttack >=    HP  ||  Focused ||  (buffedAttack    <=  normalAttack*2)    )
          {
              
              if(Focused)
                HP  -=  buffedAttack;
              else
                HP  -=  normalAttack;
                
            Focused =   0;
          }
          else
            Focused =   1;
        
        total_attacks++;
      }
      return    total_attacks;
  }
};
