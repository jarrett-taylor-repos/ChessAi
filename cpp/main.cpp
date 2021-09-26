#include "chessboard.cpp"

int main() {
    cout << "Chess AI" << endl;

    //TEST ENPASSANT, WORKING
    //white and black should pass, WORKING
    ChessBoard board;
    board.printBoard();
    board.makeMove(g2, g4);
    board.makeMove(e7, e6);
    board.makeMove(g4, g5);
    board.makeMove(f7, f5);
    board.printBoard();
    board.makeMove(g5, f6); //en passant white
    board.printBoard();
    board.makeMove(d7, d5);
    board.makeMove(f2, f3);
    board.makeMove(d5, d4);
    board.makeMove(e2, e4);
    board.printBoard();
    board.makeMove(d4, e3); //en passant black
    board.printBoard();
    return 0;


    //  NEEDS
    //need en-passant, DONE W/ OUT CHECK
    //need castle, DONE W/ OUT CHECK
    //need concept of check and checkmate
    //need 3 repition rule
    //need 50 move rule
    //need stalemate
    //promotion of pawn


    // useful functions to make, 
    //    -all possible legal moves
    //    -get fen, DONE 
    //    -list of fens after each move
    //    -getAllMoves()
    //      -canKingBeCapturedNextMove()
}