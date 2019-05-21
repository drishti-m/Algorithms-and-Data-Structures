
//reference: https://www.geeksforgeeks.org/place-k-knights-such-that-they-do-not-attack-each-other/

#include <iostream> 
using namespace std; 
  
/* 
n*n is the board size
n is the number of knights to be placed on board  
solutions_no is the number of possible solutions */
int n, k; 
int solutions_no = 0; 
  
/*   Create an empty board of size n*n   */
void makeBoard(char** board) 
{ 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            board[i][j] = '_'; 
        } 
    } 
} 
  
/* displays the n*n board */
void displayBoard(char** board) 
{ 
    cout << endl; 
         
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            cout << " " << board[i][j] << " "; 
        } 
        cout << endl; 
    } 
} 
  
/* marks all the attacking 
 position of a knight placed at board[i][j] 
  */
void mark_attack(int x, int j, char a, 
            char** board) 
{ 
  
    /* conditions to ensure that the  
       block to be checked is inside the board */
    if ((x + 2) < n && (j - 1) >= 0) { 
        board[x + 2][j - 1] = a; 
    } 
    if ((x - 2) >= 0 && (j - 1) >= 0) { 
        board[x - 2][j - 1] = a; 
    } 
    if ((x + 2) < n && (j + 1) < n) { 
        board[x + 2][j + 1] = a; 
    } 
    if ((x - 2) >= 0 && (j + 1) < n) { 
        board[x - 2][j + 1] = a; 
    } 
    if ((x + 1) < n && (j + 2) < n) { 
        board[x + 1][j + 2] = a; 
    } 
    if ((x - 1) >= 0 && (j + 2) < n) { 
        board[x - 1][j + 2] = a; 
    } 
    if ((x + 1) < n && (j - 2) >= 0) { 
        board[x + 1][j - 2] = a; 
    } 
    if ((x - 1) >= 0 && (j - 2) >= 0) { 
        board[x - 1][j - 2] = a; 
    } 
} 
  
/* If the position is empty, 
   return true, as knight can be placed */
bool check_placeKnight(int i, int j, char** board) 
{ 
    if (board[i][j] == '_') 
        return true; 
    else
        return false; 
} 
  
/* place the knight at [i][j] position 
   on board */
void placeKnight(int i, int j, char k, char a, 
           char** board, char** new_board) 
{ 
  
    /* copy old board to new board */
    for (int y = 0; y < n; y++) { 
        for (int z = 0; z < n; z++) { 
            new_board[y][z] = board[y][z]; 
        } 
    } 
  
    /* placing knight at position[i][j] */
    new_board[i][j] = k; 
  
    /* mark all attacking positions in new board, with knight placed */
    mark_attack(i, j, a, new_board); 
} 
  
/* Function for placing knights on board 
   such that they don't attack each other */
void Final_knight_board(int k, int xi, int xj, char** board) 
{ 
  
    /* If there are no knights left to be placed, 
     display the board and increment the count of solutions_no .
     */
    //Base case:
    if (k == 0) { 
        displayBoard(board); 
        solutions_no++; 
    } 
    else { 
  
        /* Loop for checking all the  
       positions on n*n board */
        for (int i = xi; i < n; i++) { 
            for (int j = xj; j < n; j++) { 
  
                /* check if it is possible to place knight at  
           [i][j] position on board */
                if (check_placeKnight(i, j, board)) { 
  
                    /* Create a a new board and place the  
                      new knight on it */
                    char** new_board = new char*[n]; 
                    for (int x = 0; x < n; x++) { 
                        new_board[x] = new char[n]; 
                    } 
                    placeKnight(i, j, 'K', 'A', board, new_board); 
  
                    /* Recursively call function for 
                      (k-1) left knights */
                    Final_knight_board(k - 1, i, j, new_board); 
  
                    /* Delete the new board  */
                    for (int x = 0; x < n; x++) { 
                        delete[] new_board[x]; 
                    } 
                    delete[] new_board; 
                } 
            } 
            xj = 0; 
        } 
    } 
} 
  
// Test code
int main() 
{ 
    cout << "Enter n\n";
    cin >> n;
     k = n; 
  
    /* allocation while creating a n*n board */
    char** board = new char*[n]; 
    for (int i = 0; i < n; i++) { 
        board[i] = new char[n]; 
    } 
  
    /* Make board such that all the places are empty */
    makeBoard(board); 
    cout << "Creating a board..\n";

    cout << "\nPossible solutions placing knights as K are:" << endl;
  
  //Place knights such that they dont attack
    Final_knight_board(k, 0, 0, board); 
  
    cout << endl 
         << "Total number of solutions for " << n << " knights are: "
         << solutions_no; 
    return 0; 
} 