//#include "Board.cpp"
#include "zobrist.cpp"
#include <direct.h>
#include <sstream>
#include <bitset>
//#include <ofstream>

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

pair<Notation, Notation> findbookmove(Board b){
    ifstream opens;
    opens.open ("C:\\Users\\samue\\Documents\\sideproj\\repos\\ChessAi\\new\\opens.txt");
    string line;
    vector<string> allnextmoves;
    while ( getline (opens,line) ) {
        string bFEN = b.getFEN();
        vector<string> fen_info = split(bFEN, " ");
        bFEN = fen_info[0];
        string line2;
        int a = line.length();
        if (line.length() !=  0){
            fen_info = split(line, " ");
            line2 = fen_info[0];
        }

        if (bFEN==line2){
            string nextmove;
            getline(opens,nextmove);
            if (nextmove != "") {
                allnextmoves.push_back(nextmove);
            }
        }
    }
    opens.close();
    if (allnextmoves.size()==0){
        return make_pair(MOVE,MOVE);
    }

    //getting random next move
    string nextFEN = allnextmoves[rand()%allnextmoves.size()];
    vector<string> fen_info = split(nextFEN, " ");
    nextFEN = fen_info[0];
    vector<pair<Notation, Notation>> allmoves = b.returnNotationMoves();
    for(int i = 0; i < allmoves.size(); i++) {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        Board b2 =b;
        b2.makeMove(n1,n2);
        string b2FEN = b2.getFEN();
        vector<string> fen_info = split(b2FEN, " ");
        b2FEN = fen_info[0];
        if (b2FEN==nextFEN){
            return make_pair(n1,n2);
        }
    }
    cout<<"err";
    return make_pair(MOVE,MOVE);

}

int evaluate(Board b, int alpha, int beta) {
    string fen = b.getFEN();
    Color turn = b.getMoveColor();

    //game over
    if (b.isGameOver()){
        Color winner = b.Winner();
        if (winner==NONE){
            return 0;
        }
        return -1000000;
    }

    if (turn == WHITE){

        return findmaterial(fen)*1000+rand()%10;
    }
    else {
        return -findmaterial(fen)*1000-rand()%10;
    }
}

int alphaBeta(Board b,int alpha, int beta, int depthleft, vector<long long int> movestack,array<array<array<long long int,12>,8>,9> zarray,zstuff zobriststuff) {
    //cout<<"alphabeta: d:"<<depthleft<<" move: "<<b.getMoveColor()<<endl;
    if( depthleft == 0 ) return evaluate(b, alpha, beta );
    vector<pair<Notation, Notation>> allmoves = b.returnNotationMoves();

   for (int i = 0; i < allmoves.size(); i++)  {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        Board b2 = b;
        zstuff newzobriststuff = zmove(b2, n1,n2,zobriststuff,zarray);
        //b2.makeMove(n1,n2);

        //logs
        string newdir = getcwd(NULL,0);
        stringstream buffer;
        buffer<<n1<<'-'<<n2<<"_"<<b2.getLastPGNmove();
        string oldname = buffer.str();
        mkdir(oldname.c_str());
        chdir(oldname.c_str());
        // ofstream info;
        // info.open("info.txt");
        // info<<"FEN:"<<b2.getFEN()<<endl<<"zval:"<<zobriststuff.zval<<endl<<"materialadv:"<<zobriststuff.materialadv<<endl;
        
        // info.close();


        if(!(find(movestack.begin(), movestack.end(), newzobriststuff.zval) != movestack.end())){ //MOVE IS NOT REPEAT
            movestack.push_back(newzobriststuff.zval);
            int score = -alphaBeta(b2,-beta, -alpha, depthleft - 1,movestack,zarray,newzobriststuff);
            movestack.pop_back();

            //logging
            chdir(newdir.c_str());
            string newname = buffer.str()+"__"+to_string(score)+" BETA cut";
            rename(oldname.c_str(),newname.c_str());

            if( score >= beta )
                return beta;   //  fail hard beta-cutoff
            if( score > alpha )
                alpha = score; // alpha acts like max in MiniMax

        }
   }

    return alpha;
}

pair<Notation, Notation> rootsearch(Board b,vector<long long int> movestack,array<array<array<long long int,12>,8>,9> zarray,zstuff ogzobriststuff){

    pair<Notation,Notation> book = findbookmove(b);
    if (book.first != MOVE){
        cout<<"book move"<<endl;
        return make_pair(book.first,book.second);
    }

    //LOGS
    string olddir = getcwd(NULL,0);
    string newdir = to_string(b.getFullTurnNum())+"-"+to_string(b.getMoveColor());
    mkdir(newdir.c_str());
    chdir(newdir.c_str());
    newdir = getcwd(NULL,0);

    int alpha = -999999999;
    int beta = 999999999;
    //zstuff ogzobriststuff = board2zvals(b,zarray);
    pair<Notation, Notation> bestmove;
    vector<pair<Notation, Notation>> allmoves = b.returnNotationMoves();
    for(int i = 0; i < allmoves.size(); i++) {
        Notation n1 = allmoves[i].first;
        Notation n2 = allmoves[i].second;
        Board b2 = b;
        zstuff zobriststuff = zmove(b2,n1,n2,ogzobriststuff,zarray);
        //b2.makeMove(n1,n2);

        //logs
        stringstream buffer;
        buffer<<n1<<'-'<<n2<<"_"<<b2.getLastPGNmove();
        string oldname = buffer.str();
        mkdir(oldname.c_str());
        chdir(oldname.c_str());
        ofstream info;
        info.open("info.txt");
        info<<"FEN:"<<b2.getFEN()<<endl<<"zval:"<<zobriststuff.zval<<endl<<"materialadv:"<<zobriststuff.materialadv<<endl;
        //for (int j= 0; j<b.returnNotationMoves().size();j++) {info<<b.returnNotationMoves()[i].first,info<<b.returnNotationMoves()[i].second<<endl;}
        info.close();
        
        
        
        if(!(inside(movestack,zobriststuff.zval))){ //MOVE IS NOT REPEAT
            //make move
            movestack.push_back(zobriststuff.zval);
            
            int score = -alphaBeta(b2,-beta,-alpha,2,movestack,zarray,zobriststuff);
            if (score>alpha) {
                alpha = score;
                bestmove = make_pair(n1,n2); //
            }
            movestack.pop_back();

            //logging
            chdir(newdir.c_str());
            string newname = buffer.str()+"__"+to_string(score);
            rename(oldname.c_str(),newname.c_str());
        }
        else{
            chdir(newdir.c_str());
        }

        
    }
    //zstuff zobriststuff = zmove(bbestmove.first,bestmove.second,ogzobriststuff,zarray);
    chdir(olddir.c_str());
    return bestmove;
}

int playgame(){
    Board b;
    array<array<array<long long int,12>,8>,9> zarray = initialize();
     

    //b.loadFEN("8/8/8/8/8/k7/P7/K7 w - - 0 1");
    cout <<b.getFEN()<<endl;
    bool gn = !b.isGameOver();
    vector<long long int> movestack;
    zstuff zobriststuff = board2zvals(b,zarray);
    movestack.push_back(zobriststuff.zval);

    //LOG STUFF
    cout<<remove("logs");
    mkdir("logs");
    chdir("logs");
    string olddir = getcwd(NULL,0);
    //LOG STUFF

    while (gn){
        //LOG STUFF
        pair<Notation, Notation> move = rootsearch(b,movestack,zarray,zobriststuff);
        zobriststuff = zmove(b,move.first,move.second,zobriststuff,zarray);
        b.makeMove(move.first,move.second);
        movestack.push_back(zobriststuff.zval);
        //b.makeMove(move.first,move.second);
        cout <<b.getPGN()<<endl;
        
        gn = !b.isGameOver();
    }
    cout<<"DONE"<<endl;
    cout<<b.getPGN()<<endl;
    return 0;
}

Board testfun(Board b){
    b.makeMove(e2,e4);
    return b;
}

int main() {
    srand (time(NULL));
    cout<<"STARTING"<<endl;
    playgame();



}

