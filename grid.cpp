#include "grid.h"
#include "brick1.h"
#include "brick2.h"
#include "switchbrick.h"
#include "fragile.h"
#include "goaltile.h"
//{"NULL", "brown", "brown", "switch remove 2 3", "switch toggle backward 4 7 toggle backward 5 7 toggle backward 6 7 toggle forward 4 9 toggle forward 5 9 toggle forward 6 9 toggle left 4 8 remove 5 8 toggle right 6 8", "brown"},
grid::grid(int level):level(level) {
  offset = 0;
  dx = dz = offset;
  xoffset = -scalingFactor*float(dx);
  zoffset = -scalingFactor*float(dz);
  differentGrids[0] = {
    {"NULL", "switch toggle backward 2 5 toggle forward 2 6", "grey", "grey", "brown", "grey"},

    {"NULL", "brown", "grey", "brown", "fragile", "brown"},

    {"NULL", "brown", "brown", "switch remove 2 3", "switch toggle backward 4 7 toggle backward 5 7 toggle backward 6 7 toggle forward 4 9 toggle forward 5 9 toggle forward 6 9 toggle left 4 8 remove 5 8 toggle right 6 8", "brown"},

    {"NULL", "brown", "won", "brown", "brown", "brown"},

    {"NULL", "grey", "NULL", "NULL", "NULL", "NULL"},

    {"NULL", "grey", "NULL", "NULL", "NULL", "NULL"},

    {"brown", "brown", "grey", "brown", "brown", "brown"},

    {"brown", "brown", "grey", "brown", "grey", "brown"},

    {"brown", "grey", "grey", "brown", "switch", "brown"},

    {"brown", "brown", "brown", "grey", "brown", "brown"},

    {"NULL", "grey", "NULL", "NULL", "NULL", "NULL"},

    {"NULL", "grey", "NULL", "NULL", "NULL", "NULL"},

    {"brown", "grey", "brown", "brown", "brown", "NULL"},

    {"grey", "grey", "won", "brown", "grey", "NULL"},

    {"brown", "brown", "grey", "brown", "grey", "NULL"},
  };

  differentGrids[1] = {
    {"grey","switch toggle forward 2 3","grey","brown","grey"},           //NOTE one row along z-axis so in (a,b) === a->zCord and b->xCord
    {"brown","grey","brown","grey","brown"},
    {"grey","brown","fragile","brown","grey"},
    {"brown","fragile","brown","grey","brown"},
  };

  sequence = differentGrids[level];
  setupGrid();

  vector<string> a = sequence[0];
}

void grid::setupGrid(){
  columns = sequence[0].size();
  rows = sequence.size();
  tileCollection.clear();
  tileCollection.resize(rows, std::vector<tiles *>(columns,NULL));

  for(int z = 0; z < rows; ++z){
    vector<string> temp;
    for(int x = 0; x < columns; ++x){
      setTile(x+1,z+1);
    }
  }
}

void grid::removeTile(int x, int z) {
  if(x < 1 || z < 1 || x > columns || z > rows) {
    return;
  }
  x = x - 1;
  z = z - 1;
  if( sequence[z][x] != "NULL" ) {
    sequence[z][x] = "NULL";
    tileCollection[z][x]->removeTile();
    updated = true;
    std::cout << "removed" << std::endl;
  }
}

bool grid::isupdated() {
  return updated;
}

void grid::toggleupdated() {
  updated = false;
}

void grid::setTile(int x, int z) {
  updated = true;
  if(x < 1 || z < 1 || x > columns || z > rows){
    return;
  }
  x = x - 1;
  z = z - 1;
  split(sequence[z][x],' ',parsedResult);
  brickname = parsedResult[0];
  float xCord = xoffset + float(x*scalingFactor);
  float zCord = zoffset + float(z*scalingFactor);
  if( brickname == "NULL" ) {
    tileCollection[z][x] = NULL;
  }
  else if( brickname == "grey" ) {
    tileCollection[z][x] = new brick1(xCord, 0, zCord);
  }
  else if( brickname == "brown" ) {
    tileCollection[z][x] = new brick2(xCord, 0, zCord ,this);
  }
  else if( brickname == "switch" ) {
    tileCollection[z][x] = new switchbrick(xCord, 0, zCord, parsedResult ,this);
  }
  else if( brickname == "fragile" ) {
    tileCollection[z][x] = new fragile(xCord, 0, zCord, this);
  }
  else if( brickname == "won" ) {
    tileCollection[z][x] = new goaltile(xCord, 0, zCord, this);
  }
}

string grid::getTileColor(int x, int z){
  if(x < 1 || z < 1 || x > columns || z > rows){
    return "NULL";
  }
  return sequence[z-1][x-1];
}

tiles * grid::getTile(int x, int z){
  if(x < 1 || z < 1 || x > columns || z > rows){
    return NULL;
  }
  return tileCollection[z-1][x-1];
}

void grid::changeLevel(int delta){
  level += delta;
  setupGrid();
}

vector<vector <tiles *>>* grid::gettileCollection(){
  return &tileCollection;
}

void grid::getGridDimensions(int * length,int * breadth, int * xoff, int * zoff) {
  *length  = sequence[0].size();
  *breadth = sequence.size();
  *xoff = dx;
  *zoff = dz;
}

float grid::getxoffset() {
  return xoffset;
}
float grid::getzoffset() {
  return zoffset;
}

void grid::split(const string &s, char delim, vector<string> & result) {
    result.clear();
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }
}
