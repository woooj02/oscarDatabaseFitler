#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>

#include "person.h"
#include "grid.h"
#include "ship.h"

using namespace std;

/* Declare two players - one for the user, and one for the
computer */

User u;
Computer c;

int get_col(char* p)
{
  char sym = p[0];
  return ((int)(sym))-65;
}

int get_row(char* p)
{
  int row = atoi((p+1));
  return row-1;
}

int main() 
{
  // Create the different types of ships
  Ship::create_ships();

  char input_file[256];
  cout << "Enter the input file name: ";
  cin>>input_file;

  ifstream infile(input_file);

  if(!infile)
  {
    cout<<"\nNo such file. Exiting..";
    exit(0);
  }

  // Create the user's battlefiled by reading the CSV
  for(std::string line; getline(infile, line);)
  {
    // Process each line.
    // cout<<line<<endl;
    
    char * cstr = new char [line.length()+1];  
    std::strcpy (cstr, line.c_str());

    char * p = std::strtok (cstr,",");

    char sym = Ship::get_ship_symbol(p);
    int size = Ship::get_ship_size(p);
    if(size==-1)
    {
      // No ship with that name
      cout<<line;
      cout<<"\nNo ship with the specified name. Exiting..";
      exit(0);
    }

    // Now, get the row,col coordinates
    p = std::strtok(NULL,",");
    int r = get_row(p);
    int c = get_col(p);

    // Check if row and col are valid or not. 
    if(!((0<=r) && (r<10) && (0<=c) && (c<10)))
    {
      cout<<line;
      cout<<"\nOut of bounds. Exiting..";
      exit(0);
    }

    // Now, look for whether horizontal or vertical

    p = std::strtok(NULL,",");
    char hv = p[0];

    if((hv!='H') && (hv!='V'))
    {
      cout<<line;
      cout<<"\nExpected H or V at the end. Exiting..";
      exit(0);
    }

    /* Try to place the ship at the specified row,
    col coordinates. */

    if(hv=='H')
    {
      if(size+c>10)
      {
        cout<<line;
        cout<<"\nOut of horizontal bounds. Exiting..";
        exit(0);
      }
    }
    else 
    {
      if(size+r>10)
      {
        cout<<line;
        cout<<"\nOut of vertical bounds. Exiting..";
        exit(0);
      }
    }

    /* If another ship occupies the squares, raise
    error message */
    
    if(!u.SetPrimaryGrid(sym,r,c,size,hv))
    {
      cout<<line;
      cout<<"\nShips overlap. Exiting..";
      exit(0);
    }
    else
    {
      // The ship was placed successfully.

    }
    
  } // end of loop

  // Check whether the user's battlefield has all the 
  // five different varieties of ships 

  if(u.GetShipCount()!=5)
  {
    cout<<"\nMissing ships. Exiting..";
    exit(0);
  }
  
  /* Display the user's battlefield
  cout<<"\nYOUR BATTLEFIELD"<<endl;
  cout<<"------------------------"<<endl;
  u.showPrimaryGrid();  */

  // Now, generate the computer's battlefield randomly.
  srand(time(NULL));
  for(int i=0;i<5;i++)
  {
    // Select a random row and column 
    int row = rand()%10;
    int col = rand()%10;
    // Select horizontal or vertical randomly 
    int horv = rand()%2;
    char hv;

    if(horv==0)
      hv = 'H';
    else
      hv = 'V';

    char sym = Ship::get_symbol_index(i);
    int size = Ship::get_size_index(i);

    // Try to place a ship in the computer's primary grid.
    if(!c.SetPrimaryGrid(sym,row,col,size,hv))
      --i;
  }

  /* Display the computer's battlefield
  cout<<"\n\nCOMPUTER'S BATTLEFIELD"<<endl;
  cout<<"------------------------"<<endl;
  c.showPrimaryGrid();  */

  // Play the game 

  for(int i=0;((u.GetShipCount()>0)&&(c.GetShipCount()>0));++i)
  {
    cout<<"\nGAME ROUND "<<(i+2)/2<<endl;
    if(i%2==0)
    {
      u.showGrids();
      u.MakeMove(c);
    }
    else
      c.MakeMove(u);
  }

  if(u.GetShipCount()>0)
    cout<<"HEY! YOU WIN!"<<endl;
  else 
    cout<<"OOPS YOU LOST!"<<endl;

  cout<<"GAME OVER. EXITING...";
  return 0;

} // end of main()