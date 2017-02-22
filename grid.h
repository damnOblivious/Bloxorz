#include "headers.h"

#ifndef GRID
#define GRID

class tiles;

class grid {
private:
  int level;
  int offset;
  int rows,columns;
  float xoffset,zoffset;
  int dx,dz;
  bool updated;
  string brickname;
  vector<string> parsedResult;
  vector<vector <string>> sequence;
  vector<vector <string>> differentGrids[5];
  vector<vector <tiles *>> tileCollection;

public:
  grid(int);
  void setupGrid();
  void changeLevel(int=1);
  vector<vector <tiles*>> * gettileCollection();
  string getTileColor(int,int);
  void getGridDimensions(int *,int *,int *,int *);
  void split(const string &s, char, vector<string> & result);
  void setTile(int,int);
  void removeTile(int,int);
  tiles * getTile(int,int);
  float getxoffset();
  float getzoffset();
  bool isupdated();
  void toggleupdated();
};

#endif
