#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

int main()
{
    fstream inFile;
    
    inFile.open("input.txt");
    
    Node start;
    start.weight = 0;
    start.hasParent = false;

    for(int j = 0; j < 3; j++)
    {
      
      for(int i = 0; i < 3; i++)
      {
        
        inFile >> start.nboard.gameArea[j][i];
        
      }
      
      
    }    
    start.nboard.printBoard();
    
    int solution = aStar(start);
    
    cout << "The shortest path cost = " << solution << endl;
    
}