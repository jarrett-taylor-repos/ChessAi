#include "Square.cpp"

class ChessBoard {
    private:
        Square board[8][8];
        bool canWhiteCastleShort;
        bool canWhiteCastleLong;
        bool canBlackCastleShort;
        bool canBlackCastleLong;
        Color moveColor;

    public:
        ChessBoard();

        string getFen();

        void Move(Notation start, Notation end);

        //need all functions to get possible moves of pieces
        //need ability to see if check 
        bool canMoveCaptureLogic(Square* item, int tempx, int tempy);
        bool canCastleShort();
        bool canCastleLong();

        pair<int, int> movetHelper(int tempx, int tempy, Square* sq);
        vector<pair<int, int>> kingMoves(Square* king);
        vector<pair<int, int>> queenMoves(Square* king);
        vector<pair<int, int>> rookMoves(Square* king);
        vector<pair<int, int>> bishopMoves(Square* king);
        vector<pair<int, int>> knightMoves(Square* king);
        vector<pair<int, int>> pawnMoves(Square* king);


        Square* getSquare(Piece p, Color c);
        Square* getSquare(Notation strsq);
        Square* getSquare(int x, int y);
        Notation getNotation(int x, int y);

        Color getTurnColor();
        void nextTurnColor();


        void printBoard();
};

ChessBoard::ChessBoard() {
    canWhiteCastleShort = false;
    canWhiteCastleLong = false;
    canBlackCastleShort = false;
    canBlackCastleLong = false;
    moveColor = WHITE;

    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            board[y][x].setPieceandColor(EMPTY, NONE);
            board[y][x].setxy(y, x);
        }
    }

    board[0][0].setPieceandColor(ROOK, BLACK);
    board[1][0].setPieceandColor(KNIGHT, BLACK);
    board[2][0].setPieceandColor(BISHOP, BLACK);
    board[3][0].setPieceandColor(QUEEN, BLACK);
    board[4][0].setPieceandColor(KING, BLACK);
    board[5][0].setPieceandColor(BISHOP, BLACK);
    board[6][0].setPieceandColor(KNIGHT, BLACK);
    board[7][0].setPieceandColor(ROOK, BLACK);

    board[0][7].setPieceandColor(ROOK, WHITE);
    board[1][7].setPieceandColor(KNIGHT, WHITE);
    board[2][7].setPieceandColor(BISHOP, WHITE);
    board[3][7].setPieceandColor(QUEEN, WHITE);
    board[4][7].setPieceandColor(KING, WHITE);
    board[5][7].setPieceandColor(BISHOP, WHITE);
    board[6][7].setPieceandColor(KNIGHT, WHITE);
    board[7][7].setPieceandColor(ROOK, WHITE);

    for (int i = 0; i < 8; i++) {
        board[i][1].setPieceandColor(PAWN, BLACK);
        board[i][6].setPieceandColor(PAWN, WHITE);
    }

}


void ChessBoard::Move(Notation start, Notation end) {
    
    nextTurnColor();
}

bool ChessBoard::canMoveCaptureLogic(Square* start, int tempx, int tempy) { //does not implement individual piece logic, just mechanics of capture rules
    bool canMove = false;
    
    if(start->getColor() != NONE && start->getPiece() != EMPTY) { //must be a colored piece 
        Square* temp = getSquare(tempx, tempy);
        if(temp->getColor() == start->getColor()) { //can capture same color
            canMove = false;
        } else if (temp->getColor() != start->getColor() && temp->getColor() != NONE) { //opposite color detection
            canMove = true;
        } else { //no piece is here
            canMove = true;
        }
    }
    return canMove;
}


bool ChessBoard::canCastleShort() {
    if(moveColor == WHITE) {
        Square* wKing = getSquare(KING, WHITE);
        if() {

        }
    }
}
bool ChessBoard::canCastleLong() {
    
}

pair<int, int> ChessBoard::movetHelper(int tempx, int tempy, Square* sq) {
    pair<int, int> p = make_pair(int(), int());
    if(isInRange(tempx, tempy)) {
        if(canMoveCaptureLogic(sq, tempx, tempy)) {
            pair<int, int> temppair = make_pair(tempx, tempy);
            p=temppair;
        }
    } 
    return p;
}

vector<pair<int, int>> ChessBoard::kingMoves(Square* king) {
    vector<pair<int, int>> kings;
    int x = king->getx();
    int y = king->gety();

    vector<pair<int, int>> pairs;
    pairs.push_back(make_pair(-1, -1));
    pairs.push_back(make_pair(-1, 0));
    pairs.push_back(make_pair(-1, 1));
    pairs.push_back(make_pair(0, -1));
    pairs.push_back(make_pair(0, 1));
    pairs.push_back(make_pair(1, -1));
    pairs.push_back(make_pair(1, 0));
    pairs.push_back(make_pair(1, 1));

    //castling stuff
    // if(canCastleShort()) {
    //    pairs.push_back(make_pair(2, 0));
    // }
    // if(canCastleLong()) {
    //    pairs.push_back(make_pair(-2, 0));
    // }

    for(int i = 0; i < pairs.size(); i++) {
        pair<int, int> temp = movetHelper(x+pairs[i].first, y+pairs[i].second, king);
    }

    return;
}


Square* ChessBoard::getSquare(Piece p, Color c) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Square* temp = getSquare(i, j);
            if(temp->getColor() == c && temp->getPiece() == p) {
                return temp;
            }
        }
    }
}

Square* ChessBoard::getSquare(int x, int y) {
    return &board[x][y];
}

Square* ChessBoard::getSquare(Notation strsq) {
    int x, y = -1;
    switch(strsq) {
        case a1: x=0; y=7;break;
        case a2: x=0; y=6;break;
        case a3: x=0; y=5;break;
        case a4: x=0; y=4;break;
        case a5: x=0; y=3;break;
        case a6: x=0; y=2;break;
        case a7: x=0; y=1;break;
        case a8: x=0; y=0;break;
        case b1: x=1; y=7;break;
        case b2: x=1; y=6;break;
        case b3: x=1; y=5;break;
        case b4: x=1; y=4;break;
        case b5: x=1; y=3;break;
        case b6: x=1; y=2;break;
        case b7: x=1; y=1;break;
        case b8: x=1; y=0;break;
        case c1: x=2; y=7;break;
        case c2: x=2; y=6;break;
        case c3: x=2; y=5;break;
        case c4: x=2; y=4;break;
        case c5: x=2; y=3;break;
        case c6: x=2; y=2;break;
        case c7: x=2; y=1;break;
        case c8: x=2; y=0;break;
        case d1: x=3; y=7;break;
        case d2: x=3; y=6;break;
        case d3: x=3; y=5;break;
        case d4: x=3; y=4;break;
        case d5: x=3; y=3;break;
        case d6: x=3; y=2;break;
        case d7: x=3; y=1;break;
        case d8: x=3; y=0;break;
        case e1: x=4; y=7;break;
        case e2: x=4; y=6;break;
        case e3: x=4; y=5;break;
        case e4: x=4; y=4;break;
        case e5: x=4; y=3;break;
        case e6: x=4; y=2;break;
        case e7: x=4; y=1;break;
        case e8: x=4; y=0;break;
        case f1: x=5; y=7;break;
        case f2: x=5; y=6;break;
        case f3: x=5; y=5;break;
        case f4: x=5; y=4;break;
        case f5: x=5; y=3;break;
        case f6: x=5; y=2;break;
        case f7: x=5; y=1;break;
        case f8: x=5; y=0;break;
        case g1: x=6; y=7;break;
        case g2: x=6; y=6;break;
        case g3: x=6; y=5;break;
        case g4: x=6; y=4;break;
        case g5: x=6; y=3;break;
        case g6: x=6; y=2;break;
        case g7: x=6; y=1;break;
        case g8: x=6; y=0;break;
        case h1: x=7; y=7;break;
        case h2: x=7; y=6;break;
        case h3: x=7; y=5;break;
        case h4: x=7; y=4;break;
        case h5: x=7; y=3;break;
        case h6: x=7; y=2;break;
        case h7: x=7; y=1;break;
        case h8: x=7; y=0;break;
    }
    Square* sq = getSquare(x, y);
    return sq;
}

Notation ChessBoard::getNotation(int x, int y) {
    int value = x*8 + y;
    Notation s= MOVE;
    switch(value){
        case 0: s= a8; break;
        case 1: s= a7; break;
        case 2: s= a6; break;
        case 3: s= a5; break;
        case 4: s= a4; break;
        case 5: s= a3; break;
        case 6: s= a2; break;
        case 7: s= a1; break;
        case 8: s= b8; break;
        case 9: s= b7; break;
        case 10: s= b6; break;
        case 11: s= b5; break;
        case 12: s= b4; break;
        case 13: s= b3; break;
        case 14: s= b2; break;
        case 15: s= b1; break;
        case 16: s= c8; break;
        case 17: s= c7; break;
        case 18: s= c6; break;
        case 19: s= c5; break;
        case 20: s= c4; break;
        case 21: s= c3; break;
        case 22: s= c2; break;
        case 23: s= c1; break;
        case 24: s= d8; break;
        case 25: s= d7; break;
        case 26: s= d6; break;
        case 27: s= d5; break;
        case 28: s= d4; break;
        case 29: s= d3; break;
        case 30: s= d2; break;
        case 31: s= d1; break;
        case 32: s= e8; break;
        case 33: s= e7; break;
        case 34: s= e6; break;
        case 35: s= e5; break;
        case 36: s= e4; break;
        case 37: s= e3; break;
        case 38: s= e2; break;
        case 39: s= e1; break;
        case 40: s= f8; break;
        case 41: s= f7; break;
        case 42: s= f6; break;
        case 43: s= f5; break;
        case 44: s= f4; break;
        case 45: s= f3; break;
        case 46: s= f2; break;
        case 47: s= f1; break;
        case 48: s= g8; break;
        case 49: s= g7; break;
        case 50: s= g6; break;
        case 51: s= g5; break;
        case 52: s= g4; break;
        case 53: s= g3; break;
        case 54: s= g2; break;
        case 55: s= g1; break;
        case 56: s= h8; break;
        case 57: s= h7; break;
        case 58: s= h6; break;
        case 59: s= h5; break;
        case 60: s= h4; break;
        case 61: s= h3; break;
        case 62: s= h2; break;
        case 63: s= h1; break;
    }
    return s;
}

Color ChessBoard::getTurnColor() {
    return moveColor;
}

void ChessBoard::nextTurnColor() {
    if(moveColor == WHITE) {
        moveColor == BLACK;
    } else {
        moveColor == WHITE;
    }
}

void ChessBoard::printBoard() {
    cout <<"-------------"<< endl;
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            cout << board[x][y].getPrint();
        }
        cout << endl;
    }
    cout <<"-------------"<< endl << endl;
}