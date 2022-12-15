#include "grid.h"

class Person
{
  int score;
  battlefield primary_grid;
  battlefield secondary_grid;
  
  // Methods
  public:

  // Constructor
  Person();

  // Display methods
  void showPrimaryGrid();
  void showSecondaryGrid();
  void showGrids();

  // Getters
  char GetPrimaryGrid(int x, int y);
  char GetSecondaryGrid(int x, int y);
  int GetShipCount();
  void ClearPrimaryGrid(char,int,int);

  // Setters
  void SetSecondaryGrid(int h, int x, int y);

  void SinkShip();
  void ClearPrimaryGrid(int, int);
  bool SetPrimaryGrid(char, int, int, int, char);
  
  // Other methods
  bool Hit(Person&,int, int);
  
};

class User:public Person
{
  public:
  void MakeMove(Person&);
};

class Computer:public Person
{
  private:

  // variables to store information about the just previous hit
  int prev_x; 
  int prev_y;
  bool prev_hit;

  public:
  Computer(); // Constructor 
  void MakeMove(Person&);
};