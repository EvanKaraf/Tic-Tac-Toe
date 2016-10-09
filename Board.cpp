//
// Created by EvanKaraf on 1/10/2016.
//

#include <algorithm>
#include "Board.h"
#include "iostream"

using namespace std;

int INITIAL_DEPTH;

Board::Board(int choice) {      //ENTER OPPONENTS MARK OF CHOICE  1== X , 0 == O
    if (choice == 0) {
        this->me = 1;
        this->opponent = 0;
    } else {
        this->me = 0;
        this->opponent = 1;
    }

    for (int i = 0; i < 10; i++) {
        b[i] = -1;
    }
}

void Board::drawBoard() {
    string str[5];
    int countRows = 0;
    str[0] = "   |   |   ";
    str[1] = "-----------";
    str[2] = "   |   |   ";
    str[3] = "-----------";
    str[4] = "   |   |   ";

    for (int i = 0; i < 5; i += 2) {
        for (int j = 1; j < 11; j += 4) {
            switch (b[countRows + 1]) {
                case -1 :
                    str[i][j] = ' ';
                    break;
                case 0:
                    str[i][j] = 'O';
                    break;
                case 1:
                    str[i][j] = 'X';
                    break;
                default:
                    break;
            }
            countRows++;
        }
    }
    for (int i = 0; i < 5; i++) {
        cout << str[i] << endl;
    }

}

void Board::playMove(int move, int player) {
    if (player == -1)
        player = 0;
    if (move < 1 || move > 9 || b[move] != -1) {
        cout << "Invalid move try again" << endl;
        return;
    }
    if (player == ME)
        b[move] = this->me;
    else
        b[move] = this->opponent;


}

int Board::checkWinner() {
    int winRow = -1;
    for (int i = 0; i < 9; i = i + 3) {
        if ((b[i + 1] == b[i + 2]) && (b[i + 1] == b[i + 3]) && b[i + 1] != -1)
            winRow = i + 1;
    }
    for (int i = 0; i < 3; i++) {
        if ((b[i + 1] == b[i + 4]) && (b[i + 1] == b[i + 7]) && b[i + 1] != -1)
            winRow = i + 1;
    }
    if ((b[1] == b[5]) && (b[1] == b[9]) && b[1] != -1)
        winRow = 1;
    else if ((b[3] == b[5]) && (b[3] == b[7]) && b[3] != -1) {
        winRow = 3;
    }

    if (winRow != -1) {
        if (b[winRow] == this->me)
            return ME;
        else
            return OPPONENT;
    } else {
        for (int i = 1; i < 10; i++) {
            if (b[i] == -1)
                return -1;
        }
        return -2;
    }
}

int Board::evaluateMove() {
    int winner = checkWinner();
    if (winner == ME)
        return 10;
    else if (winner == OPPONENT)
        return -10;
    else {
        return 0;
    }
}

MOVE Board::negamax(int depth, int player) {
    MOVE tempMove;
    MOVE bestMove;

    if (checkWinner() != -1 || depth == 0) {
        tempMove.value = -(player * evaluateMove());
        return tempMove;
    }

    bestMove.value = -20;
    bestMove.move = -1;

    for (int i = 1; i < 10; i++) {
        if (b[i] == -1) {
            playMove(i, player);

            tempMove.value = -(negamax(depth - 1, -player).value);
            if (tempMove.value > bestMove.value) {
                bestMove.value = tempMove.value;
                bestMove.move = i;
            }
            b[i] = -1;

        }
    }
    return bestMove;

}

int Board::findMove() {
    MOVE best;
    INITIAL_DEPTH = 7;
    best = negamax(INITIAL_DEPTH, -1); //MAXIMIZING
    return best.move;
}

void Board::announceResults() {
    this->drawBoard();
    cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    switch (checkWinner()) {
        case ME:
            cout << "  You just lost." << endl;
            break;
        case OPPONENT:
            cout << "  You just did an incredible feat. You won!!" << endl;
            break;
        case -2:
            cout << "  It's a tie..." << endl;
            break;
        default:
            return;
    }
    cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

bool Board::promptRematch() {
    string answer;
    cout << "Do you want a rematch?  Y/N:";
    cin >> answer;
    transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
    return answer == "NO" || answer == "N";
}

