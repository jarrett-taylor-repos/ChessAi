#include "Board.cpp"



int main() {
    Board b;
    // b.makeMoveAndPrint(e2, e4);
    // b.makeMoveAndPrint(e7, e5);
    // b.makeMoveAndPrint(d1, f3);
    // b.makeMoveAndPrint(a7, a6);
    // b.makeMoveAndPrint(f1, c4);
    // b.makeMoveAndPrint(b8, c6);
    // b.makeMoveAndPrint(f3, f7);
    // b.makeMoveAndPrint(a8, b8);//should be checkmate
    // cout << b.getPGN() << endl;
    //print_map(b.getfenMap());

    // string pinnedmoves = "4k3/4r3/4Q3/8/8/3R1R2/8/4K3 b - - 0 1";
    // b.loadFEN(pinnedmoves);
    // b.print();
    // b.makeMoveAndPrint(e7, e6);

    // string enpassm = "rnbqkbnr/ppp2ppp/4p3/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
    // b.loadFEN(enpassm);
    // b.print();
    // b.makeMoveAndPrint(e5, d6);
    
    // string castle = "rnbqk2r/ppppppbp/5np1/8/8/5NP1/PPPPPPBP/RNBQK2R w KQkq - 4 4";
    // b.loadFEN(castle);
    // b.print();
    // b.makeMoveAndPrint(e1, g1);
    // b.makeMoveAndPrint(e8, g8);

    // string promo = "rnbq1rk1/ppP1ppbp/5np1/8/8/5NP1/P1pPPPBP/RNBQ1RK1 w - - 0 9";
    // b.loadFEN(promo);
    // b.print();
    // b.makeMoveAndPrint(c7, d8Q);
    // b.makeMoveAndPrint(c2, d1q);

    // string stalemate = "4k3/4p3/4Q3/3R1R2/8/8/PPPPPPPP/1NB1KBN1 b - - 0 1";
    // b.loadFEN(stalemate);
    // b.print();
    // b.makeMoveAndPrint(e8, d8);

    // string insuff = "4k3/8/5N2/8/8/8/8/4K3 b - - 0 1";
    // b.loadFEN(insuff);
    // b.print();
    // b.makeMoveAndPrint(e8, d8);

    // Board test;
    // test.loadFEN("rnbqkbnr/1ppppppp/p7/8/P7/8/1PPPPPPP/RNBQKBNR b KQkq - 0 2");
    // test.makeMoveAndPrint(d6, d5);

    // string enpassantPin = "8/8/3p4/KPp4r/1R3p1k/4P3/6P1/8 w - c6 0 1";//white enpassant pin
    // b.loadFEN(enpassantPin);
    // b.makeMoveAndPrint(b5, c6);//shouldnt make move

    // string enpassantPin ="8/8/2pp4/7r/R4Ppk/KP2P3/8/8 b - f3 0 1";//black enpassant pin
    // b.loadFEN(enpassantPin);
    // cout << b.makeMove(g4, f3) << endl;//shouldnt make move
    // b.print();

    // string promotest = "1nbqkbnr/rPpppppp/8/P7/8/2R5/2PPPPPP/1NBQKBNR w Kk - 1 13";
    // b.loadFEN(promotest);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    string testfen = "rnbq1rk1/pp2ppbp/2p2np1/3p4/2PP4/5NP1/PP2PPBP/RNBQ1RK1 w - - 0 7";
    b.loadFEN(testfen);
    b.makeMoveAndPrint(c4, d5);
    b.makeMoveAndPrint(c6, d5);



    
    
    return 0;
}