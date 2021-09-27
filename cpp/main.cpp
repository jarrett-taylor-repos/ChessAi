#include "chessboard.cpp"

int main() {
    cout << "Chess AI" << endl;

    //TEST getAllMoves(), WORKING??
    ChessBoard board;
    board.printBoard();
    vector<pair<stringSquare, stringSquare>> allmoves = board.getAllMoves();
    cout << "Number of moves =  " <<  allmoves.size() << endl;
    for(int i = 0; i < allmoves.size(); i++) {
        cout << "move " << (i+1) << ": " << allmoves[i].first << allmoves[i].second << endl;
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