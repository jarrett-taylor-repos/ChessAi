#include "chessboard.cpp"


int main() {
    cout << "Chess AI" << endl;


    //test new check idea and cant make move that is out of check, working i think
    ChessBoard cb;
    cb.makeMove(e2, e3);
    cb.makeMove(f7, f5);
    cb.makeMove(d1, h5); //black in check, bishop working
    cb.printBoard();
    //cb.makeMove(g8, f6); //says cant make this move
    cb.makeMove(g7, g6); //only legal move
    cb.printBoard();    

    // cb.makeMove(f2, f3);
    // cb.makeMove(e7, e6);
    // cb.makeMove(a2, a3);
    // cb.makeMove(d8, h4); //white in check, bishop working
    // cb.printBoard();

    // vector<pair<stringSquare, stringSquare>> legalmoves = cb.getallLegalMoves();  //workign
    // cout << legalmoves.size() << endl;
    // for(int i = 0; i < legalmoves.size(); i++) {
    //     cout << legalmoves[i].first << legalmoves[i].second << endl;
    // }
    



    return 0;



    //  NEEDS
    //need en-passant, DONE W/ OUT CHECK
    //need castle, DONE W/ OUT CHECK
    //need concept of check and checkmate, pending
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