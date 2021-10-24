//#include "Board.cpp"
#include "zobrist.cpp"

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

int alphaBeta(int alpha, int beta, int depthleft, vector<long long int> movestack,array<array<array<long long int,12>,8>,9> zarray,zstuff zobriststuff) {
    Board b = zobriststuff.b;
   if( depthleft == 0 ) return evaluate(b, alpha, beta );
   vector<pair<Notation, Notation>> allmoves = b.getAllMovesVector();
   for (int i = 0; i < allmoves.size(); i++)  {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        zstuff newzobriststuff = zmove(n1,n2,zobriststuff,zarray);
        Board b2 = newzobriststuff.b;
        if(!(find(movestack.begin(), movestack.end(), newzobriststuff.zval) != movestack.end())){ //MOVE IS NOT REPEAT
            movestack.push_back(newzobriststuff.zval);
            int score = -alphaBeta(-beta, -alpha, depthleft - 1,movestack,zarray,newzobriststuff);
            movestack.pop_back();
            if( score >= beta )
                
                return beta;   //  fail hard beta-cutoff
            if( score > alpha )
                alpha = score; // alpha acts like max in MiniMax

        }
   }
   return alpha;
}

pair<Notation, Notation> rootsearch(Board b,vector<long long int> movestack,array<array<array<long long int,12>,8>,9> zarray){
    int alpha = -999999999;
    int beta = 999999999;
    zstuff ogzobriststuff = board2zvals(b,zarray);
    pair<Notation, Notation> bestmove;
    vector<pair<Notation, Notation>> allmoves = b.getAllMovesVector();
    for(int i = 0; i < allmoves.size(); i++) {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        //cout<<"testing:"<<n1<<n2<<endl;
        // string FEN = b.getFEN();
        // Board b2;
        // b2.loadFEN(FEN);
        zstuff zobriststuff = zmove(n1,n2,ogzobriststuff,zarray);
        Board b2 = zobriststuff.b;
        if(find(movestack.begin(), movestack.end(), zobriststuff.zval) != movestack.end()){
            cout<<"found repeat";
        }
        
        if(!(find(movestack.begin(), movestack.end(), zobriststuff.zval) != movestack.end())){ //MOVE IS NOT REPEAT
            //make move
            movestack.push_back(zobriststuff.zval);
            int score = -alphaBeta(-beta,-alpha,2,movestack,zarray,zobriststuff);
            if (score>alpha) {
                alpha = score;
                bestmove = make_pair(n1,n2); //
            }
            movestack.pop_back();
        }   
    }
    return bestmove;
}

int playgame(){
    Board b;
    array<array<array<long long int,12>,8>,9> zarray = initialize();

    cout <<b.getFEN()<<endl;
    bool gn = !b.isGameOver();
    vector<long long int> movestack;
    while (gn){
        zstuff zobriststuff = board2zvals(b,zarray);
        movestack.push_back(zobriststuff.zval);
        pair<Notation, Notation> move = rootsearch(b,movestack,zarray);

        b.makeMove(move.first,move.second);
        cout << b.getFEN()<<endl;
        
        gn = !b.isGameOver();
    }
    for (int i =0;i<movestack.size();i++){
        cout <<movestack[i]<<endl;
    }
    return 0;
}

Board testfun(Board b){
    b.makeMove(e2,e4);
    return b;
}

int main() {
    cout<<"STARTING"<<endl;
    playgame();

    // Board b;
    // array<array<array<long long int,12>,8>,9> zarray = initialize();
    // zstuff zobriststuff = board2zvals(b,zarray);
    // cout<<zobriststuff.zval<<b.getFEN()<<endl;
    // zobriststuff = zmove(b,a1,a2,zobriststuff,zarray);
    // cout<<zobriststuff.zval<<b.getFEN()<<endl;
    // Board b2;
    // b2.loadFEN(b.getFEN());
    // zobriststuff = board2zvals(b,zarray);
    // cout<<zobriststuff.zval<<endl;

    // Board b;
    // cout<<b.getFEN()<<endl;
    // Board b2 = testfun(b);
    // cout<<b.getFEN();
    // cout<<endl<<b2.getFEN();
    // cout<<"done";

}

