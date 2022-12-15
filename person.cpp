#include "person.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// Constructor 
Person::Person()
{
  score = 0;
}

Computer::Computer(): Person()
{
  prev_x = 0;
  prev_y = 0;
  prev_hit = false;
}

// Display methods 
void Person::showPrimaryGrid()
{
  primary_grid.display();
}

void Person::showSecondaryGrid()
{
  secondary_grid.display();
}

void Person::showGrids()
{
  cout<<"\nPRIMARY GRID\t\t\t\tSECONDARY GRID\n";
  cout<<"----------------------------------------------\n";
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
      cout<<primary_grid.content(i,j)<<" ";
    
    cout<<"\t\t";

    for(int j=0;j<10;j++)
      cout<<secondary_grid.content(i,j)<<" ";

    cout<<endl;
  }
  cout<<"\n\n";
}

// Getters 

int Person::GetShipCount()
{
  return primary_grid.get_count();
}

char Person::GetPrimaryGrid(int x, int y)
{
  return primary_grid.content(x,y);
}

char Person::GetSecondaryGrid(int x, int y)
{
  return secondary_grid.content(x,y);
}

// Setters 

void Person::SinkShip()
{
  primary_grid.decrCount();
}

void Person::SetSecondaryGrid(int hit, int x, int y)
{
  if(hit)
    secondary_grid.set('O',x,y);
  else
    secondary_grid.set('X',x,y);
}

bool Person::SetPrimaryGrid(char symbol, int row, int col, int size, char hv)
{
  return primary_grid.place_ship(symbol, row, col, size, hv);
}

void Person::ClearPrimaryGrid(char c, int x, int y)
{
  primary_grid.set(c,x,y);
}

// Other methods 

void User::MakeMove(Person &c)
{
  int row, col;
  bool valid = true;
  string input;

  do
  {
    valid = true;
    cout<<"Enter your target location (A1 - J10): ";  
    cin>>input;

    if(input=="Q")
    {
      cout<<"\nCOMPUTER'S GRIDS";
      c.showGrids();
      cout<<"\nQuitting... Bye.";
      exit(0);
    }

    // Check for valid input 
    if((input.length()>3) || (input.length()<2))
    {
      cout<<"\nInvalid input. Re-enter..\n";
      valid = false;
    }
    else
    {
      // Get column from the input. 
      char a = input[0]; 
      a = toupper(a);
      col = (int)(a) - 65;

      // cout<<"col = "<<col;

      // Get row from the input.
      if(input.length()==2)
      {
        char b = input[1];
        row = (int)(b) - 49;
      }
      else
      {
        if((input[1]=='1') && (input[2]=='0'))
          row = 9;
        else
          valid = false;
      }
      
      // cout<<"row = "<<row;

      if((row<0) || (row>9) || (col<0) || (col>9))
        valid = false;
    } 
  }while(!valid);

  bool hit = Hit(c, row, col);
  if(!hit)
    cout<<"Oh no! that was a miss :("<<endl;
  else
    cout<<"Yay! You hit a ship"<<endl;
  SetSecondaryGrid(hit, row, col);
}

void Computer::MakeMove(Person &u)
{
  int x,y;
  
  do{
    if(prev_hit)
    {
      // Choose x and y in the vicinity of prev_x, prev_y 
      int r = rand()%2;
      if(r==0)  x = prev_x+1; else x = prev_x -1;

      r = rand()%2;
      if(r==0)  y = prev_y+1; else y = prev_y -1;

      if((x<0) || (y<0) || (x>9) || (y>9))
      {
        // Choose x and y randomly
        x = rand()%10;
        y = rand()%10;
      }

    }
    else
    {
      // Choose x and y randomly
      x = rand()%10;
      y = rand()%10;
    }
  }while('_'!=GetSecondaryGrid(x,y));

  bool hit = Hit(u,x,y);
  prev_x = x;
  prev_y = y;
  
  cout<<"\nComputer hit you at "<<(char)(x+65)<<y+1<<endl;
  if(!hit)
    cout<<"Fortunately, that was a miss!"<<endl;
  else
  {
    cout<<"Oops! That hurts!"<<endl;
    prev_hit = true;
  }

  SetSecondaryGrid(hit,x,y);
}

bool Person::Hit(Person &p, int x, int y)
{
  // We are trying to hit p's battlefield at (x,y)
  char c = p.GetPrimaryGrid(x,y);
  if(c=='_')  //miss
  {
    p.ClearPrimaryGrid('X',x,y);
    return false;
  }

  else    // hit
  {
    // There's a ship here
    p.ClearPrimaryGrid('O',x,y);

    /* Check if there's an adjacent location with the
    same ship letter. If not, then the ship has sunk */
    if((c==p.GetPrimaryGrid(x+1,y)) || (c==p.GetPrimaryGrid(x-1,y)) || (c==p.GetPrimaryGrid(x,y+1)) || (c==p.GetPrimaryGrid(x,y-1)))
      return true;
    
    // A ship has sunk. 
    p.SinkShip();
    cout<<"Ship "<<c<<" just sunk!";

    return true;
  }
}