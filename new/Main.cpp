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

    string promo = "rnbq1rk1/ppP1ppbp/5np1/8/8/5NP1/P1pPPPBP/RNBQ1RK1 w - - 0 9";
    b.loadFEN(promo);
    b.print();
    b.makeMoveAndPrint(c7, d8Q);
    b.makeMoveAndPrint(c2, d1q);
}