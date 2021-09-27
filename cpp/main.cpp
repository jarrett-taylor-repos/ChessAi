#include "chessboard.cpp"

int main() {
    cout << "Chess AI" << endl;

    //TEST getAllMoves(), pending
    ChessBoard board;
    board.printBoard();
    //vector<pair<stringSquare, stringSquare>> allmoves = board.getAllMoves();
    // cout << "Number of moves =  " <<  allmoves.size() << endl;
    // for(int i = 0; i < allmoves.size(); i++) {
    //     cout << "move " << (i+1) << ": " << allmoves[i].first << allmoves[i].second << endl;
    // }
    // for(int j = 0; j < 8; j++) {
    //     Square* testsq = board.getSquare(j, 6); //i, 6 for white pawns
    //     vector<pair<int, int>> testpawns = board.getPawns(testsq);
    //     cout << testsq->getColor() << " " << testsq->getPiece() << " at " << j << ", " << 6 << " or " << board.getStringSquare(j, 6) << endl;
    //     for(int i = 0; i < testpawns.size(); i++) {
    //         int tempx = testpawns[i].first;
    //         int tempy = testpawns[i].second;
    //         cout << "test move " << (i+1) << ": " << tempx << ", "<< tempy << " or " << board.getStringSquare(tempx, tempy) <<endl;
    //     }
    // }
    // for(int j = 0; j < 8; j++) {
    //     Square* testsq = board.getSquare(j, 1); //i, 6 for white pawns
    //     vector<pair<int, int>> testpawns = board.getPawns(testsq);
    //     cout << testsq->getColor() << " " << testsq->getPiece() << " at " << j << ", " << 6 << " or " << board.getStringSquare(j, 1) << endl;
    //     for(int i = 0; i < testpawns.size(); i++) {
    //         int tempx = testpawns[i].first;
    //         int tempy = testpawns[i].second;
    //         cout << "     " << tempx << ", "<< tempy << " or " << board.getStringSquare(tempx, tempy) <<endl;
    //     }
    // }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Square* testsq = board.getSquare(j, i);
            if(testsq->getPiece() != EMPTY) {
                vector<pair<int, int>> testpieces = board.returnPieceMoves(testsq);
                cout << testsq->getColor() << " " << testsq->getPiece() << " at " << board.getStringSquare(j, i) << endl;
                if(testpieces.size() != 0) {
                    cout << "    ->";
                }
                for(int i = 0; i < testpieces.size(); i++) {
                    int tempx = testpieces[i].first;
                    int tempy = testpieces[i].second;
                    if(testpieces.size()-1 > i) {
                        cout << board.getStringSquare(tempx, tempy) << ", ";
                    } else {
                        cout << board.getStringSquare(tempx, tempy) << endl;
                    }
                }
            }
        }
    }
    return 0;



    //  NEEDS
    //need en-passant, DONE W/ OUT CHECK
    //need castle, DONE W/ OUT CHECK
    //need concept of check and checkmate
    //need 3 repition rule
    //need 50 move rule
    //need stalemate
    //promotion of pawn, DONE W/ OUT CHECK


    // useful functions to make, 
    //    -get fen, DONE 
    //    -list of fens after each move
    //    -getAllMoves(), pending
    //      -canKingBeCapturedNextMove()
}