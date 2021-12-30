#include<bits/stdc++.h>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526 // (25 * 25 - 99)

int SIDE ; // side length of the board
int MINES ; // number of mines on the board

bool isValid(int row, int col){
	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}

bool isMine (int row, int col, char board[][MAXSIDE]){
	if (board[row][col] == '*')
		return true;
	return false;
}

void printBoard(char myBoard[][MAXSIDE]){
	cout << " ";
	for(int i=0; i<SIDE; i++)
		cout << i << " ";
	cout << "\n" << endl;
	for(int i=0; i<SIDE; i++){
		cout << i << "\t";
		for(int j=0; j<SIDE; j++)
			cout << myBoard[i][j] << " ";
		cout << endl;
	}
	return;
}

int countAdjacentMines(int row, int col, char realBoard[][MAXSIDE]){
	int count = 0;
	if (isValid (row-1, col) == true)
		if (isMine (row-1, col, realBoard) == true)
            count++;
	if (isValid (row+1, col) == true)
		if (isMine (row+1, col, realBoard) == true)
	    	count++;
	if (isValid (row, col+1) == true)
		if (isMine (row, col+1, realBoard) == true)
    		count++;
	if (isValid (row, col-1) == true)
		if (isMine (row, col-1, realBoard) == true)
			count++;
	if (isValid (row-1, col+1) == true)
		if (isMine (row-1, col+1, realBoard) == true)
			count++;
	if (isValid (row-1, col-1) == true)
		if (isMine (row-1, col-1, realBoard) == true)
			count++;
	if (isValid (row+1, col+1) == true)
		if (isMine (row+1, col+1, realBoard) == true)
			count++;
	if (isValid (row+1, col-1) == true)
		if (isMine (row+1, col-1, realBoard) == true)
			count++;
	return count;
}

bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
			int mines[][2], int row, int col, int *movesLeft){
	// Base Case of Recursion
	if (myBoard[row][col] != '-')
		return false;

	if (realBoard[row][col] == '*'){
		myBoard[row][col]='*';
		for (int i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';
		printBoard (myBoard);
		printf ("\nYou lost :((\n");
		return true;
	}
	else{
		int count = countAdjacentMines(row, col, realBoard);
		(*movesLeft)--;
		myBoard[row][col] = count + '0';
		if (count==0){
			if (isValid (row-1, col) == true)
				if (isMine (row-1, col, realBoard) == false)
				    playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			if (isValid (row+1, col) == true)
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			if (isValid (row, col+1) == true)
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			if (isValid (row, col-1) == true)
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			if (isValid (row-1, col+1) == true)
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			if (isValid (row-1, col-1) == true)
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			if (isValid (row+1, col+1) == true)
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			if (isValid (row+1, col-1) == true)
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
		}
		return false;
	}
}

void placeMines(int mines[][2], char realBoard[][MAXSIDE]){
	bool mark[MAXSIDE*MAXSIDE];
	memset(mark, false, sizeof (mark));
	for (int i=0; i<MINES; ){
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;
		// Add the mine if no mine is placed at this position on the board
		if (mark[random] == false){
			mines[i][0]= x;
			mines[i][1] = y;
			realBoard[x][y] = '*';
			mark[random] = true;
			i++;
		}
	}
}

void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE]){
	// Initiate the random number generator so that
	// the same configuration doesn't arises
	srand(time(NULL));
	for (int i=0; i<SIDE; i++){
		for (int j=0; j<SIDE; j++){
			myBoard[i][j] = '-';
            realBoard[i][j] = '-';
        }
    }
}

void playMinesweeper(){
	bool gameOver = false;
	char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];
	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines.
	initialise (realBoard, myBoard);
	placeMines (mines, realBoard);
	int currentMoveIndex = 0;
	while (gameOver == false){
		cout << "Current Status of Board : " << endl;
		printBoard (myBoard);
        cout << endl;
	    cout << "Enter your move(space separated row & column) -> ";
	    cin >> x >> y;
        while(!isValid(x,y)){
            cout << "Not a valid move. Please enter your move again -> ";
            cin >> x >> y;
        }
		currentMoveIndex ++;
		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);
		if ((gameOver == false) && (movesLeft == 0)){
			cout << "\nYou won !!!" << endl;
			gameOver = true;
		}
	}
}

void chooseDifficultyLevel (){
	/*
	--> BEGINNER = 9 * 9 Cells and 10 Mines
	--> INTERMEDIATE = 16 * 16 Cells and 40 Mines
	--> ADVANCED = 24 * 24 Cells and 99 Mines
	*/
	int level;
	cout << "Enter the Difficulty Level" << endl;
    cout << "Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)" << endl;
    cout << "Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)" << endl;
    cout << "Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)" << endl;
	cin >> level;
	if(level == BEGINNER){
		SIDE = 9;
		MINES = 10;
	}
	else if(level == INTERMEDIATE){
		SIDE = 16;
		MINES = 40;
	}
    else if(level == ADVANCED){
		SIDE = 24;
		MINES = 99;
	}
    else
        cout << "Please enter only 0, 1 or 2" << endl;
}

int main(){
	chooseDifficultyLevel();
	playMinesweeper();
	return 0;
}