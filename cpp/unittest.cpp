#include "chessboard.cpp"

int main() {
    /*
        //TESTING FEN, WORKING
        string fen = "r3r1k1/pp3nPp/1b1p1B2/1q1P1N2/8/P4Q2/1P3PK1/R6R";
        cout << fen << endl;
        ChessBoard cb(fen);
        cb.printBoard();
    */

    /*
        //TESTING BOARD PRINT, WORKING
        ChessBoard p;
        p.printBoard();
    */

    /*
        //file rank unit test, WORKING
        for(int i = 0; i < 64; i ++) {
            vector<int> values = getFileRank(i);
            cout << "i, file, rank: " << i << ", " << values[0] << ", " << values[1] << endl;
        }
    */

    /*
        //GET PIECE LETTER AND COLOR UNIT TEST, WORKING
        string letters = "KQRBNPkqrbnpXx";
        for(int i = 0; i < letters.length(); i++) {
            char ch = letters[i];
            Piece p = getPieceByLetter(ch);
            Color c = getColorByLetter(ch);
            Square sq(p, c);
            sq.printSquare();
            cout << " " << ch <<endl;
        }
    */

    /*
        //TEST TO CHECK HORIZONTALS AND VERTICALS, WORKING
        vector<pair<int, int>> allrookmoves;
        string testr = "k1r5/8/1R6/8/8/8/8/7K";
        ChessBoard test(testr);
        test.printBoard();
        Square* sqtest = test.getSquare(2, 0); //test.getSquare(pos)
        cout << endl;
        allrookmoves = test.getVerticalsandHorizontals(sqtest);
        for(int i =0; i < allrookmoves.size(); i++) {
            cout << "move: " << allrookmoves[i].first << ", " << allrookmoves[i].second << endl;
        }
    */

    /*
        //TEST TO CHECK DIAGONALS, WORKING
        vector<pair<int, int>> allbishopmoves;
        string testb = "2K5/k7/8/8/3B4/8/8/8";
        ChessBoard testbb(testb);
        testbb.printBoard();
        Square* sqtestq = testbb.getSquare(3, 4); //test.getSquare(pos)
        cout << endl;
        allbishopmoves = testbb.getDiagonals(sqtestq);
        for(int i =0; i < allbishopmoves.size(); i++) {
            cout << "move: " << allbishopmoves[i].first << ", " << allbishopmoves[i].second << endl;
        }
    */

    /*
        //TEST ALL KING MOVES, WORKING
        vector<pair<int, int>> allkingmoves;
        string testking = "kr6/8/8/8/8/8/8/8";
        ChessBoard testingking(testking);
        testingking.printBoard();
        Square* sqtestking = testingking.getSquare(0, 0); //test.getSquare(pos)
        cout << endl;
        allkingmoves = testingking.getKings(sqtestking);
        for(int i =0; i < allkingmoves.size(); i++) {
            cout << "move: " << allkingmoves[i].first << ", " << allkingmoves[i].second << endl;
        }
    */

    /*
        //TEST ALL KNIGHT MOVES, WORKING
        vector<pair<int, int>> allknightmoves;
        string testknight = "8/2R5/8/3N4/8/8/8/8";
        ChessBoard testingknight(testknight);
        testingknight.printBoard();
        Square* sqknight = testingknight.getSquare(3, 3); //test.getSquare(pos)
        cout << endl;
        allknightmoves = testingknight.getKnights(sqknight);
        for(int i =0; i < allknightmoves.size(); i++) {
            cout << "move: " << allknightmoves[i].first << ", " << allknightmoves[i].second << endl;
        }
    */

    /*
        //TEST ALL PAWN MOVES, WORKING w/ out en-passant and promtion
        vector<pair<int, int>> allpawnmoves;
        string testpawn = "8/4p3/4q3/4Q3/8/8/8/8";
        ChessBoard testingpawn(testpawn);
        testingpawn.printBoard();
        Square* sqknight = testingpawn.getSquare(4, 1);
        cout << endl;
        allpawnmoves = testingpawn.getPawns(sqknight);
        for(int i =0; i < allpawnmoves.size(); i++) {
            cout << "move: " << allpawnmoves[i].first << ", " << allpawnmoves[i].second << endl;
        }
    */

    /*
        //TEST MAKE MOVE, WORKING
        string startfen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        ChessBoard board;
        board.printBoard();
        board.makeMove(d2, d4);
        board.printBoard();
        board.makeMove(d7, d5);
        board.printBoard();
        board.makeMove(c2, c4);
        board.printBoard();
        board.makeMove(d5, c4);
        board.printBoard();
        //TEST PRINT ALL MOVES, WORKING
        board.printAllMoves();
    */


    /*
        //TEST FEN GENERATOR, WORKING
        string testfen = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R";
        cout << testfen << endl;
        ChessBoard board(testfen);
        board.printBoard();
        string fen = board.getBoardFEN();
        cout << fen << endl;
    */

    /*
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
        //test castling long should pass, WORKING 
        ChessBoard board;
        board.printBoard();
        board.makeMove(b1, c3);
        board.makeMove(b8, c6);
        board.makeMove(d2, d3);
        board.makeMove(d7, d6);
        board.makeMove(c1, e3);
        board.makeMove(c8, e6);
        board.makeMove(d1, d2);
        board.makeMove(d8, d7);
        board.makeMove(e1, c1);
        board.printBoard();
        board.makeMove(e8, c8);
        board.printBoard();
        //test castling  should fail, WORKING
        ChessBoard board;
        board.printBoard();
        board.makeMove(g2, g3);
        board.makeMove(g7, g6);
        board.makeMove(f1, g2);
        board.makeMove(f8, g7);
        board.makeMove(g1, f3);
        board.makeMove(g8, f6);
        board.makeMove(h1, g1);
        board.makeMove(h8, g8);
        board.makeMove(g1, h1);
        board.makeMove(g8, h8);
        board.makeMove(e1, g1);//castle move
        board.printBoard();
    */

    /*
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
    */

    /* 
        //TEST PROMOTION, WORKING
        //white and black should pass, WORKING
        ChessBoard board;
        board.printBoard();
        board.makeMove(g2, g4);
        board.makeMove(e7, e6);
        board.makeMove(g4, g5);
        board.makeMove(f7, f5);
        board.makeMove(g5, f6); //en passant white
        board.makeMove(d7, d5);
        board.makeMove(f2, f3);
        board.makeMove(d5, d4);
        board.makeMove(e2, e4);
        board.makeMove(d4, e3); //en passant black
        board.makeMove(f6, g7);
        board.makeMove(e3, e2);
        board.printBoard();
        board.makeMove(g7, h8); //promotion for white
        board.printBoard();
        board.makeMove(e2, f1);//promotion for black
        board.printBoard();
    */

   
}