#include "Board.cpp"



int main() {
    //Board b;
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
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }
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

    // string testfen = "rnbq1rk1/pp2ppbp/2p2np1/3p4/2PP4/5NP1/PP2PPBP/RNBQ1RK1 w - - 0 7";
    // b.loadFEN(testfen);
    // b.makeMoveAndPrint(c4, d5);
    // b.makeMoveAndPrint(c6, d5);

    // string testcheckmoves = "rnbqkbnr/1ppp1ppp/p7/P3R2P/8/1PN5/2PPPPP1/2BQKBNR b Kk - 0 11";
    // b.loadFEN(testcheckmoves);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string testcheckmoves2 = "8/rp1b1kbp/5np1/4Q3/4P2P/2rK1P2/1qP3P1/3R3R w - - 0 20";
    // b.loadFEN(testcheckmoves2);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string testcheck3 = "2b1k1nr/2r2qpp/n2p4/6B1/Qp2P3/4RN2/5PPP/1N2K2R b Kk - 1 21";
    // b.loadFEN(testcheck3);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }
    
    // string testcheck4 = "rnb1k1nr/pppp1ppp/8/4N3/Nb1qp3/8/PPPP1KPP/R1BQ3R w kq - 2 9";//bishop type
    // b.loadFEN(testcheck4);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string testcheck5 = "rnQ1kb1r/1p1npp1p/3p4/p2P2P1/1q6/3RB3/6PP/2K2BNR b k - 0 26";
    // b.loadFEN(testcheck5);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string testmoves = "rn1q1rk1/2ppbppp/pp6/3b4/8/1Q3NP1/PP2PPBP/R1B2RK1 b - - 1 12";
    // b.loadFEN(testmoves);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string testpinmoves2 = "rnbqkbnr/pppppppp/4b3/8/8/4R3/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    // b.loadFEN(testpinmoves2);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string impossiblemoves = "rnb2b1r/1p1nkpp1/3pq3/p7/P1PP3p/8/1PBBQPPP/R3K1NR b KQ - 4 14";
    // b.loadFEN(impossiblemoves);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // cout << notmoves.size() << endl;
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string impMove2 = "rn2Qk1r/ppq1bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R b KQ - 2 9";
    // b.loadFEN(impMove2);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // cout << notmoves.size() << endl;
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string impMove3 = "rnQ2k1r/ppq1bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 9";
    // b.loadFEN(impMove3);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    // cout << notmoves.size() << endl;
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    // string impMove4 = "rnQq1k1r/pp2bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R b KQ - 0 8";
    // Board b(impMove4);
    // b.print();
    // vector<pair<Notation, Notation>> notmoves = b.returnNotationMoves();
    // cout << notmoves.size() << endl;
    // for(int i = 0; i < notmoves.size(); i++) {
    //     cout << notmoves[i].first << notmoves[i].second << endl;
    // }

    string vectorTest = "2rqkbnr/1bpppppp/1pn5/p7/2P1P1P1/N4P2/PP1P3P/R1BQKBNR w KQk - 3 6";
    Board b(vectorTest);
    b.print();
    vector<pair<Notation, Notation>> notmoves = b.returnNotationMoves();
    cout << notmoves.size() << endl;
    for(int i = 0; i < notmoves.size(); i++) {
        cout << notmoves[i].first << notmoves[i].second << endl;
    }
    return 0;
}