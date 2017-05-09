#include <iostream>
#include <vector>

using namespace std;
//Initalized and assigns the values for the goal array to be compared later
int goalArray[3][3] = {{1,2,3}, {8,0,4}, {7,6,5}};

class coordinate
{
  public:
    int x;
    int y;
};

class board
{
  public:
    int gameArea[3][3];
    void printBoard();
    int heuristic;
    int fscore;
    coordinate boardZero();
    
    void setH();
    void setfscore(int fscr);
};

class Node
{
  public:
    board nboard;
    int weight;
    Node* parent;
    bool hasParent;
};



int tileWeight(int arrayValue)
{
        switch (arrayValue)
        {
                case 1:
                        return 1;
                        break;
                case 2:
                        return 2;
                        break; 
                case 3:
                        return 3;
                        break;
                case 4:
                        return 4;
                        break;
                case 5:
                        return 5;
                        break;
                case 6:
                        return 6;
                        break;
                case 7:
                        return 7;
                        break;
                case 8:
                        return 8;
                        break;
                default:
                        return -1;
        }
}

//Print the board for testing purposes
void board::printBoard()
{
  for(int j = 0; j < 3; j++)
  {
    for(int i = 0; i < 3; i++)
    {
      cout << gameArea[j][i] << " "; 
    }
    cout << endl; 
  }
}

void board::setfscore(int fscr)
{
  fscore = fscr;
}

//Compare current node with goal node, get amount of displaced nodes (heuristic)
void board::setH()
{
  heuristic = 0;
  for(int j = 0; j < 3; j++)
  {     
    for(int i = 0; i < 3; i++)
    {
      if (gameArea[j][i] != goalArray[j][i])
      {
        if(gameArea[j][i] == 0)
        {
          continue;
        }
        ++heuristic; 
      }
    }
  }
}

//Finds the zero in the array, used to figure out which tiles can be moved
coordinate board::boardZero()
{
	coordinate a;
	a.x = 0;
	a.y = 0;
  for(int j = 0; j < 3; j++)
  {
    for(int i = 0; i < 3; i++)
    {
      if (gameArea[j][i] == 0)
      {
        a.x = i;
        a.y = j;
        return a;
      }
    }
  }
  return a;
}       

bool operator==(Node lhs, Node rhs)
{
  for(int j = 0; j < 3; j++)
  {
    for(int i = 0; i < 3; i++)
    {
      if(lhs.nboard.gameArea[j][i] != rhs.nboard.gameArea[j][i])
      {       
        return 0;
      } 
    }
  }
  return 1;
}

bool nodeInList(Node fNode, vector<Node> list)
{
  for(int i = 0; i < list.size(); i++)
  { 
    if(fNode == list.at(i))
    {
      return 1;
    }
  }
  return 0;
}

Node bringNIList(Node fNode, vector<Node> list)
{
  for(int i = 0; i < list.size(); i++)
  { 
    if(fNode == list.at(i))
    {
      return  list.at(i);
    }
  }
  return fNode;
}


int aStar(Node start)
{
    
        start.nboard.setH();
        
        if(start.nboard.heuristic == 0)
        {
          return 0;
        }
          
        vector<Node> open;
        vector<Node> closed;
        open.push_back(start);
  
        
        while (!open.empty())
        {
          
          Node current = open.back();  
          
          coordinate zero = current.nboard.boardZero();
          
          if(current.nboard.heuristic == 0)
          {
            return current.weight;
          }    
          
          //remove current from open
          open.pop_back();  
          
          // add current to closed
          closed.push_back(current);

          for(int k = 0; k < 4; k++)
          {
            //cout << "Begin For loop" << endl;
            Node newNode = current;
            
            //check element to right
            if(k == 0 && !(zero.x + 1 > 2))
            {
              
              newNode.weight += tileWeight(newNode.nboard.gameArea[zero.y][zero.x + 1]);

              //Swap zero with the value 1 space to its right
              swap(newNode.nboard.gameArea[zero.y][zero.x], 
                   newNode.nboard.gameArea[zero.y][zero.x + 1]);
  
            }
            
            //check element to left
            if(k == 1 && !(zero.x - 1 < 0))
            {
              
              newNode.weight += tileWeight(newNode.nboard.gameArea[zero.y][zero.x - 1]);

              //Swap zero with the value 1 space to its left
              swap(newNode.nboard.gameArea[zero.y][zero.x], 
                   newNode.nboard.gameArea[zero.y][zero.x - 1]);
              
            }
            
            //Check element down
            if(k == 2 && !(zero.y + 1 > 2))
            {
              
              newNode.weight += tileWeight(newNode.nboard.gameArea[zero.y + 1][zero.x]);

              //Swap zero with the value 1 space to its down
              swap(newNode.nboard.gameArea[zero.y][zero.x], 
                   newNode.nboard.gameArea[zero.y + 1][zero.x]); 

            }
            
            //Check the element up
            if(k == 3 && !(zero.y - 1 < 0))
            {
              
             newNode.weight += tileWeight(newNode.nboard.gameArea[zero.y - 1][zero.x]);
             
             //Swap zero with the value 1 space to its up
             swap(newNode.nboard.gameArea[zero.y][zero.x], 
                  newNode.nboard.gameArea[zero.y - 1][zero.x]); 

            }

            newNode.parent = &current;
            newNode.hasParent = true;

            if(newNode.nboard.heuristic == 0)
            {
              return newNode.weight;
            }
            
            newNode.nboard.setH();
            newNode.nboard.setfscore(newNode.weight + newNode.nboard.heuristic);
            
            //check if node is already in closed list
            if(nodeInList(newNode, closed))
            {
              continue;
            }           

            //If its alreay in open list
            if(!nodeInList(newNode, open))
            {
              open.push_back(newNode);
            }

            else 
            {
                //Node compare = bringNIList(newNode, open);
                if(bringNIList(newNode, open).weight > newNode.weight)
                {
                  for(int j = 0; j < open.size(); j++)
                  { 
                    if(newNode == open.at(j))
                    {
                      open.at(j).weight = newNode.weight;
                      open.at(j).nboard.heuristic = newNode.nboard.heuristic;
                      open.at(j).nboard.fscore = newNode.nboard.fscore;
                    }
                  }
                }
                continue;
            }
       
          }

          for(int i = 0; i < open.size(); i++)
          {
            int j = i;
            while(j > 0 && open.at(j - 1).nboard.fscore < open.at(j).nboard.fscore)
            {
              
              swap(open.at(j), open.at(j - 1));
              --j;
            }
            
          }
          
      }
	return 0;
}
