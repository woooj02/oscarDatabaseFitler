#include <string>
#include <cstring>
using namespace std;
class Ship
{
  string name;
  int size;
  char symbol;

  public:
  
  // Constructor
  Ship();
  Ship(string, int, char);
  
  string get_name();
  int get_size();
  char get_symbol();

  static char get_symbol(int);

  // Static functions
  static void create_ships();
  static int get_ship_size(char*);
  static char get_ship_symbol(char*);
  static char get_symbol_index(int);
  static int get_size_index(int);
  static int get_index_symbol(char);
};