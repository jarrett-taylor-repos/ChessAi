#include <random>
#include "zstuff.cpp"
#include "Zobristclass.cpp"
using namespace std;


long long int largerandom(){
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0,0xFFFFFFFFFFFFFFFF);

    return distribution(generator);
}


array<array<array<long long int,12>,8>,9> initialize(){
    array<array<array<long long int,12>,8>,9> zarray;
    for (int i=0; i<9; i++){
        for (int j=0; j<8;j++){
            for (int k=0; k<12; k++){
                zarray[i][j][k] = largerandom();
            }
        }
    }
    return zarray;
}

int Square2Int(Square* sqr){
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

zstuff board2zvals(Board b,array<array<array<long long int,12>,8>,9> zarray){
    long long int zval = 0;
    int materialadv = 0;
    array<int,12> materialevals = {1,3,3,5,9,36,-1,-3,-3,-5,-9,-36};
    
    for (int i=0; i<8; i++){
        for (int j=0; j<8;j++){
            Square* sqr = b.getSquare(i,j);

            if (sqr->getPiece()!=EMPTY) {
                int iter = Square2Int(sqr);
                zval = zval^zarray[i][j][iter];
                materialadv += materialevals[iter];
            }

        }
    }

    if (b.getMoveColor()==BLACK){
        zval^zarray[9][0][0];
    }

    //TODO: Cating rights and shit

    return zstuff(zval,materialadv);
}


zstuff zmove(Board &b,Notation first,Notation second,zstuff zobriststuff,array<array<array<long long int,12>,8>,9> zarray){
    int materialadv = zobriststuff.materialadv;
    long long int zval = zobriststuff.zval;
    array<int,12> materialevals = {1,3,3,5,9,36,-1,-3,-3,-5,-9,-36};
    
    Square* sqr = b.getSquare(first);
    
    int firstpiece = Square2Int(sqr);
    zval=zval^zarray[sqr->getx()][sqr->gety()][firstpiece]; //removing old piece

    //is there a piece at new loc
    sqr = b.getSquare(second);
    int secondpiece = Square2Int(sqr);   
    
    if (secondpiece != -1){ //capture
        zval = zval^zarray[sqr->getx()][sqr->gety()][secondpiece];
        materialadv -= materialevals[secondpiece];
    }
    
    
    bool movemade = b.makeMove(first,second);
    sqr = b.getSquare(second);
    secondpiece = Square2Int(sqr);

    if(b.getWasEnpassant()){
        if (b.getMoveColor()==WHITE){
            materialadv -= 1;
            zval = zval^zarray[sqr->getx()][6][0];
        }
        else {
            materialadv+=1;
            zval = zval^zarray[sqr->getx()][3][6];
        }
    }

    if(b.getWasPromo()){
        if (secondpiece<6){ //white
            materialadv+=materialevals[secondpiece]-1;
            zval = zval^zarray[sqr->getx()][sqr->gety()][secondpiece];
        }
        else{
            materialadv-=materialevals[secondpiece]+1;
            zval = zval^zarray[sqr->getx()][sqr->gety()][secondpiece];
        }
    }
    else{
        zval = zval^zarray[sqr->getx()][sqr->gety()][secondpiece];
    }

    if (b.getWasCastle()) {
        if (second == g1){
            zval = zval^zarray[7][7][3]^zarray[5][7][3];
        }
        else if (second == a1) {
            zval = zval^zarray[0][7][3]^zarray[3][7][3];
        }
        else if (second == c8) {
            zval = zval^zarray[0][0][9]^zarray[3][0][9];
        }
        else {
            zval = zval^zarray[7][0][9]^zarray[5][0][9];
        }
    }

    zval = zval^zarray[8][0][0];

    return zstuff(zval,materialadv);

}

bool inside(vector<long long int> v, long long int a){
    for (int i = 0; i<v.size();i++){
        //cout<<v[i]<<'-'<<a<<endl;
        if (v[i] == a){
            return true;
        }
    }
    return false;
}

