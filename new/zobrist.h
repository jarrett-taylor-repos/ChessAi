#include <random>
#include "Board.cpp"
using namespace std;

long long int largerandom(){
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}


array<array<array<long long int,12>,8>,8> initialize(){
    array<array<array<long long int,12>,8>,8> zarray;
    for (int i=0; i<8; i++){
        for (int j=0; j<8;j++){
            for (int k=0; k<12; k++){
                zarray[i][j][k] = largerandom();
            }
        }
    }
    return zarray;
}

int Square2Int(Square sqr){
    int iter;
    Piece piecee = sqr->getPiece();
    switch(piecee){
        
        case PAWN:
            iter = 0;
            break;
        case KNIGHT:
            iter = 1;
            break;
        case BISHOP:
            iter = 2;
            break;
        case ROOK:
            iter = 3;
            break;
        case QUEEN:
            iter = 4;
            break;
        case KING:
            iter = 5;
            break;
        default:
            return -1;
    }
    Color colorr = sqr->getColor();
    if (colorr==BLACK){
        iter+=6;
    }
    return iter;
    
}

array<long long int,3> board2zvals(Board b,array<array<array<long long int,12>,8>,8> zarray){
    long long int zval = 0;
    int materialadv = 0;
    array<int,12> materialevals = {1,3,3,5,9,36,-1,-3,-3,-5,-9,-36};
    
    for (int i=0; i<8; i++){
        for (int j=0; j<8;j++){
            Square* sqr = getSquare(i,j);

            if (sqr->getPiece()!=EMPTY) {
                int iter = Square2Int(Square sqr);
                zval = zval^zarray[i][j][iter];
                materialadv += materialevals[iter];
            }

        }
    }
    return {zval,materialadv,0}
}

