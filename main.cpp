#include <iostream>
#include <utility>
using namespace std;

const int BOARD_LENGTH = 3;
const int LINES = 8;
const int COLUMNS = 3;
const int MAX_MOVES = 9;
const string EMPTY_SPACE = "_";
const string PLAYER_1 = "❌";
const string PLAYER_2 = "🅾️";

string board[BOARD_LENGTH + 1][BOARD_LENGTH + 1];
string player = PLAYER_1;

const pair<int, int> winningCases[LINES][COLUMNS] = {
    { {1,1}, {1,2}, {1,3} },
    { {2,1}, {2,2}, {2,3} },
    { {3,1}, {3,2}, {3,3} },
    { {1,1}, {2,1}, {3,1} },
    { {1,2}, {2,2}, {3,2} },
    { {1,3}, {2,3}, {3,3} },
    { {1,1}, {2,2}, {3,3} },
    { {1,3}, {2,2}, {3,1} }
};


void gameRules() {
    cout << "Regulile jocului:" << "\n";
    cout << "Primul jucator care obtine 3 de X/0 pe coloana/linie/diagonala castiga" << "\n";
    cout << "Pentru linie/coloana poti introduce valori doar intre 1-3" << "\n";
    cout << "Daca spatiul este ocupat trebuie sa introduci niste valori valide pentru o pozitie goala" << "\n";
    cout << "Jucatorul 1 - " << PLAYER_1 << "\n";
    cout << "Jucatorul 2 - " << PLAYER_2 << "\n";
}

void drawEmptyBoard(string board[BOARD_LENGTH + 1][BOARD_LENGTH + 1]) {
    for (int i = 1; i <= BOARD_LENGTH; ++i) {
        for (int j = 1; j <= BOARD_LENGTH; ++j) {
            board[i][j] = EMPTY_SPACE;
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

string playerTurn(string &player) {
    if (player == PLAYER_1) {
        player = PLAYER_2;
        return "Este randul Jucatorului 1 - ❌\n";
    } else {
        player = PLAYER_1;
        return "Este randul Jucatorului 2 - 🅾️\n";
    }
}

//checks if one of the players already marked the space on the game board
bool isOccupied(int line, int column) {
    if (board[line][column] == EMPTY_SPACE) {
        return true;
    }
    return false;
}

//marks board with either X or 0;
void markBoard(string player, int line, int column) {
    if ((line >= 1 && line <= BOARD_LENGTH) && (column >= 1 && column <= BOARD_LENGTH)) {
        if (isOccupied(line, column)) {
            board[line][column] = player;
        } else {
            cout << "Pozitia este ocupata, introdu alte valori\n";
            cout << "Reintrodu linie: ";
            cin >> line;
            cout << "Reintrodu coloana: ";
            cin >> column;
            markBoard(player, line, column);
        }
    } else {
        cout << "Nu ai introdus o pozitie existenta pe tabla de joc";
        cout << "Reintrodu linia: ";
        cin >> line;
        cout << "Reintrodu coloana: ";
        cin >> column;
        markBoard(player, line, column);
    }
}

bool checkWinner(string player) {
    for (auto winCombo : winningCases) {
        if (board[winCombo[0].first][winCombo[0].second] == player &&
            board[winCombo[1].first][winCombo[1].second] == player &&
            board[winCombo[2].first][winCombo[2].second] == player) {
            return true;
        }
    }
    return false;
}

void drawBoard() {
    for (int i = 1; i <= BOARD_LENGTH; ++i) {
        for (int j = 1; j <= BOARD_LENGTH; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

void restartGame(bool &gameFinished, int &moves, string &playerMove) {
    int answer;
    cout << "Incepe un joc nou? Da - 1, Nu - 2\n";
    cin >> answer;
    if (answer == 1) {
        gameFinished = false;
        moves = 0;
        playerMove = PLAYER_1;
    } else {
        gameFinished = true;
    }
}

int main() {
    int line, column;
    int moves = 1;
    bool finishGame = false;
    string nextMove = PLAYER_1;
    
    gameRules();
    
    while (!finishGame) {
        if (moves == 1) {
            drawEmptyBoard(board);
        } else {
            drawBoard();
            cout << "\n";
        }
        cout << playerTurn(nextMove);
        cout << "Introdu numarul liniei: ";
        cin >> line;
        cout << "Introdu numarul coloanei: ";
        cin >> column;
        markBoard(player, line, column);
        if (checkWinner(player)) {
            drawBoard();
            cout << "Jucatorul " << player << " a castigat 🎉\n";
            restartGame(finishGame, moves, nextMove);
        } else if (moves == MAX_MOVES) {
            drawBoard();
            cout << "Jocul s-a terminat la egalitate! 🤝\n";
            restartGame(finishGame, moves, nextMove);
        }
        cout << "\n";
        player = nextMove;
        ++moves;
    }
    
    return 0;
}
