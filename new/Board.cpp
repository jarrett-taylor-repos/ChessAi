#include "Square.cpp"

class Board {
    private:
        Square board[8][8];
        pair<Notation,Notation> moves[1000];
        int turnNum;
        Notation enpassantTarget;
        Color moveColor;
        bool wasCapture;
        bool wasPromo;
        bool wasCastle;
        int halfTurnNum;
        int fullTurnNum;
        bool wKQ_bkq[4]; //0 means cant castle
        

        unordered_map<string, int> fenMap;

        vector<pair<Square*, Square*>> vectorGetAllLegalMoves; 
        vector<pair<Notation, Notation>> vectorGetNotationMoves;        
    public:
        Board();
        void loadFEN(string fen);

        Color getMoveColor();
        vector<pair<Notation, Notation>> getAllMovesVector();
        unordered_map<string, int> getfenMap();
        void setfenMap(); 
        int getFenRepeat();
        bool getWasCapture();
        bool getWasPromo();
        bool getWasCastle();

        vector<bool> canWhiteCastle();
        vector<bool> canBlackCastle(); 

        void setMoveColor();

        Color Winner();
        bool isGameOver();
        bool isCheckmate();
        bool isDraw();
        bool repitionDraw();
        bool noForcedMateDraw();
        bool makeMove(Notation, Notation);
        void makeMoveAndPrint(Notation, Notation);


        vector<pair<Square*, Square*>> getAllMoves();
        pair<int, int> movetHelper(int tempx, int tempy, Square* sq);
        vector<pair<Square*, Square*>> getPieceMoves(Square*);
        vector<pair<Square*, Square*>> KingMoves(Square*);
        vector<pair<Square*, Square*>> QueenMoves(Square*);
        vector<pair<Square*, Square*>> RookMoves(Square*);
        vector<pair<Square*, Square*>> BishopMoves(Square*);
        vector<pair<Square*, Square*>> KnightMoves(Square*);
        vector<pair<Square*, Square*>> PawnMoves(Square*);

        vector<pair<int,int>> isBishopAttacker(Square*);
        vector<pair<int,int>> isRookAttacker(Square*);
        vector<pair<int,int>> isKnightAttacker(Square*);
        vector<pair<int,int>> isPawnAttacker(Square*);
        vector<pair<int,int>> isKingAttacker(Square*);
        vector<pair<int,int>> isSquareAttack(Square*);
        Square* getKing(Color);
        Piece getPawnPromotion(Notation);

        pair<bool, Square*> isBetweenKingandAttacker(Square*, Square*, Square*);
        vector<pair<int,int>> isInCheck();
        pair<bool, vector<pair<Square*, Square*>>> isSquarePinned(Square*);



        Square* getSquare(Piece p, Color c);
        Square* getSquare(Notation c);
        Square* getSquare(int x, int y);
        Notation getNotation(int, int);

        string moveToChess(Notation start, Notation end);//used for pgn 


        void print();
        string boardString();
        string getPGN();
        string getFEN();

};

Board::Board() {
    moveColor = WHITE;
    for(int i = 0; i < 1000; i++) {
        moves[i] = make_pair(MOVE, MOVE);
    }

    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            board[y][x].setPieceandColor(EMPTY, NONE);
            board[y][x].setxy(y, x);
        }
    }
    wasCapture = false;
    wasPromo = false;
    wasCastle = false;
    turnNum = 0;
    enpassantTarget = MOVE;
    moveColor = WHITE;
    halfTurnNum = 0;
    fullTurnNum = 1;
    wKQ_bkq[0] = true;
    wKQ_bkq[1] = true;
    wKQ_bkq[2] = true;
    wKQ_bkq[3] = true;

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
    vectorGetAllLegalMoves = getAllMoves();
    vectorGetNotationMoves = getAllMovesVector();
    setfenMap();
}

Color Board::getMoveColor() {
    return moveColor;
}

vector<pair<Notation, Notation>> Board::getAllMovesVector() {
    vector<pair<Notation, Notation>> moves;
    for(int i = 0; i < vectorGetAllLegalMoves.size(); i++) {
        pair<Square*, Square*> pairSq = vectorGetAllLegalMoves[i];
        Square* sq1 = pairSq.first;
        int sq1x = sq1->getx();
        int sq1y = sq1->gety();
        Square* sq2 = pairSq.second;
        int sq2x = sq2->getx();
        int sq2y = sq2->gety();

        Notation not_sq1 = getNotation(sq1x, sq1y);
        Notation not_sq2 = getNotation(sq2x, sq2y);
        pair<Notation, Notation> pairNot = make_pair(not_sq1, not_sq2);
        moves.push_back(pairNot);
    }
    return moves;
}

unordered_map<string, int> Board::getfenMap() {
    return fenMap;
}

void Board::setfenMap() {
    string fen_info = split(getFEN(), " ")[0];
    unordered_map<string, int>::iterator it = fenMap.find(fen_info);
    if(it != fenMap.end()) {
        it->second++;
    } else { 
        fenMap.insert(make_pair(fen_info, 1));
    }
}
int Board::getFenRepeat() {
    string findfen = split(getFEN(), " ")[0];
    unordered_map<string, int>::iterator it = fenMap.find(findfen);
    int repeat = 0;
    if(it != fenMap.end()) {
        repeat = it->second;
    }
    return repeat;
}

bool Board::getWasCapture() {
    return wasCapture;
}

bool Board::getWasPromo(){
    return wasPromo;
};

bool Board::getWasCastle(){
    return wasCastle;
};

void Board::setMoveColor() {
    if(moveColor == WHITE) {
        moveColor = BLACK;
    } else {
        moveColor = WHITE;
    }
}

void Board::loadFEN(string fen) {
    //format of fen
    // 8/8/8/4p1K1/2k1P3/8/8/8 b - - 0 1
    // #'s mean space, / means newline, b or w means move color, 
    // Qk means white queen side, kq means black queen side
    // e2 means en passant targets, this is where pawn would end up 
    // halfmove clock for 50 move rule, 99 means next move is 50 move rule
    // fullmove counter, incremented after black move and starts at 1

    vector<string> fen_info = split(fen, " ");
    string fen_str = fen_info[0]; //fen string
    string fen_color = fen_info[1]; // color move
    string fen_castle = fen_info[2]; //castlign rights
    string fen_en = fen_info[3]; //en passant target
    string fen_50 = fen_info[4]; //number of moves without capture or pawn move
    string fen_move = fen_info[5]; //current move number

    if(fen_color == "w") {
        moveColor = WHITE;
    } else if(fen_color == "b") {
        moveColor = BLACK;
    } else {
        moveColor = NONE;
    }

    if(fen_castle == "-") {
        wKQ_bkq[0] = false;
        wKQ_bkq[1] = false;
        wKQ_bkq[2] = false;
        wKQ_bkq[3] = false;
    } else {
        wKQ_bkq[0] = (fen_castle.find('K') != string::npos);
        wKQ_bkq[1] = (fen_castle.find('Q') != string::npos);
        wKQ_bkq[2] = (fen_castle.find('k') != string::npos);
        wKQ_bkq[3] = (fen_castle.find('q') != string::npos);
    }

    enpassantTarget = (fen_en != "-") ? stringToNotation(fen_en) : MOVE; 

    halfTurnNum = stoi(fen_50);
    fullTurnNum = stoi(fen_move);
    wasCapture = false;
    wasPromo = false;
    wasCastle = false;

    int position = 0;
    for(int i = 0; i < fen_str.length(); i++) {
        char ch = fen[i];
        bool isNum = isdigit(ch);
        if (isNum) {
            int chval = (int) ch - '0';
            for(int j = 0; j < chval; j++) {
                int temppos = position + j;
                vector<int> location = getFileRank(temppos);
                int f = location[0];
                int r = location[1];

                board[f][r].setPieceandColor(EMPTY, NONE);
            } 
            position += chval;
        } else if(ch != '/') {
            vector<int> location = getFileRank(position);
            int f = location[0];
            int r = location[1];

            Piece p = getPieceFromChar(ch);
            Color c = getColorFromChar(ch);
            board[f][r].setPieceandColor(p, c);

            position++;
        } else {
            //useless
        }
    }
    vectorGetAllLegalMoves = getAllMoves();
    vectorGetNotationMoves = getAllMovesVector();
}

Color Board::Winner() {
    if(isCheckmate()) {
        if(moveColor == BLACK) {
            return WHITE;
        } else {
            return BLACK;
        }
    } else {
        return NONE;
    }
}

bool Board::isGameOver() {
    bool game = isCheckmate() || isDraw();
    return game;
}
bool Board::isCheckmate() {
    bool checkmate = false;
    if(vectorGetAllLegalMoves.size() == 0 && isInCheck().size() == 1) {
        checkmate = true;
    }
    return checkmate;
}     
bool Board::isDraw() {
    bool draw = false;
    if(vectorGetAllLegalMoves.size() == 0 && isInCheck().size() == 0) {
        draw = true;
    }
    if(halfTurnNum == 100) {
        draw = true;
    }
    bool repdraw = repitionDraw();
    if(repdraw) {
        draw = true;
    }
    bool noforcedmate = noForcedMateDraw();
    if(noforcedmate) {
        draw = true;
    }
    return draw;
}
bool Board::repitionDraw() {

    string fen_info = split(getFEN(), " ")[0];
    unordered_map<string, int>::iterator it = fenMap.find(fen_info);
    if(it != fenMap.end()) {
        if(it->second==3) {
            return true;
        }
    }
    return false;

}
bool Board::noForcedMateDraw() {
    bool noforce = false;
    vector<pair<Piece, Color>> pieces;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            Square* temp = getSquare(i, j);
            if(temp->getPiece() != EMPTY) {
                Piece p = temp->getPiece();
                Color c = temp->getColor();
                pair<Piece, Color> add = make_pair(p, c);
                pieces.push_back(add);
            }
        }
    }

    if(pieces.size() == 2) {
        noforce = true;
    }
    if(pieces.size() == 3) {
        Piece p1 = pieces[0].first;
        Piece p2 = pieces[1].first;
        Piece p3 = pieces[2].first;
        bool isKnight = (p1 == KNIGHT) || (p2 == KNIGHT) || (p3 == KNIGHT);
        bool isBishop = (p1 == BISHOP) || (p2 == BISHOP) || (p3 == BISHOP);
        if(isKnight || isBishop) {
            noforce = true;
        }
    }

    return noforce;
}

void Board::makeMoveAndPrint(Notation start, Notation end) {
    bool makingmove = makeMove(start, end);
    if(makingmove) {
        print();
    }
    return;
}

bool Board::makeMove(Notation start, Notation end) {
    //cout << "makeMove()" << endl;
    //cout << "moveColor: " << moveColor << endl;
    //if can make move return true and make move
    bool move_made = false;
    Square* sqstart = getSquare(start);
    Square* sqend = getSquare(end);
    
    bool rightColor = sqstart->getColor() == moveColor;
    vectorGetAllLegalMoves = getAllMoves();
    vectorGetNotationMoves = getAllMovesVector();
    //cout << "allmoves size: " << vectorGetAllLegalMoves.size() << endl;
    bool gameOver = isGameOver();
    if(!vectorGetAllLegalMoves.size()) {
        move_made = false;
    }
    bool legalmove = false;
    for(int i = 0; i < vectorGetAllLegalMoves.size(); i++) {
        Square* teststart = vectorGetAllLegalMoves[i].first;
        Square* testend = vectorGetAllLegalMoves[i].second;
        bool testxstart = teststart->getx() == sqstart->getx();
        bool testystart = teststart->gety() == sqstart->gety();
        bool testxend = testend->getx() == sqend->getx();
        bool testyend = testend->gety() == sqend->gety();
        if(testxstart && testystart && testxend && testyend) {
            legalmove = true;
            break;
        }
    }

    //cout << "rightColor, gameover, legalmove: " << rightColor << ", " << gameOver << ", " << legalmove << endl;
    if(rightColor && !gameOver && legalmove) {
        bool pawnmove=false;
        bool capture=false;
        bool updateEnpassantTarget=false;
        //test if castling
        bool castleMove = sqstart->getPiece() == KING &&
            abs(sqstart->getx() - sqend->getx()) == 2;
        //test if en passant
        bool enpassant = sqstart->getPiece() == PAWN &&
            end==enpassantTarget;
        //test if promotion
        bool promotion = sqstart->getPiece() == PAWN &&
            notationToString(end).length() == 3;
        bool pawnDoubleMove = sqstart->getPiece() == PAWN &&
            abs(sqstart->gety() - sqend->gety()) == 2;

        if(castleMove) {
            if(moveColor == WHITE) {
                wKQ_bkq[0] = 0;
                wKQ_bkq[1] = 0;
                bool longcastle = end == c1;
                if(longcastle) {
                    Square* d1sqaure = getSquare(d1);
                    Square* a1sqaure = getSquare(a1);
                    sqend->setPieceandColor(KING, WHITE);
                    d1sqaure->setPieceandColor(ROOK, WHITE);
                    sqstart->setEmpty();
                    a1sqaure->setEmpty();
                } else {
                    Square* f1sqaure = getSquare(f1);
                    Square* h1sqaure = getSquare(h1);
                    sqend->setPieceandColor(KING, WHITE);
                    f1sqaure->setPieceandColor(ROOK, WHITE);
                    sqstart->setEmpty();
                    h1sqaure->setEmpty();
                }
            } else {
                bool longcastle = end == c8;
                wKQ_bkq[2] = 0;
                wKQ_bkq[3] = 0;
                if(longcastle) {
                    Square* d8sqaure = getSquare(d8);
                    Square* a8sqaure = getSquare(a8);
                    sqend->setPieceandColor(KING, BLACK);
                    d8sqaure->setPieceandColor(ROOK, BLACK);
                    sqstart->setEmpty();
                    a8sqaure->setEmpty();
                } else {
                    Square* f8sqaure = getSquare(f8);
                    Square* h8sqaure = getSquare(h8);
                    sqend->setPieceandColor(KING, BLACK);
                    f8sqaure->setPieceandColor(ROOK, BLACK);
                    sqstart->setEmpty();
                    h8sqaure->setEmpty();
                }
            }
        } else if(enpassant) {
            pawnmove=true;
            sqend->setPieceandColor(PAWN, sqstart->getColor());
            sqstart->setEmpty();
            Square* takenpawn = getSquare(sqend->getx(), sqstart->gety());
            takenpawn->setEmpty();
        } else if(promotion) {
            pawnmove=true;
            if(sqend->getPiece() != EMPTY) {
                capture = true;
            }
            Piece promoPiece = getPawnPromotion(end);
            sqend->setPieceandColor(promoPiece, sqstart->getColor());
            sqstart->setEmpty();
        } else {
            if(sqstart->getPiece() == PAWN) {
                pawnmove = true;
            }
            if(sqend->getPiece() != EMPTY) {
                capture = true;
            }
            sqend->setPieceandColor(sqstart->getPiece(), sqstart->getColor());
            sqstart->setEmpty();
        }

        if(pawnDoubleMove) {
            if(moveColor == WHITE) {//add 1 y, same x as before
                int y = sqend->gety();
                enpassantTarget = getNotation(sqend->getx(), y+1);
            } else {
                int y = sqend->gety();
                enpassantTarget = getNotation(sqend->getx(), y-1);
            }
        } else {
            enpassantTarget = MOVE;
        }


        if(start == a1 || end == a1) { wKQ_bkq[0] = false; }
        if(start == e1 || end == e1) { wKQ_bkq[0] = false; wKQ_bkq[1] = false; }
        if(start == h1 || end == h1) { wKQ_bkq[1] = false; }
        if(start == a8 || end == a8) { wKQ_bkq[2] = false; }
        if(start == e8 || end == e8) { wKQ_bkq[2] = false; wKQ_bkq[3] = false; }
        if(start == h8 || end == h8) { wKQ_bkq[3] = false; }

        moves[turnNum] = make_pair(start, end);
        wasCapture = capture;
        wasPromo = promotion;
        wasCastle = castleMove;
        if(pawnmove || capture) { halfTurnNum = 0; } else { halfTurnNum++; }
        if(moveColor == BLACK) { fullTurnNum++; }
        setMoveColor();
        turnNum++;

        move_made = true;
        setfenMap();
    } else {
        move_made = false;
    }
    
    vectorGetAllLegalMoves = getAllMoves();
    vectorGetNotationMoves = getAllMovesVector();
    return move_made;
}

Piece Board::getPawnPromotion(Notation n){
    string str = notationToString(n);
    Piece p = EMPTY;
    switch(str[2]) {
        case 'q': p = QUEEN; break;
        case 'Q': p = QUEEN; break;
        case 'r': p = ROOK; break;
        case 'R': p = ROOK; break;
        case 'b': p = BISHOP; break;
        case 'B': p = BISHOP; break;
        case 'n': p = KNIGHT; break;
        case 'N': p = KNIGHT; break;
        default: break;
    }
    return p;
}

pair<int, int> Board::movetHelper(int tempx, int tempy, Square* sq) {
    pair<int, int> p = make_pair(-1, -1);
    if(isInRange(tempx, tempy)) {
        Square* temp = getSquare(tempx, tempy);
        if(sq->getColor() == temp->getColor()) {//check if not color
            //skip
        } else if (sq->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(tempx, tempy);
            p=temppair;
        } else {
            pair<int, int> temppair = make_pair(tempx, tempy);
            p=temppair;
        }
    }
    return p;
}

vector<pair<Square*, Square*>> Board::getAllMoves() {
    //can get all moves and then test all those moves return and see if they are legal from there
    //need to see if in check
    vector<pair<int, int>> checks = isInCheck();
    //coutTab(1);
    //cout << "getallmoves()" << endl;
    vector<pair<Square*, Square*>> allmoves;
    if(checks.size() == 2) { //if in double check return all possible king moves
        Square* king = getKing(moveColor);
        return getPieceMoves(king);
    } else if(checks.size() == 1) { //if in single check, return all moves that block the check, can caputre the piece without check or move to king to non check position
        vector<pair<Square*, Square*>> testmoves;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                Square* temp = getSquare(i, j);
                if(temp->getPiece() != EMPTY && temp->getPiece() != KING) {
                    pair<bool, vector<pair<Square*, Square*>>> pinnedmoves = isSquarePinned(temp);
                    if(pinnedmoves.first) {
                        vector<pair<Square*, Square*>> moves = pinnedmoves.second;
                        for(int k = 0; k < moves.size(); k++) {
                            testmoves.push_back(moves[k]);
                        }
                    }
                }
            }
        }
        //have all moves moves without testing check, need to get piece moves that capture piece or where king moves or where move blocks check
        Square* king = getKing(moveColor);
        vector<pair<Square*, Square*>> kingMoves = getPieceMoves(king);
        pair<int, int> attackercheck = checks[0];
        int attx = attackercheck.first;
        int atty = attackercheck.second;
        Square* attacker = getSquare(attx, atty);
        for(int i = 0; i < testmoves.size(); i++) {
            Square* testmove_end = testmoves[i].second;
            bool testx = testmove_end->getx() == attx;
            bool testy = testmove_end->gety() == atty;
            pair<bool, Square*> block = isBetweenKingandAttacker(king, attacker, testmove_end);
            if(testx && testy) { //test if capture
                allmoves.push_back(testmoves[i]);
            } else if(block.first) {//test if block
                allmoves.push_back(testmoves[i]);
            }
        }
        for(int i = 0; i < kingMoves.size(); i++) {
            allmoves.push_back(kingMoves[i]);
        }


    } else { //if no check, need to see if piece is pinned, if pinned get all moves possible will pin in mind
        //coutTab(1);
        //cout << "0 checks" << endl;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                Square* temp = getSquare(i, j);
                if(temp->getPiece() != EMPTY && temp->getColor() != NONE) {
                    pair<bool, vector<pair<Square*, Square*>>> pinnedmoves = isSquarePinned(temp);
                    if(pinnedmoves.first) {
                        //cout << "square is pinned " << endl;
                        vector<pair<Square*, Square*>> moves = pinnedmoves.second;
                        for(int k = 0; k < moves.size(); k++) {
                            allmoves.push_back(moves[k]);
                        }
                    } else {
                        //cout << "square is NOT pinned " << endl;
                        vector<pair<Square*, Square*>> moves = pinnedmoves.second;
                        for(int k = 0; k < moves.size(); k++) {
                            allmoves.push_back(moves[k]);
                        }
                    }
                }
            }
        }
    }
    //coutTab(1);
    //cout << "get all moves done" << endl;
    return allmoves;
}

vector<pair<Square*, Square*>> Board::getPieceMoves(Square*sq){
    //coutTab(3);
    //cout << "getPieceMoves()" << endl;
    vector<pair<Square*, Square*>> temp = {make_pair(nullptr, nullptr)};
    Piece p = sq->getPiece();
    //coutTab(3);
    //cout << "Piece: " << p << endl;
    switch(p){
        case KING:
            temp = KingMoves(sq);
            //coutTab(3);
            //cout << "king moves size: " << temp.size() << endl;
            break;
        case QUEEN:
            temp = QueenMoves(sq);
            break;
        case ROOK:
            temp = RookMoves(sq);
            break;
        case BISHOP:
            temp = BishopMoves(sq);
            break;
        case KNIGHT:
            temp = KnightMoves(sq);
            break;
        case PAWN:
            temp = PawnMoves(sq);
            break;
    }
    //coutTab(3);
    //cout << "piecemoves size: " << temp.size() << endl;
    return temp;
}
vector<pair<Square*, Square*>> Board::KingMoves(Square*sq){
    //coutTab(4);
    //cout << "kingmove()" << endl;
    vector<pair<Square*, Square*>> kings;
    int x = sq->getx();
    int y = sq->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

    vector<pair<int, int>> pairs;
    pairs.push_back(make_pair(-1, -1));
    pairs.push_back(make_pair(-1, 0));
    pairs.push_back(make_pair(-1, 1));
    pairs.push_back(make_pair(0, -1));
    pairs.push_back(make_pair(0, 1));
    pairs.push_back(make_pair(1, -1));
    pairs.push_back(make_pair(1, 0));
    pairs.push_back(make_pair(1, 1));


    //castling
    if(moveColor == WHITE) {
        vector<bool> castle = canWhiteCastle();
        if(castle[0]) {
            pairs.push_back(make_pair(-2, 0));
        }
        if(castle[1]) {
            pairs.push_back(make_pair(2, 0));
        }
    } else {
        vector<bool> castle = canBlackCastle();
        if(castle[0]) {
            pairs.push_back(make_pair(-2, 0));
        }
        if(castle[1]) {
            pairs.push_back(make_pair(2, 0));
        }
    }


    for(int i = 0; i < pairs.size(); i++) {
        pair<int, int> temp = movetHelper(x+pairs[i].first, y+pairs[i].second, sq);
        if(temp.first != -1) {
            Square* end = getSquare(temp.first, temp.second);
            bool notFutureCheck = isSquareAttack(end).size() == 0;
            if(notFutureCheck) {
                pair<Square*, Square*> add = make_pair(sq, end);
                kings.push_back(add);
            }
        }
    }
    //coutTab(4);
    //cout << "num king moves: " << kings.size() << endl;
    return kings;
}
vector<pair<Square*, Square*>> Board::QueenMoves(Square*sq){
    //coutTab(4);
    //cout << "queenmove()" << endl;
    vector<pair<Square*, Square*>> queens;
    vector<pair<Square*, Square*>> bishops = BishopMoves(sq);
    vector<pair<Square*, Square*>> rooks = RookMoves(sq);
    for(int i = 0; i < bishops.size(); i++) {
        queens.push_back(bishops[i]);
    }
    for(int i = 0; i < rooks.size(); i++) {
        queens.push_back(rooks[i]);
    }
    //coutTab(4);
    //cout << "num queen moves: " << queens.size() << endl;
    return queens;
}
vector<pair<Square*, Square*>> Board::RookMoves(Square*start){
    //coutTab(4);
    //cout << "rookmove()" << endl;
    vector<pair<Square*, Square*>> rookmoves;
    int x = start->getx();
    int y = start->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

    for(int i = x+1; i < 8; i++) { //check files positive
        Square* temp = getSquare(i, y);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(i, y);
            Square* end = getSquare(temppair.first, temppair.second);
            rookmoves.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(i, y);
        Square* end = getSquare(temppair.first, temppair.second);
        rookmoves.push_back(make_pair(start, end));
    }
    for(int i = x-1; i >= 0; i--) { //check files negative
        Square* temp = getSquare(i, y);
        if(start->getColor() == temp->getColor() ) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(i, y);
            Square* end = getSquare(temppair.first, temppair.second);
            rookmoves.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(i, y);
        Square* end = getSquare(temppair.first, temppair.second);
        rookmoves.push_back(make_pair(start, end));
    }
    for(int i = y-1; i >= 0; i--) { //check rank negative
        Square* temp = getSquare(x, i);;
        if(start->getColor() == temp->getColor()) {//check for same color piece color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(x, i);
            Square* end = getSquare(temppair.first, temppair.second);
            rookmoves.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(x, i);
        Square* end = getSquare(temppair.first, temppair.second);
        rookmoves.push_back(make_pair(start, end));
    }
    for(int i = y+1; i < 8; i++) { //check rank positive
        Square* temp = getSquare(x, i);;
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(x, i);
            Square* end = getSquare(temppair.first, temppair.second);
            rookmoves.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(x, i);
        Square* end = getSquare(temppair.first, temppair.second);
        rookmoves.push_back(make_pair(start, end));
    }
    //coutTab(4);
    //cout << "num rookmoves: " << rookmoves.size() << endl;
    return rookmoves;
}
vector<pair<Square*, Square*>> Board::BishopMoves(Square*start){
    //coutTab(4);
    //cout << "bishopmove()" << endl;
    vector<pair<Square*, Square*>> diags;
    int x = start->getx();
    int y = start->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

    int tempx = x;
    int tempy = y;
    while(tempx+1<8 && tempy+1<8) { //postive x and poisitve y
        tempx++;
        tempy++;
        Square* temp = getSquare(tempx, tempy);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(tempx, tempy);
            Square* end = getSquare(temppair.first, temppair.second);
            diags.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        Square* end = getSquare(temppair.first, temppair.second);
        diags.push_back(make_pair(start, end));
    }

    tempx = x;
    tempy = y;
    while(tempx-1>=0 && tempy+1<8) {//negative x and positive y
        tempx--;
        tempy++;
        Square* temp = getSquare(tempx, tempy);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(tempx, tempy);
            Square* end = getSquare(temppair.first, temppair.second);
            diags.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        Square* end = getSquare(temppair.first, temppair.second);
        diags.push_back(make_pair(start, end));
    }

    tempx = x;
    tempy = y;
    while(tempx+1<8 && tempy-1>=0) {//postive x and negative y
        tempx++;
        tempy--;
        Square* temp = getSquare(tempx, tempy);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(tempx, tempy);
            Square* end = getSquare(temppair.first, temppair.second);
            diags.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        Square* end = getSquare(temppair.first, temppair.second);
        diags.push_back(make_pair(start, end));
    }

    tempx = x;
    tempy = y;
    while(tempx-1>=0 && tempy-1>=0) {//negative x and negative y
        tempx--;
        tempy--;
        Square* temp = getSquare(tempx, tempy);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(tempx, tempy);
            Square* end = getSquare(temppair.first, temppair.second);
            diags.push_back(make_pair(start, end));
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        Square* end = getSquare(temppair.first, temppair.second);
        diags.push_back(make_pair(start, end));
    }
    //coutTab(4);
    //cout << "num bishop moves: " << diags.size() << endl;
    return diags;
}
vector<pair<Square*, Square*>> Board::KnightMoves(Square*sq){
    //coutTab(4);
    //cout << "knightmove()" << endl;
    vector<pair<Square*, Square*>> knights;
    int x = sq->getx();
    int y = sq->gety();

    vector<pair<int, int>> pairs;
    pairs.push_back(make_pair(-1, -2));
    pairs.push_back(make_pair(-2, -1));
    pairs.push_back(make_pair(-2, 1));
    pairs.push_back(make_pair(-1, 2));
    pairs.push_back(make_pair(1, 2));
    pairs.push_back(make_pair(2, 1));
    pairs.push_back(make_pair(2, -1));
    pairs.push_back(make_pair(1, -2));

    for(int i = 0; i < pairs.size(); i++) {
        pair<int, int> temp = movetHelper(x+pairs[i].first, y+pairs[i].second, sq);
        if(temp.first != -1) { //(-1, -2)
            Square* end = getSquare(temp.first, temp.second);
            knights.push_back(make_pair(sq, end));
        }
    }
    //coutTab(4);
    //cout << "num knights moves: " << knights.size() << endl;
    return knights;
}
vector<pair<Square*, Square*>> Board::PawnMoves(Square*pawn){
    //coutTab(4);
    //cout << "pawnmove()" << endl;
    vector<pair<Square*, Square*>> pawns;
    int x = pawn->getx();
    int y = pawn->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

    vector<pair<int, int>> push;
    vector<pair<int, int>> capture;
    pair<int, int> temp;
    //check 4 spots
    if(pawn->getColor() == WHITE) {
        capture.push_back(make_pair(-1, -1));
        capture.push_back(make_pair(1, -1));
        Square* cap1 = getSquare(x-1, y-1);
        if(cap1->getPiece() != EMPTY && cap1->getColor() != pawn->getColor() && x-1 >= 0) {
            temp = make_pair(x-1, y-1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
        }

        Square* cap2 = getSquare(x+1, y-1);
        if(cap2->getPiece() != EMPTY && cap2->getColor() != pawn->getColor() && x+1 <= 7) {
            temp = make_pair(x+1, y-1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
        }


        Square* sq1 = getSquare(x, y-1);
        if(sq1->getPiece() == EMPTY) {
            temp = make_pair(x, y-1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
            Square* sq2 = getSquare(x, y-2);
            if(pawn->gety() == 6 && sq2->getPiece() == EMPTY) {
                temp = make_pair(x, y-2);
                Square * end = getSquare(temp.first, temp.second);
                pawns.push_back(make_pair(pawn, end));
            }

        }

        if(pawn->gety() == 3 && enpassantTarget != MOVE) {
            Square* enpassantSquare = getSquare(enpassantTarget);
            int enpassantSquare_x = enpassantSquare->getx();
            int enpassantSquare_y = enpassantSquare->gety();
            bool goodx = abs(enpassantSquare_x-x) == 1;
            bool goody = enpassantSquare_y-y == -1;

            Square* king = getKing(BLACK);
            Square* attacked;
            if(abs(x-king->getx()) > abs(enpassantSquare_x-king->getx())) {
                attacked = pawn;
            } else {
                attacked = enpassantSquare;
            }
            bool rookIsPinningPawn = false;
            vector<pair<int, int>> rooksAttackers = isRookAttacker(attacked);
            for(int i = 0; i < rooksAttackers.size(); i++) {
                pair<int, int> temp = rooksAttackers[i];
                if(temp.second == 3) {
                    rookIsPinningPawn = true;
                }
            }
            bool notpinned = king->gety()==3 && rookIsPinningPawn;

            if(goodx && goody && notpinned) {
                pawns.push_back(make_pair(pawn, enpassantSquare));
            }
        }
        
    } else {
        capture.push_back(make_pair(-1, 1));
        capture.push_back(make_pair(1, 1));
        Square* cap1 = getSquare(x-1, y+1);
        if(cap1->getPiece() != EMPTY && cap1->getColor() != pawn->getColor() && x-1 >= 0) {
            temp = make_pair(x-1, y+1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
        }

        Square* cap2 = getSquare(x+1, y+1);
        if(cap2->getPiece() != EMPTY && cap2->getColor() != pawn->getColor() && x+1 <= 7) {
            temp = make_pair(x+1, y+1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
        }


        Square* sq1 = getSquare(x, y+1);
        if(sq1->getPiece() == EMPTY) {
            temp = make_pair(x, y+1);
            Square * end = getSquare(temp.first, temp.second);
            pawns.push_back(make_pair(pawn, end));
            Square* sq2 = getSquare(x, y+2);
            if(pawn->gety() == 1 && sq2->getPiece() == EMPTY) {
                temp = make_pair(x, y+2);
                Square * end = getSquare(temp.first, temp.second);
                pawns.push_back(make_pair(pawn, end));
            }

        }

        if(pawn->gety() == 4  && enpassantTarget != MOVE) {
            Square* enpassantSquare = getSquare(enpassantTarget);
            int enpassantSquare_x = enpassantSquare->getx();
            int enpassantSquare_y = enpassantSquare->gety();
            bool goodx = abs(enpassantSquare_x-x) == 1;
            bool goody = enpassantSquare_y-y == 1;

            Square* king = getKing(BLACK);
            Square* attacked;
            if(abs(x-king->getx()) > abs(enpassantSquare_x-king->getx())) {
                attacked = pawn;
            } else {
                attacked = enpassantSquare;
            }
            bool rookIsPinningPawn = false;
            vector<pair<int, int>> rooksAttackers = isRookAttacker(attacked);
            for(int i = 0; i < rooksAttackers.size(); i++) {
                pair<int, int> temp = rooksAttackers[i];
                if(temp.second == 4) {
                    rookIsPinningPawn = true;
                }
            }
            bool notpinned = king->gety()==4 && rookIsPinningPawn;

            if(goodx && goody && notpinned) {
                pawns.push_back(make_pair(pawn, enpassantSquare));
            }
        }
    }


    // cout << "getPawns()" << endl;
    // for(int i = 0; i < pawns.size(); i++) {
    //     cout << pawns[i].first << ", " << pawns[i].first << endl;
    // }
    //coutTab(4);
    //cout << "num pawn moves: " << pawns.size() << endl;
    return pawns;
}


Square* Board::getKing(Color c) {
    Square* king;
    Square* temp;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            temp = getSquare(i, j);
            if(temp->getColor() == c && temp->getPiece() == KING && isInRange(temp->getx(), temp->gety())) {
                king = temp;
            }
        }
    }
    return king;
}


pair<bool, Square*> Board::isBetweenKingandAttacker(Square* king, Square* attacker, Square* pin) {
    int kingx = king->getx();
    int kingy = king->gety();

    int attx = attacker->getx();
    int atty = attacker->gety();

    int pinx = pin->getx();
    int piny = pin->gety();

    int king_to_attaker_x = abs(kingx-attx);
    int king_to_attaker_y = abs(kingy-atty);

    bool in_range = inRange(kingx, attx, pinx) && inRange(kingy, atty, piny);

    //test if attacker on pin is actually pinned by 
    bool is_bishop_pinning = in_range &&
        (king_to_attaker_x == king_to_attaker_y) && 
        (king_to_attaker_x > 1 && king_to_attaker_x > 1) &&
        (attacker->getPiece() == QUEEN || attacker->getPiece() == BISHOP); 

    bool is_rook_pinning = in_range &&
        (king_to_attaker_x == 0 && king_to_attaker_y != 0) || 
        (king_to_attaker_x != 0 && king_to_attaker_y == 0) && 
        (attacker->getPiece() == ROOK || attacker->getPiece() == BISHOP);

    if(is_bishop_pinning || is_rook_pinning) {
        return make_pair(true, attacker);
    } else {
        return make_pair(false, attacker);
    }
}

pair<bool, vector<pair<Square*, Square*>>> Board::isSquarePinned(Square* s) {
    //coutTab(2);
    //cout << "isSquarePinned()" << endl;
    Piece p = s->getPiece();
    Color c = s->getColor();
    vector<pair<int, int>> attackers = isSquareAttack(s);
    vector<pair<Square*, Square*>> legalmoves;
    pair<bool, vector<pair<Square*, Square*>>> returnthis;
    if(p == EMPTY || c == NONE) {
        //coutTab(2);
        //cout << "empty piece" << endl;
        returnthis = make_pair(false, legalmoves);
    } 
    if(c == moveColor && attackers.size() != 0) {
        Square* king = getKing(moveColor);

        for(int i = 0; i < attackers.size(); i++) {
            pair<int, int> temp = attackers[i];
            int tempx = temp.first;
            int tempy = temp.second;
            Square* att = getSquare(tempx, tempy);
            
            pair<bool, Square*> data = isBetweenKingandAttacker(king, att, s);

            if(data.first == true) {
                //coutTab(2);
                //cout << "attackers, is protecting king" << endl;
                Square* att = data.second;
                //get all moves for square* s
                vector<pair<Square*, Square*>> piecemoves = getPieceMoves(s);//get all moves for square s
                for(int i = 0; i < piecemoves.size(); i++) {//test in all position if endmove for square s is between king and attacker
                    Square* testSquare = piecemoves[i].second;
                    pair<bool, Square*> test = isBetweenKingandAttacker(king, att, testSquare);
                    if(test.first == true) {
                        legalmoves.push_back(piecemoves[i]);
                    }
                }
                returnthis = make_pair(true, legalmoves);
            } else {
                //coutTab(2);
                //cout << "attackers, but not protecting king" << endl;
                legalmoves = getPieceMoves(s);
                returnthis = make_pair(false, legalmoves);
            }
        }
    } else if(c == moveColor && attackers.size() == 0) {
        //coutTab(2);
        //cout << "no attackers" << endl;
        legalmoves = getPieceMoves(s);
        returnthis = make_pair(false, legalmoves);
    }
    //coutTab(2);
    //cout << "returnthis: " << returnthis.first << ", " << returnthis.second.size() << endl;
    return returnthis;

}

vector<pair<int,int>> Board::isInCheck() {
    vector<pair<int,int>> checks;
    if(moveColor == WHITE) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                Square* temp = getSquare(i, j);
                if(temp->getColor() == WHITE && temp->getPiece() == KING) {
                    checks = isSquareAttack(temp);
                }
            }
        }
    } else {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                Square* temp = getSquare(i, j);
                if(temp->getColor() == BLACK && temp->getPiece() == KING) {
                    checks = isSquareAttack(temp);
                }
            }
        }
    }
    return checks;
}

vector<bool> Board::canWhiteCastle() {
    vector<bool> longshort;
    longshort.push_back(false);
    longshort.push_back(false);

    bool emptysquare_short = 
        getSquare(f1)->getPiece() == EMPTY &&
        getSquare(g1)->getPiece() == EMPTY;

    bool emptysquare_long = 
        getSquare(d1)->getPiece() == EMPTY &&
        getSquare(c1)->getPiece() == EMPTY &&
        getSquare(b1)->getPiece() == EMPTY;

    bool no_checks_short = 
        isSquareAttack(getSquare(e1)).size() == 0 && 
        isSquareAttack(getSquare(f1)).size() == 0 && 
        isSquareAttack(getSquare(g1)).size() == 0;
    bool no_checks_long = 
        isSquareAttack(getSquare(e1)).size() == 0 &&  
        isSquareAttack(getSquare(d1)).size() == 0 &&  
        isSquareAttack(getSquare(c1)).size() == 0;

    if(wKQ_bkq[0] && no_checks_short && emptysquare_short) {
        longshort[1] = true;
    }

    if(wKQ_bkq[1] && no_checks_long && emptysquare_long) {
        longshort[0] = true;
    }

    return longshort;
}

vector<bool> Board::canBlackCastle() {
    vector<bool> longshort;
    longshort.push_back(false);
    longshort.push_back(false);

    bool emptysquare_short = 
        getSquare(f8)->getPiece() == EMPTY &&
        getSquare(g8)->getPiece() == EMPTY;

    bool emptysquare_long = 
        getSquare(d8)->getPiece() == EMPTY &&
        getSquare(c8)->getPiece() == EMPTY &&
        getSquare(b8)->getPiece() == EMPTY;

    bool no_checks_short = 
        isSquareAttack(getSquare(e8)).size() == 0 && 
        isSquareAttack(getSquare(f8)).size() == 0 &&  
        isSquareAttack(getSquare(g8)).size() == 0;
    bool no_checks_long = 
        isSquareAttack(getSquare(e8)).size() == 0 &&  
        isSquareAttack(getSquare(d8)).size() == 0 &&  
        isSquareAttack(getSquare(c8)).size() == 0;

    if(wKQ_bkq[2] && no_checks_short && emptysquare_short) {
        longshort[1] = true;
    }

    if(wKQ_bkq[3] && no_checks_long && emptysquare_long) {
        longshort[0] = true;
    }

    return longshort;
}


vector<pair<int,int>> Board::isBishopAttacker(Square*s) {
    int x = s->getx();
    int y = s->gety();
    vector<pair<int, int>> pairs;

    //up left (-x, -y)
    for(int i = 1; i < 8; i++) {
        int tempx = x-i;
        int tempy = y-i;

        if(isInRange(tempx, tempy)) {
            Square* temp = getSquare(tempx, tempy);
            if(temp->getColor() == moveColor) {
                break;
            } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
                break;
            } else {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
            }
        }
    }

    //down left (-x, +y)
    for(int i = 1; i < 8; i++) {
        int tempx = x-i;
        int tempy = y+i;
        if(isInRange(tempx, tempy)) {
            Square* temp = getSquare(tempx, tempy);
            if(temp->getColor() == moveColor) {
                break;
            } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
                break;
            } else {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
            }
        } else {
            break;
        }
    }

    //down right (+x, +y)
    for(int i = 1; i < 8; i++) {
        int tempx = x+i;
        int tempy = y+i;
        if(isInRange(tempx, tempy)) {
            Square* temp = getSquare(tempx, tempy);
            if(temp->getColor() == moveColor) {
                break;
            } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
                break;
            } else {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
            }
        } else {
            break;
        }
    }

    //up right (+x, -y)
    for(int i = 1; i < 8; i++) {
        int tempx = x+i;
        int tempy = y-i;
        if(isInRange(tempx, tempy)) {
            Square* temp = getSquare(tempx, tempy);
            if(temp->getColor() == moveColor) {
                break;
            } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
                break;
            } else {
                pair<int, int> newpair = make_pair(tempx, tempy);
                pairs.push_back(newpair);
            }
        } else {
            break;
        }
    }

    vector<pair<int, int>> attackers;
    for(int i = 0; i < pairs.size(); i++) {
        int tempx = pairs[i].first;
        int tempy = pairs[i].second;
        Square* temp = getSquare(tempx, tempy);
        //cout << tempx << ", " << tempy << endl;
        bool isAttackingBishop = ((temp->getPiece() == BISHOP) ||  (temp->getPiece() == QUEEN)) && (temp->getColor() != moveColor);
        if(isAttackingBishop) {
            attackers.push_back(make_pair(tempx, tempy));
        }
    }
    return attackers;
}
vector<pair<int,int>> Board::isRookAttacker(Square*square) {
    int x = square->getx();
    int y = square->gety();
    vector<pair<int, int>> pairs;

    //right
    for(int i = x+1; i < 8; i++) {
        int tempx = i;
        int tempy = y;
        Square* temp = getSquare(tempx, tempy);
        if(temp->getColor() == moveColor) {
            break;
        } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
            break;
        } else {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
        }
    }

    //left
    for(int i = x-1; i >= 0; i--) {
        int tempx = i;
        int tempy = y;
        Square* temp = getSquare(tempx, tempy);
        if(temp->getColor() == moveColor) {
            break;
        } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
            break;
        } else {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
        }
    }

    //up
    for(int i = y-1; i >= 0; i--) {
        int tempx = x;
        int tempy = i;
        Square* temp = getSquare(tempx, tempy);
        if(temp->getColor() == moveColor) {
            break;
        } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
            break;
        } else {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
        }
    }

    //down
    for(int i = y+1; i < 8; i++) {
        int tempx = x;
        int tempy = i;
        Square* temp = getSquare(tempx, tempy);
        if(temp->getColor() == moveColor) {
            break;
        } else if(temp->getColor() != NONE && temp->getColor() != moveColor) {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
            break;
        } else {
            pair<int, int> newpair = make_pair(tempx, tempy);
            pairs.push_back(newpair);
        }
    }

    vector<pair<int, int>> attackers;
    for(int i = 0; i < pairs.size(); i++) {
        int tempx = pairs[i].first;
        int tempy = pairs[i].second;
        Square* temp = getSquare(tempx, tempy);
        //cout << tempx << ", " << tempy << endl;
        bool isAttackingRook = ((temp->getPiece() == ROOK) ||  (temp->getPiece() == QUEEN)) && (temp->getColor() != moveColor);
        if(isAttackingRook) {
            attackers.push_back(make_pair(tempx, tempy));
        }
    }
    return attackers;
}
vector<pair<int,int>> Board::isKnightAttacker(Square*square) {
    int currx = square->getx();
    int curry = square->gety();
    vector<pair<int, int>> pairs;
    vector<pair<int, int>> attackers;
    pairs.push_back(make_pair(-1, -2));
    pairs.push_back(make_pair(-2, -1));
    pairs.push_back(make_pair(-2, 1));
    pairs.push_back(make_pair(-1, 2));
    pairs.push_back(make_pair(1, 2));
    pairs.push_back(make_pair(2, 1));
    pairs.push_back(make_pair(2, -1));
    pairs.push_back(make_pair(1, -2));

    vector<pair<int, int>> searched_pairs;

    for(int i = 0; i < pairs.size(); i++) {
        int tempx = currx + pairs[i].first;
        int tempy = curry + pairs[i].second;
        bool onboard = isInRange(tempx, tempy);
        if(onboard) {
            pair<int, int> add = make_pair(tempx, tempy);
            searched_pairs.push_back(add);
        }
    }

    for(int i = 0; i < searched_pairs.size(); i++) {
        int tempx = searched_pairs[i].first;
        int tempy = searched_pairs[i].second;
        Square* temp = getSquare(tempx, tempy);
        bool isAttckingKnight = (temp->getPiece() == KNIGHT) && (temp->getColor() != moveColor);
        if(isAttckingKnight) {
            attackers.push_back(make_pair(tempx, tempy));
        }
    }
    return attackers;
}
vector<pair<int,int>> Board::isPawnAttacker(Square*square) {
    int currx = square->getx();
    int curry = square->gety();

    bool tester = false;
    vector<pair<int, int>> pairs;
    vector<pair<int, int>> attackers;

    if(moveColor == WHITE) {
        Square* temp1 = getSquare(currx-1, curry-1);
        Square* temp2 = getSquare(currx+1, curry-1);
        bool isAttackingBlackPawn1 = (temp1->getColor() == BLACK && temp1->getPiece() == PAWN);
        bool isAttackingBlackPawn2 = (temp2->getColor() == BLACK && temp2->getPiece() == PAWN);

        if(isAttackingBlackPawn1) {
            attackers.push_back(make_pair(temp1->getx(), temp1->gety()));
        }

        if(isAttackingBlackPawn2) {
            attackers.push_back(make_pair(temp2->getx(), temp2->gety()));
        }
    } else { //color is BLACK
        Square* temp1 = getSquare(currx-1, curry+1);
        Square* temp2 = getSquare(currx+1, curry+1);
        bool isAttackingWhitePawn1 = (temp1->getColor() == WHITE && temp1->getPiece() == PAWN);
        bool isAttackingWhitePawn2 = (temp2->getColor() == WHITE && temp2->getPiece() == PAWN);

        if(isAttackingWhitePawn1) {
            attackers.push_back(make_pair(temp1->getx(), temp1->gety()));
        }

        if(isAttackingWhitePawn2) {
            attackers.push_back(make_pair(temp2->getx(), temp2->gety()));
        }
    }
    return attackers;
}
vector<pair<int,int>> Board::isKingAttacker(Square*square) {
    int currx = square->getx();
    int curry = square->gety();

    vector<pair<int, int>> pairs;
    pairs.push_back(make_pair(-1, -1));
    pairs.push_back(make_pair(-1, 0));
    pairs.push_back(make_pair(-1, 1));
    pairs.push_back(make_pair(0, -1));
    pairs.push_back(make_pair(0, 1));
    pairs.push_back(make_pair(1, -1));
    pairs.push_back(make_pair(1, 0));
    pairs.push_back(make_pair(1, 1));

    vector<pair<int, int>> searched_pairs;

    for(int i = 0; i < pairs.size(); i++) {
        int tempx = currx + pairs[i].first;
        int tempy = curry + pairs[i].second;
        bool onboard = isInRange(tempx, tempy);
        if(onboard) {
            searched_pairs.push_back(pairs[i]);
        }
    }

    vector<pair<int, int>> attackers;
    for(int i = 0; i < searched_pairs.size(); i++) {
        int tempx = currx + searched_pairs[i].first;
        int tempy = curry + searched_pairs[i].second;
        Square* temp = getSquare(tempx, tempy);
        bool isAttckingKnight = (temp->getPiece() == KING) && (temp->getColor() != moveColor);
        if(isAttckingKnight) {
            attackers.push_back(make_pair(tempx, tempy));
        }
    }

    return attackers;
}
vector<pair<int,int>> Board::isSquareAttack(Square*s) {
    //coutTab(5);
    //cout << "isSquareAttack()" << endl;
    vector<pair<int,int>> bishops = isBishopAttacker(s);
    vector<pair<int,int>> rooks = isRookAttacker(s);
    vector<pair<int,int>> knights = isKnightAttacker(s);
    vector<pair<int,int>> pawns = isPawnAttacker(s);
    vector<pair<int,int>> kings = isKingAttacker(s);
    
    vector<pair<int,int>> all;
    for(int i = 0; i < bishops.size(); i++) {
        if(isInRange(bishops[i].first, bishops[i].second)) {
            all.push_back(bishops[i]);
        }
    }
    for(int i = 0; i < rooks.size(); i++) {
        if(isInRange(rooks[i].first, rooks[i].second)) {
            all.push_back(rooks[i]);
        }
    }
    for(int i = 0; i < knights.size(); i++) {
        if(isInRange(knights[i].first, knights[i].second)) {
            all.push_back(knights[i]);
        }
    }
    for(int i = 0; i < pawns.size(); i++) {
        if(isInRange(pawns[i].first, pawns[i].second)) {
            all.push_back(pawns[i]);
        }
    }
    for(int i = 0; i < kings.size(); i++) {
        if(isInRange(kings[i].first, kings[i].second)) {
            all.push_back(kings[i]);
        }
    }
    //coutTab(5);
    //cout << "attackers size: "<< all.size() << endl;
    return all;
}


void Board::print() {
    cout <<"-------------"<< endl;
    if(isCheckmate()) {
        cout << "CHECKMATE" << endl;
    } else if (isDraw()) {
        cout << "DRAW" << endl;
    } 
    else {
        cout << moveColor << " to move." << endl;
    }
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            board[x][y].printSquare();
        }
        cout << endl;
    }
    cout <<"-------------"<< endl << endl;
}

string Board::boardString() {
    string p = "-------------\n";
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            p += board[x][y].printString();
        }
        p += "\n";
    }
    p += "-------------\n";
    return p;
}

string Board::getFEN() {
    string fen = "";
    int counter = 0;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            Square* temp = getSquare(y, x);
            if(temp->getPiece() != EMPTY) {
                if(counter) {
                    fen.append(to_string(counter));
                    counter = 0;
                }
                fen.append(temp->printString());
            } else {
                counter++;
            }
        }
        if(counter) {
            fen.append(to_string(counter));
            counter = 0;
        }
        if(x != 7) {
            fen.append("/");
        }
    }


    if(moveColor == WHITE) { fen += " w ";} 
    else if(moveColor == BLACK) { fen += " b "; } 
    else { fen += " - "; }

    if(wKQ_bkq[0]) { fen += "K"; }
    if(wKQ_bkq[1]) { fen += "Q"; }
    if(wKQ_bkq[2]) { fen += "k"; }
    if(wKQ_bkq[3]) { fen += "q"; }
    if(!wKQ_bkq[0] && !wKQ_bkq[1] && !wKQ_bkq[2] && !wKQ_bkq[3]) { fen += "-"; }

    if(enpassantTarget != MOVE) { fen += " " + notationToString(enpassantTarget); }
    else{ fen += " -"; }

    fen += " " + to_string(halfTurnNum) + " " + to_string(fullTurnNum);

    return fen;
}

Square* Board::getSquare(Piece p, Color c) {
    Square* temp;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            temp = getSquare(i, j);
            if(temp->getColor() == c && temp->getPiece() == p) {
                break;
            }
        }
    }
    return temp;
}

Square* Board::getSquare(Notation strsq) {
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
        case a8Q: x=0; y=0;break;
        case a8R: x=0; y=0;break;
        case a8B: x=0; y=0;break;
        case a8N: x=0; y=0;break;
        case b8Q: x=1; y=0;break;
        case b8R: x=1; y=0;break;
        case b8B: x=1; y=0;break;
        case b8N: x=1; y=0;break;
        case c8Q: x=2; y=0;break;
        case c8R: x=2; y=0;break;
        case c8B: x=2; y=0;break;
        case c8N: x=2; y=0;break;
        case d8Q: x=3; y=0;break;
        case d8R: x=3; y=0;break;
        case d8B: x=3; y=0;break;
        case d8N: x=3; y=0;break;
        case e8Q: x=4; y=0;break;
        case e8R: x=4; y=0;break;
        case e8B: x=4; y=0;break;
        case e8N: x=4; y=0;break;
        case f8Q: x=5; y=0;break;
        case f8R: x=5; y=0;break;
        case f8B: x=5; y=0;break;
        case f8N: x=5; y=0;break;
        case g8Q: x=6; y=0;break;
        case g8R: x=6; y=0;break;
        case g8B: x=6; y=0;break;
        case g8N: x=6; y=0;break;
        case h8Q: x=7; y=0;break;
        case h8R: x=7; y=0;break;
        case h8B: x=7; y=0;break;
        case h8N: x=7; y=0;break;
        case a1q: x=0; y=7;break;
        case a1r: x=0; y=7;break;
        case a1b: x=0; y=7;break;
        case a1n: x=0; y=7;break;
        case b1q: x=1; y=7;break;
        case b1r: x=1; y=7;break;
        case b1b: x=1; y=7;break;
        case b1n: x=1; y=7;break;
        case c1q: x=2; y=7;break;
        case c1r: x=2; y=7;break;
        case c1b: x=2; y=7;break;
        case c1n: x=2; y=7;break;
        case d1q: x=3; y=7;break;
        case d1r: x=3; y=7;break;
        case d1b: x=3; y=7;break;
        case d1n: x=3; y=7;break;
        case e1q: x=4; y=7;break;
        case e1r: x=4; y=7;break;
        case e1b: x=4; y=7;break;
        case e1n: x=4; y=7;break;
        case f1q: x=5; y=7;break;
        case f1r: x=5; y=7;break;
        case f1b: x=5; y=7;break;
        case f1n: x=5; y=7;break;
        case g1q: x=6; y=7;break;
        case g1r: x=6; y=7;break;
        case g1b: x=6; y=7;break;
        case g1n: x=6; y=7;break;
        case h1q: x=7; y=7;break;
        case h1r: x=7; y=7;break;
        case h1b: x=7; y=7;break;
        case h1n: x=7; y=7;break;
    }
    Square* sq = getSquare(x, y);
    return sq;
}

Square* Board::getSquare(int x, int y) {
    return &board[x][y];
}

Notation Board::getNotation(int x, int y) {
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