#ifndef GRID_H
#define GRID_H

class battlefield
{
  // The entire grid
  char grid[10][10];

  // Where are the ships located ?
  int ship_rows[5];
  int ship_cols[5];

  // How many ships ?
  int count;

  public:
    // Constructor 
    battlefield();
    // Method to display the battlefield
    void display();
    // Get content 
    char content(int row, int col);
    // Place a ship 
    bool place_ship(char symbol, int row, int col, int size, char hv);
    // Get count 
    int get_count();

    //Setters 
    void decrCount();
    void set(char c, int row, int col);
};

#endif