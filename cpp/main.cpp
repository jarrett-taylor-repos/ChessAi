#include "chessboard.cpp"

int main() {
    cout << "Chess AI" << endl;


    //TEST CASTLING, WORKING
    //test castling short should pass, WORKING 
    ChessBoard board;
    board.printBoard();
    board.makeMove(g2, g3);
    board.makeMove(g7, g6);
    board.makeMove(f1, g2);
    board.makeMove(f8, g7);
    board.makeMove(g1, f3);
    board.makeMove(g8, f6);
    board.makeMove(e1, g1);
    board.printBoard();
    board.makeMove(e8, g8);
    board.printBoard();
    return 0;


    //  NEEDS
    //need en-passant
    //need castle, NEED TO CHECK FOR CASTLE THROUGH CHECK AND INTO CHECK
    //need concept of check and checkmate
    //need 3 repition rule
    //need 50 move rule
    //need stalemate
    //promotion of pawn

    // useful functions to make, 
    //    -all possible legal moves
    //    -list of fens and number of times reached, HAVE FEN 
    //        -need an fen generator from board position
    //    -need to see if on next move if king can be taken, kingAttacked()?
}