#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void setUp(char board[][26], int n);
void printBoard(char board[][26], int n);
bool gameOutcome(char board[][26], int n);
int totalMoves(char board[][26], int n, char colour);
void flip(char board[][26], int n, int row, int col, char colour);
int scoreValue(char board[][26], int n, int row, int col, char compColour);
void computerMoves(char board[][26],int n, char colour, char storeMoves[26][26]);
bool availableMoves(char board[][26], int n, char colour, char storeMoves[26][26]);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);

void printBoard(char board[][26], int n)
{   
    printf("  ");
    for(int row = 0; row < n; row++)
    {
        printf("%c", (97+row)); //horizontal
    }
    printf("\n");
    
    for(int i = 0; i < n; i++)
    {
        printf(" %c", (97+i));  //vertical
        for(int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void setUp(char board[][26], int n)
{ 
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        { 
            if((i == n/2 - 1 && j == n/2 - 1)  || (j == n/2 && i == n/2))
                board[i][j] = 'W';
            else if((i == n/2 && j == n/2 - 1) || (j == n/2 && i == n/2 - 1))
                board[i][j] = 'B';
            else
                board[i][j] = 'U';
        }
    }
    printBoard(board,n);
}

int main ()
{   
    int n;
    char compColour, userColour = 'U';
    
    printf("Enter the board dimension: ");
    scanf("%d",&n);
	char board[n][26];
    printf("Computer plays (B/W): ");
    scanf(" %c", &compColour);

    setUp(board, n); 
      
    char row, col;
    char whiteMoves[26][26], blackMoves[26][26];
    int totalBMoves, totalWMoves;
    bool done = false, finished = false;
    
    if(compColour == 'W')
    {
        userColour= 'B';
        while (finished == false)
        {
            totalBMoves = totalMoves(board, n, userColour);
			
            if (totalBMoves > 0)
            {
               printf("Enter a move for colour %c (RowCol): ", userColour);
               scanf(" %c%c",&row,&col);
      
               int newRow = (row - 'a');
               int newCol = (col - 'a');
               
               done = availableMoves(board, n, userColour, blackMoves);
               
               if (done == true)
               {
                   if(blackMoves[newRow][newCol] == userColour)
                   {
                      board[newRow][newCol] = userColour;
                      flip(board, n, newRow, newCol, userColour);
                   }
                   
                    else 
                    {
                        printf ("Invalid move.\n%c player wins.", compColour);
                        finished = true;
                        break;
                    }
                   totalWMoves = totalMoves(board, n, compColour);
                   
                   if(totalWMoves > 0)
                   {
                      availableMoves(board, n, compColour, whiteMoves);
                      computerMoves(board, n, compColour, whiteMoves);
                   }
                   else if (totalWMoves == 0)
                   {
                       finished = gameOutcome(board,n);
                       if (finished == true);
                       else 
                       {
                           printf ("%c player has no valid moves.\n", compColour);
                       }
                   }
                }
                    
            else if (totalBMoves == 0)
            {
               totalWMoves = totalMoves(board, n, compColour);
             
               if (totalWMoves > 0)
               {
                  printf ("%c player has no valid moves.\n", compColour);
				  
                  availableMoves(board, n, compColour, whiteMoves);
                  computerMoves(board, n, compColour, whiteMoves);
                  finished = gameOutcome(board, n);
               }
            
               else if (totalWMoves == 0)
               {
                  finished = gameOutcome(board, n);
               }
            }
            
            for(int cleanRow = 0; cleanRow < n; cleanRow++)
            {
               for(int cleanCol = 0; cleanCol < n; cleanCol++)
              {
                  whiteMoves[cleanRow][cleanCol] = 'U';
                  blackMoves[cleanRow][cleanCol] = 'U';
              } 
            }
         }
       }
    }
    else if (compColour == 'B')
    {
       userColour = 'W';
       while (finished == false)
       {
          totalBMoves = totalMoves(board, n, compColour);
          
          if (totalBMoves > 0)
          {
             availableMoves(board, n, compColour, blackMoves);
             computerMoves(board, n, compColour, blackMoves);
             totalWMoves = totalMoves(board, n, userColour);
             
             if (totalWMoves > 0)
             {
                 printf("Enter a move for colour %c (RowCol): ", userColour);
                 scanf(" %c%c",&row,&col);
      
                 int newRow = (row - 'a');
                 int newCol = (col - 'a');
                 
                 if(availableMoves(board, n, userColour, whiteMoves) == true)
                 {
                      if(whiteMoves[newRow][newCol] == userColour)
                      {
                          board[newRow][newCol] = userColour;
                          flip(board, n, newRow, newCol, userColour);
                          finished = gameOutcome(board, n);
                      }
                      else
                      {
                          printf ("Invalid Move.\n%c player wins.", compColour);
                          finished = true;
                      }
                 }
                else if (totalWMoves == 0)
                {
                   finished = gameOutcome(board, n);
                   if (finished == true);
                   else 
                   {
                      printf ("%c has no valid moves.", userColour);
                   }
                }
            }
           
           else if (totalBMoves == 0)
           {
              totalWMoves = totalMoves(board, n, userColour);
              if (totalWMoves == 0)
              {
                 finished = gameOutcome(board,n);
              }
              
              else 
              {
                 printf ("%c has no valid moves", compColour);
                 if(availableMoves(board, n, userColour, whiteMoves) == true)
                 {
                     finished = gameOutcome(board, n);
                 }
                 else
                 {
                    printf ("%c player wins.", compColour);
                    finished = true;
                  }
              }
           } 
        }
   
       for(int cleanRow = 0; cleanRow < n; cleanRow++)
       {
           for(int cleanCol = 0; cleanCol < n; cleanCol++)
          {
             whiteMoves[cleanRow][cleanCol] = 'U';
             blackMoves[cleanRow][cleanCol] = 'U';
          }
       } 
    }
  }
 return 0;
}


bool gameOutcome(char board[][26], int n)
{
    int whiteMoves = 0, blackMoves = 0, vacantSpaces = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (board [row][col] == 'W')
            {
                whiteMoves++;
            }
            else if (board[row][col] == 'B')
            {
                blackMoves++; 
            }
            else if (board[row][col] == 'U')
            {
                vacantSpaces++; 
            }
        }
    }
    
    if(vacantSpaces > 0)
    {
      return false;
    }
    else if(vacantSpaces == 0)
    {
      if (blackMoves > whiteMoves)
      {
         printf ("B player wins.");
         return true;
      }
      else if (whiteMoves > blackMoves)
      {
         printf ("W player wins.");
         return true;
      }
      else if (blackMoves == whiteMoves)
      {
         printf ("Draw.");
         return true;
      }
    }
}

bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{ 
   
    int newRow = row - 'a';
    int newCol = col - 'a';
    int check = false;
    char opponentColour;
    int opponentCount = 0;
 
    if (colour == 'W')
    {
       opponentColour = 'B';
    }
    
    else
    {
       opponentColour = 'W';
    }
        
    while ((newRow >= 0 && newRow < n)== true && (newCol >= 0 && newCol < n) == true)
    {
       newRow = newRow + deltaRow;
       newCol = newCol + deltaCol;
        
       if ((newRow>=0 && newRow<n)== false && (newCol >= 0 && newCol <n)==false)
            break; 
            
       if (board[newRow][newCol] == opponentColour)
       {
            opponentCount++; 
       }
       else if (board[newRow][newCol] == colour && opponentCount>0)
       {
            check = true; 
       }
       else 
            break; 
    }
    return check; 
}


bool availableMoves(char board[][26], int n, char colour, char storeMoves[26][26])
{
   bool done = false; 
   for(int row = 0; row < n; row++)
   {
       for(int col = 0; col < n; col ++)
       {
           if (board[row][col] == 'U')
           {
               for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
               {
                   for(int deltaCol = -1; deltaCol <= 1; deltaCol ++)
                   {
                      if(deltaRow == 0 && deltaCol == 0)
                      {
                          ;
                      }
                      else if(checkLegalInDirection(board, n, (row +'a'), (col +'a'), colour, deltaRow, deltaCol) == true)
                          {
                              storeMoves[row][col] = colour;
                              done = true;
                          }
                       }
                   }
               }
           } 
       }
    return done;
}


void flip(char board[][26], int n, int row, int col, char colour)
{
    char opponentColour;
     if (colour == 'W')
    {
       opponentColour = 'B';
    }
    
    else
    {
       opponentColour = 'W';
    }
    
    for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for(int deltaCol = -1; deltaCol <= 1; deltaCol++)
        {
            if(checkLegalInDirection(board, n, (row + 'a'), (col + 'a'), colour, deltaRow, deltaCol) )
            {
                int count = 1;
                int newRow = row + count*deltaRow; 
                int newCol = col + count*deltaCol;
            
               while((newRow >= 0 && newRow <= (n -1)) == true && (newCol >= 0 && newCol <= (n -1)) == true)
               {
               
                    newRow = row + count*deltaRow;
                    newCol = col + count*deltaCol;
                
                    if(board[newRow][newCol] == opponentColour)
                    {
                       board[newRow][newCol] = colour;
                    }
                    
                    else 
                    {
                    break;
                    }
                count++;
              }
            }
        }
    }
    printBoard(board, n);
}


int scoreValue(char board[][26], int n, int row, int col, char colour)
 {
     int score = 0;
     for(int deltaRow = -1; deltaRow<= 1; deltaRow++)
     {
        for(int deltaCol = -1; deltaCol <=1; deltaCol++)
        {  
           if (checkLegalInDirection(board, n, ('a' + row), ('a' + col), colour, deltaRow, deltaCol) == true)
           {  
               int count = 1;
               int newRow = row + count*deltaRow;
               int newCol = col + count*deltaCol;
         
               while ( (newRow >= 0 && newRow < n) == true && (newCol >= 0 && newCol < n) == true)  
               {
                    newRow = row + count*deltaRow;
                    newCol = col + count*deltaCol;
        
                    if (board[newRow][newCol] != colour && board[newRow][newCol] != 'U') //opponent colour
                    {
                       score++; 
                    }
                    
                   else
                   {
                      break;
                   }
              count++;
              }
           }
        }
     }
   return score; 
}


void computerMoves (char board[][26], int n, char colour, char storeMoves[26][26])
{
    int maxValue = 0, score;
    int row = 0, col = 0; 
    int tempRow = 0, tempCol = 0;

    for (row = 0; row < n; row++)
   {
       for (col = 0; col < n; col++)
       { 
            if (storeMoves[row][col] == colour)
            { 
				printf ("rowcol: %c%c: ", row+'a', col+'a');
                score = scoreValue(board, n, row, col, colour);
				printf ("%d\n", score);
                if (maxValue < score)
               {
                   maxValue = score;
                    tempRow = row;
                    tempCol = col;
               }
            
               else if (maxValue == score)
               {
                    if (tempRow == row && tempCol > col) 
                    {  
                        //same row --> least column
                        tempCol = col;
                        //printf("%d", tempCol);
                    }
					else if (tempRow < row);
                }
            }
        }
   }
     printf ("Computer places %c at %c%c\n", colour, (tempRow + 'a'), (tempCol + 'a'));
     board[tempRow][tempCol] = colour; 
     flip(board, n, tempRow, tempCol, colour);
}


int totalMoves(char board[][26], int n, char colour)
{
   int NoOfMoves = 0;
   for(int row = 0; row < n; row++)
   {
       for(int col = 0; col < n; col ++)
       {
           if (board[row][col] == 'U')
           {
               for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
               {
                   for(int deltaCol = -1; deltaCol <= 1; deltaCol++)
                   {
                      if(deltaRow == 0 && deltaCol == 0)
                      {
                          ;
                      }
                      else if(checkLegalInDirection(board, n, (row+'a'), (col+'a'), colour, deltaRow, deltaCol) == true)
                          {
                              NoOfMoves++;
                          }
                    }
                }
            }
        } 
    }
    return NoOfMoves;
}

