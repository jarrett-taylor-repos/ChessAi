#include "square.cpp"


class ChessBoard {
    private:
        Square chessboard[8][8];
        pair<stringSquare,stringSquare> moves[1000];
        string allFENs[1000];
        int turnColor; // 0 is white, 1 is black
        int turnNum;
        bool hasa1rookmoved = false;
        bool hash1rookmoved = false;
        bool hasa8rookmoved = false;
        bool hash8rookmoved = false;
        bool hase1kingmoved = false;
        bool hase8kingmoved = false;


    public:
        ChessBoard();
        ChessBoard(string fen);
        string getBoardFEN();


        void makeMove(stringSquare strstart, stringSquare strend);

        bool canMakeMove(Square* start, Square* end);
        bool canKingMove(Square* start, Square* end);
        bool canQueenMove(Square* start, Square* end);
        bool canRookMove(Square* start, Square* end);
        bool canBishopMove(Square* start, Square* end);
        bool canKnightMove(Square* start, Square* end);
        bool canPawnMove(Square* start, Square* end);
        bool canCastleShort(Color c);
        bool canCastleLong(Color c);
        void effectCastling(stringSquare move);


        pair<int, int> movetHelper(int tempx, int tempy, Square* sq);
        vector<pair<int, int>> getPawns(Square* pawn);
        vector<pair<int, int>> getKnights(Square* knight);
        vector<pair<int, int>> getKings(Square* king);
        vector<pair<int, int>> getDiagonals(Square* start);
        vector<pair<int, int>> getVerticalsandHorizontals(Square* start);


        void printAllMoves();
        void printTurnandMove();
        void printBoard();


        Color getColorfromTurn();
        void setTurnColor(int t);


        Square* getSquare(stringSquare strsq);
        Square* getSquare(int x, int y);
};

//constructors
ChessBoard::ChessBoard(){ //WORKING
        turnNum = 0;
        turnColor = 0;

        for(int i = 0; i < 1000; i++) {
            moves[i] = make_pair(MOVE, MOVE);
            allFENs[i] = "";
        }

        for(int y = 0; y < 8; y++) {
            for(int x = 0; x < 8; x++) {
                chessboard[y][x].setPieceandColor(EMPTY, NONE);
                chessboard[y][x].setxy(y, x);
            }
        }

        chessboard[0][0].setPieceandColor(ROOK, BLACK);
        chessboard[1][0].setPieceandColor(KNIGHT, BLACK);
        chessboard[2][0].setPieceandColor(BISHOP, BLACK);
        chessboard[3][0].setPieceandColor(QUEEN, BLACK);
        chessboard[4][0].setPieceandColor(KING, BLACK);
        chessboard[5][0].setPieceandColor(BISHOP, BLACK);
        chessboard[6][0].setPieceandColor(KNIGHT, BLACK);
        chessboard[7][0].setPieceandColor(ROOK, BLACK);

        chessboard[0][7].setPieceandColor(ROOK, WHITE);
        chessboard[1][7].setPieceandColor(KNIGHT, WHITE);
        chessboard[2][7].setPieceandColor(BISHOP, WHITE);
        chessboard[3][7].setPieceandColor(QUEEN, WHITE);
        chessboard[4][7].setPieceandColor(KING, WHITE);
        chessboard[5][7].setPieceandColor(BISHOP, WHITE);
        chessboard[6][7].setPieceandColor(KNIGHT, WHITE);
        chessboard[7][7].setPieceandColor(ROOK, WHITE);

        for (int i = 0; i < 8; i++) {
            chessboard[i][1].setPieceandColor(PAWN, BLACK);
            chessboard[i][6].setPieceandColor(PAWN, WHITE);

        }
    }

ChessBoard::ChessBoard(string fen) { //set board from fen, WORKING
    turnNum = 0;
    for(int i = 0; i < 1000; i++) {
        moves[i] = make_pair(MOVE, MOVE);
        allFENs[i] = "";
    }

    for(int file = 0; file < 8; file++) {
        for(int rank = 0; rank < 8; rank++) {
            chessboard[rank][file].setPieceandColor(EMPTY, NONE);
            chessboard[rank][file].setxy(file, rank);
        }
    }

    int position = 0;
    for(int i = 0; i < fen.length(); i++) {
        char ch = fen[i];
        bool isNum = isdigit(ch);
        if (isNum) {
        int chval = (int) ch - '0';
        for(int j = 0; j < chval; j++) {
            int temppos = position + j;
            vector<int> location = getFileRank(temppos);
            int f = location[0];
            int r = location[1];

            chessboard[f][r].setPieceandColor(EMPTY, NONE);
            //chessboard[f][r].printSquare();
        } 
        position += chval;
        } else if(ch != '/') {
        //cout << " isLetter " ;
        vector<int> location = getFileRank(position);
        int f = location[0];
        int r = location[1];

        Piece p = getPieceByLetter(ch);
        Color c = getColorByLetter(ch);
        chessboard[f][r].setPieceandColor(p, c);
        //chessboard[f][r].printSquare();

        position++;
        } else {
        //useless
        }
    }

}

//get fen
string ChessBoard::getBoardFEN() {
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
                    fen.append(temp->getSquareString());
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
        return fen;
    }


//make move
void ChessBoard::makeMove(stringSquare strstart, stringSquare strend) {
    Square* start = getSquare(strstart);
    Square* end = getSquare(strend);
    bool rightColorMove = (getColorfromTurn() == start->getColor());
    if(canMakeMove(start, end) && rightColorMove) { //check would go here?
        moves[turnNum] = make_pair(strstart, strend);
        turnNum++;

        //en passant same as castling in here to check move space?
        bool isMoveCastling = (strstart == e1 && strend == g1) ||
            (strstart == e1 && strend == c1) ||
            (strstart == e8 && strend == c8) ||
            (strstart == e8 && strend == g8);
        if(isMoveCastling) {
            if(strend == g1) {//need to set 2 squares to king and rook, set other 2 squares to empty
                Square* square_g1 = getSquare(g1);
                Square* square_f1 = getSquare(f1);
                square_g1->setPieceandColor(KING, WHITE);
                square_f1->setPieceandColor(ROOK, WHITE);

                Square* square_e1 = getSquare(e1);
                Square* square_h1 = getSquare(h1);
                square_e1->setEmpty();
                square_h1->setEmpty();
            } else if (strend == c1) {
                Square* square_c1 = getSquare(c1);
                Square* square_d1 = getSquare(d1);
                square_c1->setPieceandColor(KING, WHITE);
                square_d1->setPieceandColor(ROOK, WHITE);

                Square* square_e1 = getSquare(e1);
                Square* square_a1 = getSquare(a1);
                square_e1->setEmpty();
                square_a1->setEmpty();
            } else if (strend == c8) {
                Square* square_c8 = getSquare(c8);
                Square* square_d8 = getSquare(d8);
                square_c8->setPieceandColor(KING, BLACK);
                square_d8->setPieceandColor(ROOK, BLACK);

                Square* square_e8 = getSquare(e8);
                Square* square_a8 = getSquare(a8);
                square_e8->setEmpty();
                square_a8->setEmpty();
            } else { // strend == g8
                Square* square_g8 = getSquare(g8);
                Square* square_f8 = getSquare(f8);
                square_g8->setPieceandColor(KING, BLACK);
                square_f8->setPieceandColor(ROOK, BLACK);

                Square* square_e8 = getSquare(e8);
                Square* square_h8 = getSquare(h8);
                square_e8->setEmpty();
                square_h8->setEmpty();
            }
        } else {
            end->setPieceandColor(start->getPiece(), start->getColor());
            start->setEmpty();
        }
        if(turnColor==1) {
            setTurnColor(0);
        } else {
            setTurnColor(1);
        }
        effectCastling(strstart);
        effectCastling(strend);
    } else {
        cout << "CAN'T MAKE THAT MOVE! Try another move." << endl;
    }
}


//bool moves
bool ChessBoard::canMakeMove(Square* start, Square* end) {

    switch(start->getPiece()) { //need to check if actually legal
        case KING:
            return canKingMove(start, end);
            break;
        case QUEEN:
            return canQueenMove(start, end);
            break;
        case ROOK:
            return canRookMove(start, end);
            break;
        case BISHOP:
            return canBishopMove(start, end);
            break;
        case KNIGHT:
            return canKnightMove(start, end);
            break;
        case PAWN:
            return canPawnMove(start, end);
            break;
        default:
            return 0;
    }
}

bool ChessBoard::canKingMove(Square* king, Square* end) { //need to see if inCheck, if next move is also check
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);

    int kingx = king->getx();
    int kingy = king->gety();

    vector<pair<int, int>> kingmoves = getKings(king);
    return isPairInList(endxy, kingmoves);
}

bool ChessBoard::canQueenMove(Square* queen, Square* end) {
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);
    vector<pair<int, int>> rookMoves = getVerticalsandHorizontals(queen);
    vector<pair<int, int>> bishopMoves = getDiagonals(queen);
    return isPairInList(endxy, rookMoves) || isPairInList(endxy, bishopMoves);
}

bool ChessBoard::canBishopMove(Square* bishop, Square* end) {
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);
    vector<pair<int, int>> bishopMoves = getDiagonals(bishop);
    return isPairInList(endxy, bishopMoves);
}

bool ChessBoard::canRookMove(Square* rook, Square* end) { //need castling, long and short
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);
    vector<pair<int, int>> rookMoves = getVerticalsandHorizontals(rook);
    return isPairInList(endxy, rookMoves);
}

bool ChessBoard::canKnightMove(Square* knight, Square* end) {
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);
    vector<pair<int, int>> knightMoves = getKnights(knight);
    return isPairInList(endxy, knightMoves);
}

bool ChessBoard::canPawnMove(Square* pawn, Square* end) {//need en passant, promotion
    int endx = end->getx();
    int endy = end->gety();
    pair<int, int> endxy = make_pair(endx, endy);
    vector<pair<int, int>> pawnMoves = getPawns(pawn);
    return isPairInList(endxy, pawnMoves);
}

bool ChessBoard::canCastleShort(Color c) { //need to check if castling into or though check
    if(c == BLACK) {
        bool empty_squares = (getSquare(f8)->getPiece() == EMPTY) && (getSquare(g8)->getPiece() == EMPTY);
        if(empty_squares && !hash8rookmoved && !hase8kingmoved) {
            return true;
        } 
        return false;
    } else {
        bool empty_squares = (getSquare(f1)->getPiece() == EMPTY) && (getSquare(g1)->getPiece() == EMPTY);
        if(empty_squares && !hash1rookmoved && !hase1kingmoved) {
            return true;
        } 
        return false;
    }
}

bool ChessBoard::canCastleLong(Color c) { //need to check if castling into or though check
    if(c == BLACK) {
        bool empty_squares = (getSquare(b8)->getPiece() == EMPTY) && (getSquare(c8)->getPiece() == EMPTY) && (getSquare(d8)->getPiece() == EMPTY);
        if(empty_squares && !hasa8rookmoved && !hase8kingmoved) {
            return true;
        } 
        return false;
    } else {
        bool empty_squares = (getSquare(b1)->getPiece() == EMPTY) && (getSquare(c1)->getPiece() == EMPTY) && (getSquare(d1)->getPiece() == EMPTY);
        if(empty_squares && !hasa1rookmoved && !hase1kingmoved) {
            return true;
        } 
        return false;
    }
}

void ChessBoard::effectCastling(stringSquare move) {
    stringSquare castles[6] = {a1, a8, h1, h8, e1, e8};
    switch(move) {
        case a1:
            hasa1rookmoved = true;
            break;
        case a8:
            hasa8rookmoved = true;
            break;
        case h1:
            hash1rookmoved = true;
            break;
        case h8:
            hash8rookmoved = true;
            break;
        case e1:
            hase1kingmoved = true;
            break;
        case e8:
            hase8kingmoved = true;
            break;
        default:
            break;
    }
}


//move helpers
pair<int, int> ChessBoard::movetHelper(int tempx, int tempy, Square* sq) {
    pair<int, int> p = make_pair(-1, -1);
    if(7>=tempx && tempx >=0 && 7>= tempy && tempy>=0) {
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

vector<pair<int, int>> ChessBoard::getPawns(Square* pawn) { //need en passant
    //cout << "getPawns" << endl;
    vector<pair<int, int>> pawns;
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
        if(cap1->getPiece() != EMPTY && cap1->getColor() != pawn->getColor()) {
            temp = make_pair(x-1, y-1);
            pawns.push_back(temp);
        }

        Square* cap2 = getSquare(x+1, y-1);
        if(cap2->getPiece() != EMPTY && cap2->getColor() != pawn->getColor()) {
            temp = make_pair(x+1, y-1);
            pawns.push_back(temp);
        }


        Square* sq1 = getSquare(x, y-1);
        if(sq1->getPiece() == EMPTY) {
            temp = make_pair(x, y-1);
            pawns.push_back(temp);
            Square* sq2 = getSquare(x, y-2);
            if(pawn->gety() == 6 && sq2->getPiece() == EMPTY) {
                temp = make_pair(x, y-2);
                pawns.push_back(temp);
            }

        }
        
    } else {
        capture.push_back(make_pair(-1, 1));
        capture.push_back(make_pair(1, 1));
        Square* cap1 = getSquare(x-1, y+1);
        if(cap1->getPiece() != EMPTY && cap1->getColor() != pawn->getColor()) {
            temp = make_pair(x-1, y+1);
            pawns.push_back(temp);
        }

        Square* cap2 = getSquare(x+1, y+1);
        if(cap2->getPiece() != EMPTY && cap2->getColor() != pawn->getColor()) {
            temp = make_pair(x+1, y+1);
            pawns.push_back(temp);
        }


        Square* sq1 = getSquare(x, y+1);
        if(sq1->getPiece() == EMPTY) {
            temp = make_pair(x, y+1);
            pawns.push_back(temp);
            Square* sq2 = getSquare(x, y+2);
            if(pawn->gety() == 1 && sq2->getPiece() == EMPTY) {
                temp = make_pair(x, y+2);
                pawns.push_back(temp);
            }

        }
    }

    return pawns;
}

vector<pair<int, int>> ChessBoard::getKnights(Square* knight) {
    //cout << "getKnights" << endl;
    vector<pair<int, int>> knights;
    int x = knight->getx();
    int y = knight->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

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
        pair<int, int> temp = movetHelper(x+pairs[i].first, y+pairs[i].second, knight);
        if(temp.first != -1) { //(-1, -2)
            knights.push_back(temp);
        }
    }
    
    return knights;
}

vector<pair<int, int>> ChessBoard::getKings(Square* king) {//need cant castle though or into check 
    //cout << "getKings" << endl;
    vector<pair<int, int>> kings;
    int x = king->getx();
    int y = king->gety();
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
    //-cant castle through check, WILL BE DONE LATER 
    if(canCastleShort(king->getColor())) { //short castle move
        pairs.push_back(make_pair(2, 0));
    }
    if(canCastleLong(king->getColor())) { //long castle move
        pairs.push_back(make_pair(-2, 0));
    }


    for(int i = 0; i < pairs.size(); i++) {
        pair<int, int> temp = movetHelper(x+pairs[i].first, y+pairs[i].second, king);
        if(temp.first != -1) {
            kings.push_back(temp);
        }
    }
    return kings;
}

vector<pair<int, int>> ChessBoard::getDiagonals(Square* start) {
    //cout << "getDiagonals" << endl;
    vector<pair<int, int>> diags;
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
            diags.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        diags.push_back(temppair);
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
            diags.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        diags.push_back(temppair);
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
            diags.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        diags.push_back(temppair);
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
            diags.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(tempx, tempy);
        diags.push_back(temppair);
    }
    return diags;
    
}

vector<pair<int, int>> ChessBoard::getVerticalsandHorizontals(Square* start) {
    //cout << "getVerticalsandHorizontals" << endl;
    vector<pair<int, int>> rookmoves;
    int x = start->getx();
    int y = start->gety();
    //cout << " - x, y: " << x << ", " << y << endl;

    for(int i = x+1; i < 8; i++) { //check files positive
        Square* temp = getSquare(i, y);
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(i, y);
            rookmoves.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(i, y);
        rookmoves.push_back(temppair);
    }
    for(int i = x-1; i >= 0; i--) { //check files negative
        Square* temp = getSquare(i, y);
        if(start->getColor() == temp->getColor() ) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(i, y);
            rookmoves.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(i, y);
        rookmoves.push_back(temppair);
    }
    for(int i = y-1; i >= 0; i--) { //check rank negative
        Square* temp = getSquare(x, i);;
        if(start->getColor() == temp->getColor()) {//check for same color piece color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(x, i);
            rookmoves.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(x, i);
        rookmoves.push_back(temppair);
    }
    for(int i = y+1; i < 8; i++) { //check rank positive
        Square* temp = getSquare(x, i);;
        if(start->getColor() == temp->getColor()) {//check if not color
            break;
        } else if (start->getColor() != temp->getColor() && temp->getColor() != NONE) {//check for opposite color piece, BLACK and WHITE
            pair<int, int> temppair = make_pair(x, i);
            rookmoves.push_back(temppair);
            break;
        }
        pair<int, int> temppair = make_pair(x, i);
        rookmoves.push_back(temppair);
    }
    return rookmoves;
}


//printing
void ChessBoard::printAllMoves() {
    for(int i = 0; i < 1000; i++) {
        if(moves[i].first == MOVE) {
            break;
        }
        cout << moves[i].first << moves[i].second << endl;
    }
}

void ChessBoard::printTurnandMove() {
    switch(turnColor) {
        case 0:
            cout << "WHITE to move." << endl;
            break;
        case 1:
            cout << "BLACK to move." << endl;
            break;
    }
}

void ChessBoard::printBoard() { //IS WORKING
    cout <<"-------------"<< endl;
    printTurnandMove();
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            chessboard[x][y].printSquare();
        }
        cout << endl;
    }
    cout <<"-------------"<< endl << endl;
}


//color
Color ChessBoard::getColorfromTurn() {
    if(turnColor==1) {
        return BLACK;
    } else {
        return WHITE;
    }
}

void ChessBoard::setTurnColor(int t) {
    turnColor=t;
}


//return square
Square* ChessBoard::getSquare(int x, int y) {
    return &chessboard[x][y];
}

Square* ChessBoard::getSquare(stringSquare strsq) {
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