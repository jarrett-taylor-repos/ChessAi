#include "Board.cpp"

void testBoardPos(string s) {
    Board test(s);
    test.print();
    vector<pair<Notation, Notation>> notmoves = test.returnNotationMoves();
    cout << notmoves.size() << endl;
    for(int i = 0; i < notmoves.size(); i++) {
        cout << notmoves[i].first << notmoves[i].second << endl;
    }
}


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
    // Board b(promotest);
    // b.print();
    // b.makeMoveAndPrint(b7, c8Q);
    // cout << b.getPGN() << endl;

    // string testfen = "rnbq1rk1/pp2ppbp/2p2np1/3p4/2PP4/5NP1/PP2PPBP/RNBQ1RK1 w - - 0 7";
    // b.loadFEN(testfen);
    // b.makeMoveAndPrint(c4, d5);
    // b.makeMoveAndPrint(c6, d5);

    // string testcheckmoves = "rnbqkbnr/1ppp1ppp/p7/P3R2P/8/1PN5/2PPPPP1/2BQKBNR b Kk - 0 11";
    // testBoardPos(testcheckmoves);

    // string testcheckmoves2 = "8/rp1b1kbp/5np1/4Q3/4P2P/2rK1P2/1qP3P1/3R3R w - - 0 20";
    // testBoardPos(testcheckmoves2);

    // string testcheck3 = "2b1k1nr/2r2qpp/n2p4/6B1/Qp2P3/4RN2/5PPP/1N2K2R b Kk - 1 21";
    // testBoardPos(testcheck3);
    
    // string testcheck4 = "rnb1k1nr/pppp1ppp/8/4N3/Nb1qp3/8/PPPP1KPP/R1BQ3R w kq - 2 9";//bishop type
    // testBoardPos(testcheck4);


    // string testcheck5 = "rnQ1kb1r/1p1npp1p/3p4/p2P2P1/1q6/3RB3/6PP/2K2BNR b k - 0 26";
    // testBoardPos(testcheck5);

    // string testmoves = "rn1q1rk1/2ppbppp/pp6/3b4/8/1Q3NP1/PP2PPBP/R1B2RK1 b - - 1 12";
    // testBoardPos(testmoves);

    // string testpinmoves2 = "rnbqkbnr/pppppppp/4b3/8/8/4R3/PPPPPPPP/RNBQKBNR b KQkq - 0 1";
    // testBoardPos(testpinmoves2);

    // string impossiblemoves = "rnb2b1r/1p1nkpp1/3pq3/p7/P1PP3p/8/1PBBQPPP/R3K1NR b KQ - 4 14";
    // testBoardPos(impossiblemoves);

    // string impMove2 = "rn2Qk1r/ppq1bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R b KQ - 2 9";
    // testBoardPos(impMove2);

    // string impMove3 = "rnQ2k1r/ppq1bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 9";
    // testBoardPos(impMove3);

    // string impMove4 = "rnQq1k1r/pp2bppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R b KQ - 0 8";
    // testBoardPos(impMove4);

    // string vectorTest = "2rqkbnr/1bpppppp/1pn5/p7/2P1P1P1/N4P2/PP1P3P/R1BQKBNR w KQk - 3 6";
    // testBoardPos(vectorTest);

    // string testmate = "rnbqkbnr/ppppp2p/8/5ppQ/2P5/4P3/PP1P1PPP/RNB1KBNR b KQkq - 1 3";
    // testBoardPos(impMove5);

    // string impMove5 = "2qk1bnr/r1pbnp1p/p1pp2p1/8/4P2P/P1NN1P2/1PPP2P1/1RBQK2R b K - 2 12";
    // testBoardPos(impMove5);

    // string samtest = "8/3P1b2/1R3r2/3k3p/7P/2K1N3/1R3np1/8 b - - 4 72";
    // testBoardPos(samtest);

    // string samtest2 = "3rnk1r/2b2b2/4Pn2/1P5p/P2q1pPP/R2Q4/2R5/3K4 w - - 0 45";
    // testBoardPos(samtest2);

    // string samtest3= "4n3/8/1k6/5r2/7p/K7/8/1q6 w - - 2 69";
    // testBoardPos(samtest3);

    // string testEnpassantDiscoveredCheck = "knbqrbnr/ppp2ppp/8/3pP3/8/8/PPPP2PP/RNBQKBNR w KQ d6 0 1";
    // testBoardPos(testEnpassantDiscoveredCheck);

    // string testEnpassantNotDiscoveredCheck = "4k3/8/8/KppP3r/8/8/8/8 w - c6 0 1";
    // testBoardPos(testEnpassantNotDiscoveredCheck);

    // string testEnpassantISDiscoveredCheck = "4k3/8/8/K1pP3r/8/8/8/8 w - c6 0 1";
    // testBoardPos(testEnpassantISDiscoveredCheck);

    // string testPieceNotPinned = "5k2/4r3/8/8/8/4R3/4P3/4K3 w - - 0 1";
    // testBoardPos(testPieceNotPinned);

    // string testPiecePinned = "5k2/4r3/8/8/8/4R3/8/4K3 w - - 0 1";
    // testBoardPos(testPiecePinned);

    // string testEnpassantISDiscoveredCheck = "8/8/8/8/R2Pp2k/8/3K4/8 b - d3 0 1";
    // testBoardPos(testEnpassantISDiscoveredCheck);

    // string testEnpassantNotDiscoveredCheck = "8/8/8/8/R2Ppp1k/8/3K4/8 b - d3 0 1";
    // testBoardPos(testEnpassantNotDiscoveredCheck);



    //from code
    // string testFailedPos1_enpassant = "rnbqkbnr/2pppppp/p7/Pp6/8/8/1PPPPPPP/RNBQKBNR w KQkq b6 0 3"; //got 21 need 22
    // testBoardPos(testFailedPos1_enpassant);

    // string testFailedPos2_thinksKnightIsBishop = "rnbqkb1r/pppppppp/8/8/6n1/5P2/PPPPPKPP/RNBQ1BNR w kq - 3 3";
    // testBoardPos(testFailedPos2_thinksKnightIsBishop);

    // string testFailedPos2_thinksKnightIsBishop2 = "rnbqkb1r/pppppppp/8/8/5Pn1/8/PPPPPKPP/RNBQ1BNR w kq - 3 3";
    // testBoardPos(testFailedPos2_thinksKnightIsBishop2);

    // string testFailedPos2_tooManyMoves = "rnbqkbnr/2pppppp/pP6/8/8/8/1PPPPPPP/RNBQKBNR b KQkq - 0 3";
    // testBoardPos(testFailedPos2_tooManyMoves);

    // string testFailedPos_tooManyMoves2 = "rnbqkbnr/p1pp1ppp/1P6/4p3/8/8/PP1PPPPP/RNBQKBNR b KQkq - 0 3";
    // testBoardPos(testFailedPos_tooManyMoves2);

    // string testFailedPos_tooManyMoves3 = "rnbqkbnr/pppp1p1p/6P1/4p3/8/8/PPPPP1PP/RNBQKBNR b KQkq - 0 3";
    // testBoardPos(testFailedPos_tooManyMoves3);

    string doublechecktest = "1q3Nnr/r2kp1p1/6Q1/np1P1B1p/5P2/1P4P1/3P3P/1RB1K1NR b K - 0 23";
    testBoardPos(doublechecktest);
    return 0;
}