#include <iostream>
#include <algorithm>
#include "Board.h"

using namespace std;

int main() {
    int mark;
    bool gameOver = false;

    cout << "            Tic-Tac-Toe" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Choose your mark: O -> 0 , X -> 1: ";
    cin >> mark;
    cout << endl;

    while (!gameOver) {
        Board b(mark);         //ENTER OPPONENTS MARK OF CHOICE  1== X , 0 == O
        while (b.checkWinner() != -1 || b.checkWinner() != -2) {
            b.drawBoard();
            cout << endl << "Choose a move![1-9] :";
            cin >> mark;
            cout << endl;
            b.playMove(mark, OPPONENT);
            if (b.checkWinner() == -2) {
                b.announceResults();
                break;
            }
            b.playMove(b.findMove(), ME);

        }
        b.announceResults();
        gameOver = b.promptRematch();

    }
    cout << "Press any key to exit.." << endl;
    cin >> mark;
    return 0;
}