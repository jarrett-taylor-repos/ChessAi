
#include "Board.cpp"

int findmaterial(string fen) {
    vector<string> fenn = split(fen, " ");
    int p = 0;
    fen = fenn[0];
    for (int i = 0; i < fen.length(); i++) {
        char charr = fen[i];
        switch(charr) {
            case 'q': p += -9; break;
            case 'Q': p += 9; break;
            case 'r': p += -5; break;
            case 'R': p += 5; break;
            case 'b': p += -3; break;
            case 'B': p += 3; break;
            case 'n': p += -3; break;
            case 'N': p += 3; break;
            case 'p': p += -1; break;
            case 'P': p += 1; break;
            default: break;
        }
    }
    return p;
}

int evaluate(Board b, int alpha, int beta) {
    string fen = b.getFEN();
    Color turn = b.getMoveColor();
    if (turn == WHITE){
        return findmaterial(fen);
    }
    else {
        return -findmaterial(fen);
    }
}

int alphaBeta(Board b,int alpha, int beta, int depthleft ) {
   if( depthleft == 0 ) return evaluate(b, alpha, beta );
   vector<pair<Notation, Notation>> allmoves = b.getAllMovesVector();
   for (int i = 0; i < allmoves.size(); i++)  {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        Board b2;
        b2.loadFEN(b.getFEN());
        b2.makeMove(n1,n2);
        int score = -alphaBeta(b2, -beta, -alpha, depthleft - 1 );
        if( score >= beta )
            return beta;   //  fail hard beta-cutoff
        if( score > alpha )
            alpha = score; // alpha acts like max in MiniMax
   }
   return alpha;
}

pair<Notation, Notation> rootsearch(Board b){
    int alpha = -999999999;
    int beta = 999999999;
    pair<Notation, Notation> bestmove;
    vector<pair<Notation, Notation>> allmoves = b.getAllMovesVector();
    for(int i = 0; i < allmoves.size(); i++) {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        //cout<<"testing:"<<n1<<n2<<endl;
        string FEN = b.getFEN();
        Board b2;
        b2.loadFEN(FEN);
        b2.makeMove(n1,n2);
        
        //make move
        int score = -alphaBeta(b2,-beta,-alpha,2);
        if (score>alpha) {
            alpha = score;
            bestmove = make_pair(n1,n2); //
        }
    }
    return bestmove;
}

int playgame(){
    Board b;
    cout << b.getFEN()<<endl;
    bool gn = !b.isGameOver();
    while (gn){
        //cout<<b.getMoveColor()<<endl;
        pair<Notation, Notation> move = rootsearch(b);
        //cout<<"FOUND MOVE";
        //cout<<move.first<<move.second<<endl;
        b.makeMove(move.first,move.second);
        cout << b.getFEN()<<endl;
        //cout<<b.getMoveColor()<<endl;
        //cout<<endl<<endl;
        //b.print();
        
        gn = !b.isGameOver();
    }
    return 0;
}

int main() {
    cout<<"STARTING"<<endl;
    playgame();

}

