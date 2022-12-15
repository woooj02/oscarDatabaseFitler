#include <iostream>

#include "grid.h"
#include "ship.h"

using namespace std;

// Constructor
battlefield::battlefield()
{
  // There are no ships in the battlefield initially.
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
      grid[i][j] = '_';
 
  for(int i=0;i<5;i++)
  {
    ship_rows[i] = -1;
    ship_cols[i] = -1;
  }

  count = 0;
}

// Method to display the battlefield
void battlefield::display()
{
  for(int i=0;i<10;i++)
  {
    for(int j=0;j<10;j++)
      cout<<grid[i][j]<<" ";
      cout<<"\n";
  }
}

void battlefield::set(char c, int row, int col)
{
  grid[row][col] = c;
}

// Get content 
char battlefield::content(int row, int col)
{
  if((row<0)||(col<0)||(row>9)||(col>9))
    return '*';
  return grid[row][col];
}

int battlefield::get_count()
{
  return count;
}

void battlefield::decrCount()
{
  --count;
}


// Place ship
bool battlefield::place_ship(char symbol, int row, int col, int size, char hv)
{
  if(hv=='V') // place vertically
  {
    if(size+row>10)
      return false;

    for(int i=0;i<size;i++)
      if(content(row+i,col)!='_')
        return false;
    
    // Space available. Place the ship in the battlefield
    for(int i=0;i<size;i++)
      grid[row+i][col] = symbol;

    count++;
    return true;
  }
  else
  {
    // Place horizontally
    if(size+col>10)
      return false;

    for(int i=0;i<size;i++)
    if(content(row,col+i)!='_')
      return false;

    // Space available. Place the ship in the battlefield 
    for(int i=0;i<size;i++)
      grid[row][col+i] = symbol;
    
    count++;
    return true;
  }
}