#include "chessboard.cpp"


int main() {
    cout << "Chess AI" << endl;

    //test if kingattacked, pending
    // bool incheck;
    // ChessBoard cb;
    // cb.printBoard();
    // cb.makeMove(e2, e4);
    // cb.makeMove(f7, f6);
    // cb.makeMove(d1, h5);
    // cb.printBoard();
    // incheck = cb.isKingAttacked();
    // if(incheck) { cout << "incheck" << endl;} else {cout << "not in check" << endl;}

    //test new check idea, pending
    ChessBoard cb;
    cb.printBoard();
    cb.makeMove(e2, e4);
    cb.makeMove(f7, f6);
    cb.makeMove(d1, h5);
    cb.printBoard();


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