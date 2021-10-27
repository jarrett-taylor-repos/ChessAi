

class Zobrist {
    public:
        long long int zval;
        int materialadv;
        string FEN;
        int depth;
        int marker; //extact, upper, or lower cutoff
        int eval;
        Zobrist(long long int zvall,int materialadvv,string FENN, int depthh, int markerr, int evall);
};

Zobrist::Zobrist(long long int zvall,int materialadvv,string FENN, int depthh, int markerr, int evall){
    zval = zvall;
    materialadv = materialadvv;
    FEN = FENN;
    depth = depthh;
    marker = markerr;
    eval = evall;
}