#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void setUp(int n);
void printBoard(char board[][26], int n);
void printValues(char board[][26], int n);
bool positionInBounds(int n, char row, char col);
void availableMoves(char board[][26], int n, char colour);
void flipIt(char board[][26], int n, int row, int col, char colour);
bool legalMove(char board[][26], int N, char row, char col, char colour);
bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);


bool positionInBounds(int n, char row, char col)
{
    int r = row - 'a', c = col - 'a';
    if((r >= 0 && c >= 0) && (r < n && c < n))
        return true;
    else
        return false;
}


void flip(char board[][26], int n, int row, int col, char colour)
{
    for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for(int deltaCol = -1; deltaCol <= 1; deltaCol++)
        {
            int count = 1;
            int newRow = row + count*deltaRow; 
            int newCol = col + count*deltaCol;
            
            while((newRow >= 0 && newRow <= (n -1)) == true && (newCol >= 0 && newCol <= (n -1)) == true)
            {

                newRow = row + count*deltaRow;
                newCol = col + count*deltaCol;
                
                if(board[newRow][newCol] != colour && board[newRow][newCol] != 'U')
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
    printBoard(board, n);
}


void availableMoves(char board[][26], int n, char colour)
{
    printf("Available moves for %c:\n",colour);
    for (int i = 0; i<n; i++)
   {
       for (int j = 0; j < n; j++)
       {
           if (board[i][j] == 'U')
           {
			   for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
			   {
				   for(int deltaCol = -1; deltaCol <= 1; deltaCol ++)
				   {
					   if(deltaRow == 0 && deltaCol == 0)
					   {
						  ;
					   }
					   
					   else
					   {   
	                      checkLegalInDirection(board, n, 'a'+i, 'a'+j, colour, deltaRow, deltaCol);
					   }
				   }
			   }
              
            }
	   }
        
    }
}


bool legalMove(char board[][26], int n, char row, char col, char colour)
{
    char oppcolour;
    if(colour == 'W')
    {
       oppcolour = 'B';
    }
    
    if(colour == 'B')
    {
       oppcolour = 'W'; 
    }
    
    int r = (row - 'a'), c = (col - 'a');
    int count = 0;
    for(int deltaRow = -1; deltaRow <= 1; deltaRow++)
    {
        for(int deltaCol = -1; deltaCol <= 1; deltaCol++)
        {
            if (board[r][c] == 'U')
           {
                if(positionInBounds(n,row,col) && board[r + deltaRow][c + deltaCol] == oppcolour)                
                {
                    count++; 
                }
           }
        }
    }

    if (count > 0)
    {
        printf ("Valid move.\n");
        board[r][c] = colour;
        flip(board, n, r, c, colour);
        return true;
    }
    else
    {
        printf("Invalid move.\n");
		printBoard(board, n);
        return false;
    }
}


bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol)
{ 
   int r = row - 'a';
   int c = col - 'a';
 
   int newRow = r;
   int newCol = c;
   int count = 1;
   int opponentCount =0;
   bool check = false; //Makes sure that it does'nt exit.

   bool done = false; 
   while ( done!=true )
   {
        newRow = r+count*deltaRow;
        newCol = c+count*deltaCol;
    
        if ((newRow>=0 && newRow<=n-1)==true && (newCol>=0 && newCol<=n-1) == true)
        {
            if (board[newRow][newCol] != colour && board[newRow][newCol]!= 'U')
            {
               opponentCount++;
            }
            
            if (board[newRow][newCol] == 'U' || (board[newRow][newCol] == colour && opponentCount==0))
            {
                break; 
            }
        
            else if(board[newRow][newCol] == colour && opponentCount>0)
            {
               printf ("%c%c\n", 'a'+ r, 'a'+ c);
               check = true;
               done = true;
            }
        }
            else
               done = true; 
               count++;
   }
   
   return check; 
}


void printValues(char board[][26], int n)
{   
    char coin;
    char row, col;
   
    printf("Enter board configuration:\n");
    while(coin != '!' && row != '!' && col != '!')
    {
        printf("", coin,row,col);
        scanf(" %c%c%c", &coin, &row, &col);

        board[row - 'a'][col - 'a'] =  coin;
    }
    printBoard(board, n);
    
    availableMoves(board, n, 'W');
    availableMoves(board, n, 'B');
    
    char colour, row1, col1;
    printf("Enter a move:\n");
    scanf(" %c%c%c", &colour, &row1, &col1);
    legalMove(board, n, row1, col1, colour);     
}


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


void setUp(int n)
{ 
    char board[n][26];
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
    printValues(board,n);
}


int main ()
{   
    int n;
    printf("Enter the board dimension: ");
    scanf("%d",&n);
    
    if((n <= 26) && (n%2 == 0))
    {
      setUp(n); 
    }
    
	return 0;
}
