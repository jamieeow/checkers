/*   
Programmed by:    Nicholas Rupert Custodio, 
				  Jamie Shekinah Mapa
				  Marius Laggui
				  S14        
Description: CCDSTRU MP   
Last modified: April 1, 2018      
*/ 
#include<stdio.h>
#include<stdlib.h>
typedef char string10[11];



//This function is used to printout the starting graphics
void Logo()
{
printf("\t\t  ________                                _____ \n");
printf("\t\t /  _____/_____    _____   ____     _____/ ____\\\n");
printf("\t\t/   \\  ___\\__  \\  /     \\_/ __ \\   /  _ \\   __\\\n");
printf("\t\t\\    \\_\\  \\/ __ \\|  Y Y  \\  ___/  (  <_> )  | \n");
printf("\t\t \\______  (____  /__|_|  /\\___  >  \\____/|__|   \n");
printf("\t\t        \\/     \\/      \\/     \\/             \n");
printf("\t\t           _               _                 \n");
printf("\t\t          | |             | |                \n");
printf("\t\t       ___| |__   ___  ___| | _____ _ __ ___ \n");
printf("\t\t      / __| '_ \\ / _ \\/ __| |/ / _ \\ '__/ __|\n");
printf("\t\t     | (__| | | |  __/ (__|   <  __/ |  \\__ \\\n");
printf("\t\t      \\___|_| |_|\\___|\\___|_|\\_\\___|_|  |___/\n\n\n");

}

/*	This function prints the horizontal lines that form the board
	@param  (int) i is a counter
*/
void
printLine(int nLines)
{
	int i;

	for(i=0;i<=nLines;i++)
		printf("-");
	printf("\n");
}

/*	This function prints the extra space for the board
	@param  (int) i is a counter
*/
void
printExtra()
{
	int i;

	for (i=1;i<=8;i++)
		printf("|     ");
	printf("|\n %49s"," ");

}


/*	This function is used to intialize the pieces and spaces on the board
	@param  (int[]) Alpha is player 1's current pieces
	@param  (int[]) Beta is player 2's current pieces
	@param  (int[]) Free is the free spaces available
	@param  (int) x is a counter for the x value
	@param  (int) y is a counter for the y value
*/
void
initialize(int Alpha[9][9],int Beta[9][9],int Free[9][9])
{
	int x,
		y;

	for(x=1; x<=8; x++)
	{
		for(y=1; y<=8; y++)
		{
			if((x%2 == 0 && y%2==1 || x%2==1 && y%2==0) && x<=3) //initializes alphas values
			{
				Alpha[x][y] = 1;
				Beta[x][y]= 0;
				Free[x][y]=0;
			}


			else if((x%2 == 0 && y%2==1 || x%2==1 && y%2 ==0)&& x>=6) //initializes betas values
			{
				Alpha[x][y] = 0;
				Beta[x][y]= 1;
				Free[x][y]=0;
			}

			else //intializes the free spaces
			{
			Alpha[x][y] = 0;
			Beta[x][y]= 0;
			Free[x][y]=1;
			}
		}
	}
}

/*	This function is used to print the board
	@param  (int[]) Alpha is player 1's current pieces
	@param  (int[]) Beta is player 2's current pieces
	@param  (int) x is a counter for the x value
	@param  (int) y is a counter for the y value
*/
void
printGame(int Alpha[9][9],int Beta[9][9])
{
	int x,
		y;

	printf("%50c\n %49s", 'X', " ");
	printLine(48);

	for(x=1;x<=8;x++)
	{
		printf("%50d",x); //prints the values of x onto the board
		for(y=1;y<=8;y++) //prints the pieces and free spaces onto the board
		{
			if(Alpha[x][y] == 1) 
				printf("|  A  ");
			else if (Beta[x][y] == 1)
				printf("|  B  ");
			else printf("|     ");

			if(y==8)
			{
				printf("|\n %49s"," ");
				printExtra();
				printLine(48);
			}
		}

		if(x==8)
		{
			printf("%50c",'Y');
			for(y=1;y<=8;y++)
				printf("   %d  ", y); //prints the values of y on the board
		}
	}
}

/*	This function is used to check if the piece chosen has an available space to move to
	@param  (int[]) Pieces is the pieces of the current player
	@param  (int[]) prev is the piece selected by the player
	@param  (int*) ok stores the truth value which tells if the piece chosen is valid
	@param  (int) aTurn tells which player is currently making a move
*/
void
checkPrev(int Pieces[9][9],int prev[2], int *ok, int aTurn)
{
	if(Pieces[prev[0]][prev[1]] == 1 && prev[0]>=1 && prev[0]<=8 && prev[1]>=1 && prev[1]<=8 )
	{
		*ok = 1;
		if (aTurn)
		{
			if(prev[1]>1 && prev[1]<8)
			{
				if(Pieces[prev[0]+1][prev[1]+1] == 1 && Pieces[prev[0]+1][prev[1]-1] == 1)
				{
					*ok = 0;
					printf("There's No Space To Move This Piece");
				}
			}
			else
			{
				if(Pieces[prev[0]+1][prev[1]+1] == 1 || Pieces[prev[0]+1][prev[1]-1] == 1)
					{
						*ok = 0;
						printf("There's No Space To Move This Piece");
					}
			}
		}

		if(!aTurn)
		{
			if(prev[1]>1 && prev[1]<8)
			{
				if(Pieces[prev[0]-1][prev[1]+1] == 1 && Pieces[prev[0]-1][prev[1]-1] == 1)
				{
					*ok = 0;
					printf("There's No Space To Move This Piece");
				}
			}
			else
			{
				if(Pieces[prev[0]-1][prev[1]+1] == 1 || Pieces[prev[0]-1][prev[1]-1] == 1)
					{
						*ok = 0;
						printf("There's No Space To Move This Piece");
					}
			}
	}
	}
	else printf("No piece found",prev[0],prev[1]);

}

/*	This function is used to check if the piece chosen has an available space to move to
	@param  (int[]) Free is the free spaces available
	@param  (int[]) Opponent is the location of the opponent's current pieces
	@param  (int[]) next is the space chosen by the player  to move the current selected piece
	@param  (int[]) prev is the piece selected by the player
	@param  (int*) ok stores the truth value which tells if the move chosen is valid
	@param  (int) aTurn tells which player is currently making a move
*/
void
checkNext(int Free[9][9], int Opponent[9][9],int next[2],int prev[2], int *ok, int aTurn)
{
	if((Free[next[0]][next[1]]== 1 ||Opponent[next[0]][next[1]]== 1 )
		&& (next[0] == prev[0]+1 || next[0] == prev[0]-1)
		&& (next[1] == prev[1] + 1 || next[1] == prev[1] - 1)
		&& (prev[0]>=1 && prev[0]<=8) && (prev[1]>=1 && prev[1]<=8) && 
		(next[0]>=1 && next[0]<=8) && (next[1]>=1 && next[1]<=8))
		*ok = 1;

	else
	{
		printf("Cant move Piece (%d,%d) to (%d,%d)\n",prev[0],prev[1],next[0],next[1]);

		if (prev[1]>1 && prev[1]<8)
		{
			if(aTurn)
				printf("Can move it to (%d,%d) or (%d,%d)\n", prev[0]+1,prev[1]+1,prev[0]+1,prev[1]-1);
			else printf("Can move it to (%d,%d) or (%d,%d)\n", prev[0]-1,prev[1]+1,prev[0]-1,prev[1]-1);
		}
		else if (prev[1]==1)
		{
			if(aTurn)
			printf("Can move it to (%d,%d)\n",prev[0]+1,prev[1]+1);
			else printf("Can move it to (%d,%d)\n",prev[0]-1,prev[1]+1);
		}
		else if (prev[1]==8)
		{
			if(aTurn)
				printf("Can  move it to(%d,%d)\n",prev[0]+1,prev[1]-1);
			else printf("Can move it to (%d,%d)\n",prev[0]-1,prev[1]-1);
		}
	}
}

/*	This function is used to check the number of  pieces remaining on the board for each player
	@param  (int[]) Alpha is player 1's current pieces
	@param  (int[]) Beta is player 2's current pieces
	@param  (int*) over stores the truth value which tells if the game is over
	@param  (int) x is a counter for the x value
	@param  (int) y is a counter for the y value
	@param  (int) overA stores player 1's remaining number of pieces
	@param  (int) overB stores player 2's remaining number of pieces
	@param  (char) cDump stores the enter character
*/
int
GameOver(int Alpha[9][9],int Beta[9][9],int *over)
{
	int x,
		y,
		overA=0,
		overB=0;
	char cDump;

	for(x=1; x<=8;x++)
		for(y=1; y<=8; y++)
		{
			overA += Alpha[x][y];//adds up Alphas remaining pieces
			overB += Beta[x][y]; //adds up Betas remaining pieces
		}

	if(overA==0)
		*over = 1;

	else if(overB==0)
		*over = 2;

	else
	{
		printf("\nPress Enter to continue...");
		scanf("%c%c",&cDump,&cDump);
	    system ("CLS");
	}
}

/*	This function is used to Move the current player's piece
	@param  (int[]) Player is current player's pieces
	@param  (int[]) Opponent is the opponent's current pieces
	@param  (int[]) Free is the free spaces available
	@param  (int[]) prev is the piece selected by the player
	@param  (int[]) next is the space chosen by the player to move the current selected piece
	@param  (char[]) player stores the current player's name

*/
void
NextPlayerMove(int Player[9][9],int Opponent[9][9],int Free[9][9],int prev[2], int next[2], string10 player, int *aTurn)
{
	Player[prev[0]][prev[1]] = 0; 
	Free[prev[0]][prev[1]] = 1;
	Player[next[0]][next[1]] = 1;
	if(Opponent[next[0]][next[1]]==1) //if an opponent is taken by the player
		Opponent[next[0]][next[1]]= 0;
	else 
	{
		Free[next[0]][next[1]]= 0;
		*aTurn = !(*aTurn);
	}

	printf("\n%s Moved (%d,%d) to (%d,%d)",player, prev[0],prev[1],next[0],next[1]);

}


int main()
{
	int Alpha[9][9],
	    Beta[9][9],
		Free[9][9];
	int aTurn = 1,
		ok = 0,
		over = 0;
	int prev[2], 
		next[2];
	string10 player1,
			 player2;
	char cDump;

    Logo(); //start up screen
	initialize(Alpha,Beta,Free);
	printf("Player 1's Name (max 10 characters): ");
	scanf("%s",player1);
	printf("Player 2's Name (max 10 characters): ");
	scanf("%s",player2);
	printf("\nWelcome %s and %s!\n",player1,player2);
	printf("Press Enter to Continue..");
	scanf("%c%c",&cDump,&cDump);
	system ("CLS");

	while(!over) //Continues the game until over is true
	{
		printGame(Alpha,Beta); //prints the board
		if(aTurn)
			printf("\n\n%s's Turn (A)",player1);
		else printf("\n\n%s's Turn (B)",player2);
		ok = 0;
		while(!ok) //asks the user to pick a piece to move, repeats if piece is invalid
		{
			printf("\n\nWhich piece do you want to move?\n");
			printf("x:");
			scanf("%d",&prev[0]);
			printf("y:");
			scanf("%d",&prev[1]);

			if(aTurn)
				checkPrev(Alpha,prev,&ok,aTurn);
			else checkPrev(Beta,prev,&ok,aTurn);
		}
		ok = 0;
		while(!ok) //asks the user where they want to move the currentpiece, repeats if space is invalid
		{
			printf("\nWhere do you want to move piece (%d,%d)?\n",prev[0],prev[1]);
			printf("x: ");
			scanf("%d",&next[0]);
			printf("y: ");
			scanf("%d",&next[1]);

			if(aTurn)
				checkNext(Free,Beta, next, prev,&ok,aTurn);
			else checkNext(Free,Alpha, next, prev,&ok,aTurn);
		}
		if(aTurn)
			NextPlayerMove(Alpha,Beta,Free,prev,next,player1,&aTurn); //moves the pieces
		else NextPlayerMove(Beta,Alpha,Free,prev,next,player2,&aTurn);
		GameOver(Alpha,Beta,&over); //checks if the game is over
	}
	if(over == 1)
		printf("%s won!",player2);
	else printf("%s won!",player1);
	return 0;
}
