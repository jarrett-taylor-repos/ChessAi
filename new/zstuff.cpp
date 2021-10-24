#include "Board.cpp"

class zstuff{
    public:
    long long int zval;
    int materialadv;
    Board b;
    zstuff(long long int zval,int materialadv, Board b);
};

zstuff::zstuff(long long int zvall,int materialadvv, Board bb){
    zval = zvall;
    materialadv = materialadvv;
    b = bb;
}