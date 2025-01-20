#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10//Maximum board size

char board[MAX][MAX];
int n;//Board size
char playerSymbol,computerSymbol;
int movesLeft;

void initializeBoard() 
{for (int i=0;i<n;i++)
for (int j= 0;j<n;j++)
board[i][j]= ' ';
}

void displayBoard() 
{printf("\n");
for(int i=0;i<n;i++) 
{for(int j=0;j<n;j++) 
{printf(" %c ",board[i][j]);
if(j<n-1) 
printf("|");
}
printf("\n");
if(i<n - 1) 
{for(int k=0;k<n;k++) 
{printf("---");
if(k<n-1) 
printf("+");
}
printf("\n");
}
}
printf("\n");
}

int isWinningMove(char symbol) 
{// Check rows and columns
for(int i=0;i<n;i++) 
{int rowCount=0,colCount=0;
for(int j=0;j<n;j++) 
{if(board[i][j]==symbol) 
rowCount++;
if(board[j][i]==symbol) 
colCount++;
}
if(rowCount==n || colCount==n) 
return 1;
}
// Check diagonals
int diag1=0,diag2=0;
for(int i=0;i<n;i++) 
{if (board[i][i]==symbol) 
diag1++;
if (board[i][n-i-1]==symbol) 
diag2++;
}
if(diag1==n || diag2==n) 
return 1;
return 0;
}

int isDraw() 
{return movesLeft == 0;
}

void playerMove() 
{int x, y;
do 
{printf("Your move! Enter row and column (1-%d): ", n);
scanf("%d %d",&x,&y);
x--; 
y--;
if(x>= 0 && x<n && y>=0 && y<n && board[x][y]==' ') 
{board[x][y] = playerSymbol;
movesLeft--;
break;
}
else 
{printf("Invalid move. Try again!\n");
}
} 
while(1);
}

int minimax(int depth, int isMaximizing) 
{if(isWinningMove(computerSymbol)) 
return 10-depth;
if(isWinningMove(playerSymbol)) 
return depth-10;
if(isDraw()) 
return 0;
int bestScore=isMaximizing?-1000:1000;
for(int i=0;i<n;i++) 
{for(int j=0;j<n;j++) 
{if(board[i][j]==' ') 
{board[i][j]=isMaximizing?computerSymbol:playerSymbol;
int score=minimax(depth+1,!isMaximizing);
board[i][j]=' ';
bestScore=isMaximizing?(score>bestScore?score:bestScore):(score<bestScore?score:bestScore);
}
}
}
return bestScore;
}

void computerMove() 
{int bestScore=-1000;
int moveX=-1,moveY=-1;
printf("Computer is thinking...\n");
for(int i=0;i<n;i++) 
{for(int j=0;j<n;j++) 
{if(board[i][j]==' ') 
{board[i][j]=computerSymbol;
int score=minimax(0,0);
board[i][j]=' ';
if(score>bestScore) 
{bestScore=score;
moveX=i;
moveY = j;
}
}
}
}
board[moveX][moveY]=computerSymbol;
movesLeft--;
printf("Computer chose row %d and column %d\n",moveX+1,moveY+1);
}

void main() 
{
printf("Welcome to the Ultimate %dx%d Tic-Tac-Toe Game!\n", MAX, MAX);
do
{printf("Enter the board size (n x n, max %d): ", MAX);
scanf("%d", &n);
if(n<3 || n>MAX) 
{printf("Invalid size. Please choose between 3 and %d.\n", MAX);
}
}while(n<3 || n>MAX);

printf("Choose your symbol (X or O): ");
scanf("\n%c", &playerSymbol);
if(playerSymbol!='X' && playerSymbol!='O') 
{printf("Invalid symbol. Defaulting to X.\n");
playerSymbol='X';
}

computerSymbol=(playerSymbol=='X')?'O':'X';

printf("Do you want to play first? (y/n): ");
char choice;
scanf("\n%c",&choice);
int playerTurn=(choice=='y'||choice=='Y')?1:0;

initializeBoard();
movesLeft = n * n;
printf("Let the game begin!\n");
displayBoard();
while(1) 
{if(playerTurn) 
{playerMove();
displayBoard();
if(isWinningMove(playerSymbol)) 
{printf("Congratulations! You won!\n");
break;
}
} 
else 
{computerMove();
displayBoard();
if(isWinningMove(computerSymbol)) 
{printf("Oh no! The computer won. Better luck next time!\n");
break;
}
}
if(isDraw()) 
{printf("It's a draw! Well played.\n");
break;
}
playerTurn=!playerTurn;
}
printf("Game Over. Thanks for playing!\n");
}