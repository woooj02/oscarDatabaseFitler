#include "ship.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// Create the ships 
Ship ships[5];

Ship::Ship()
{

}

Ship::Ship(string a, int b, char c)
{
  name.assign(a);
  size = b;
  symbol = c;
}

void Ship::create_ships()
{
  ships[0] = Ship("Carrier",5,'C');
  ships[1] = Ship("Battleship",4,'B');
  ships[2] = Ship("Cruiser",3,'$');
  ships[3] = Ship("Submarine",3,'S');
  ships[4] = Ship("Destroyer",2,'D');
}

std::string Ship::get_name()
{
  return name;
}

int Ship::get_size()
{
  return size;
}

int Ship::get_size_index(int index)
{
  return ships[index].get_size();
}

char Ship::get_symbol()
{
  return symbol;
}

char Ship::get_symbol_index(int index)
{
  return ships[index].get_symbol();
}

int Ship::get_index_symbol(char sym)
{
  for (int i=0;i<5;i++)
    if(sym==ships[i].get_symbol())
      return i;
  return -1;
}

int Ship::get_ship_size(char p[100])
{
  for(int i=0;i<5;i++)
  {
    string s = ships[i].get_name();
    string t = string(p);
    if(s.compare(t)==0)
      return ships[i].get_size();
  }
  return -1;
}

char Ship::get_ship_symbol(char p[100])
{
  for(int i=0;i<5;i++)
  {
    string s = ships[i].get_name();
    string t = string(p);
    if(s.compare(t)==0)
      return ships[i].get_symbol();
  }
  return -1;
}
