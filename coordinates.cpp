#include "coordinates.h"

char colToFile(int col){
  return 'a' + col;
}

int fileToCol(char file){
  return file - 'a';
}

int rowToRank(int row){
  return 8-row;
}

int rankToRow(int rank){
  return 8-rank;
}
