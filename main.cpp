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
string currentPlayer = PLAYER_1;

//winning pairs array
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

//Shows game rules
void gameRules() {
    cout << "Regulile jocului:" << "\n";
    cout << "Primul jucator care obtine 3 de X/0 pe coloana/linie/diagonala castiga" << "\n";
    cout << "Pentru linie/coloana poti introduce valori doar intre 1-3 inclusiv" << "\n";
    cout << "Daca spatiul este ocupat trebuie sa introduci niste valori valide pentru o pozitie goala" << "\n";
    cout << "Jucatorul 1 - " << PLAYER_1 << "\n";
    cout << "Jucatorul 2 - " << PLAYER_2 << "\n";
}

//Creates empty game board
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

//Handles player turn
string playerTurn(string &player) {
    if (player == PLAYER_1) {
        player = PLAYER_2;
        return "Este randul Jucatorului 1 - ❌\n";
    } else {
        player = PLAYER_1;
        return "Este randul Jucatorului 2 - 🅾️\n";
    }
}

//Checks if a board position is empty.
bool isOccupied(int line, int column) {
    if (board[line][column] == EMPTY_SPACE) {
        return true;
    }
    return false;
}

//Marks board with either X or 0;
void markBoard(string player, int line, int column) {
    if (line >= 1 && line <= BOARD_LENGTH &&
        column >= 1 && column <= BOARD_LENGTH) {
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
        cout << "Nu ai introdus o pozitie existenta pe tabla de joc\n";
        cout << "Reintrodu linia: ";
        cin >> line;
        cout << "Reintrodu coloana: ";
        cin >> column;
        markBoard(player, line, column);
    }
}

//Verifies if someone won
bool checkWinner(string player) {
    for (const auto winCombo : winningCases) {
        if (board[winCombo[0].first][winCombo[0].second] == player &&
            board[winCombo[1].first][winCombo[1].second] == player &&
            board[winCombo[2].first][winCombo[2].second] == player) {
            return true;
        }
    }
    return false;
}

//Shows current state of the game board
void drawBoard() {
    for (int i = 1; i <= BOARD_LENGTH; ++i) {
        for (int j = 1; j <= BOARD_LENGTH; ++j) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

//Ends or restarts the game
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
    string nextPlayer = PLAYER_1;
    
    gameRules();
    
    while (!finishGame) {
        if (moves == 1) {
            drawEmptyBoard(board);
        } else {
            drawBoard();
            cout << "\n";
        }
        
        cout << playerTurn(nextPlayer);
        cout << "Introdu numarul liniei: ";
        cin >> line;
        cout << "Introdu numarul coloanei: ";
        cin >> column;
        
        markBoard(currentPlayer, line, column);
        
        if (checkWinner(currentPlayer)) {
            drawBoard();
            cout << "Jucatorul " << currentPlayer << " a castigat 🎉\n";
            restartGame(finishGame, moves, nextPlayer);
        } else if (moves == MAX_MOVES) {
            drawBoard();
            cout << "Jocul s-a terminat la egalitate! 🤝\n";
            restartGame(finishGame, moves, nextPlayer);
        }
        
        cout << "\n";
        currentPlayer = nextPlayer;
        ++moves;
    }
    
    cout << "Jocul s-a terminat!☠️\n";
    
    return 0;
}
