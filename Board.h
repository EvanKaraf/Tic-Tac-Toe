//
// Created by EvanKaraf on 1/10/2016.
//

#ifndef TIC_TAC_TOE_BOARD_H
#define TIC_TAC_TOE_BOARD_H

#define ME 0
#define OPPONENT 1

typedef struct move {
    int move;
    int value;
} MOVE;

class Board {
private:
    int me;
    int opponent;
    int b[10];

    int evaluateMove();

    MOVE negamax(int depth, int player);  // -1 Stands for PC and 1 stands for player.

public:

    Board(int choice);

    void drawBoard();

    void playMove(int move, int player);

    int checkWinner();

    int findMove();

    void announceResults();

    bool promptRematch();

};

#endif //TIC_TAC_TOE_BOARD_H
