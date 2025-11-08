#include <iostream>
using namespace std;

const int BOARD_LENGTH = 3;
const string EMPTY_SPACE = "-";
const string PLAYER_1 = "X";
const string PLAYER_2 = "O";

string board[BOARD_LENGTH + 1][BOARD_LENGTH + 1];

//checks if one of the players already marked the space on the game board
bool isOccupied(int line, int column) {
    if (board[line][column] == EMPTY_SPACE) {
        return true;
    }
    return false;
}

//checks what player starts first
int playerStart() {
    
    return 1;
}

//marks board with either X or 0;
void markBoard(string player) {
    
}


int main() {
    for (int i = 1; i <= BOARD_LENGTH; ++i) {
        for (int j = 1; j <= BOARD_LENGTH; ++j) {
            board[i][j] = EMPTY_SPACE;
            //out << board[i][j] << " ";
        }
        cout << "\n";
    }
    if (isOccupied(1, 1) == true) {
        cout << "este adevarat";
    }
    return 0;
}
