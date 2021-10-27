#include "Board.cpp"
#include <chrono>
using namespace std::chrono;
#include <time.h>

int moveGenerationTest(Board b, int depth) {
    if(depth == 0) {
        return 1;
    }
    int numPos = 0;
    string fen = b.getFEN();
    //cout << "MAIN FEN " << fen << endl;
    vector<pair<Notation, Notation>> notmoves = b.getAllMovesVector();
    for(int i = 0; i < notmoves.size(); i++) {
        pair<Notation, Notation> tempmove = notmoves[i];
        Board temp;
        temp.loadFEN(fen);
        //cout << "before move " << temp.getFEN() << " - " << tempmove.first << tempmove.second << endl;
        bool mademove = temp.makeMove(tempmove.first, tempmove.second);
        //cout << "after move " << temp.getFEN() << " - " << tempmove.first << tempmove.second << endl;
        if(mademove) {
            numPos += moveGenerationTest(temp, depth-1);
        } else {
            //cout << temp.getFEN() << " attempted move " << tempmove.first << tempmove.second << endl;
        }
        


    }
    return numPos;
}


int main() {
    string testPos = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
    // 1 - 44
    // 2 - 1486
    // 3 - 62379
    // 4 - 2103487
    // 5 - 89,941,194
    Board b;
    //b.loadFEN(testPos);

    // 1	20
    // 2	400
    // 3	8,902
    // 4	197,281
    // 5	4,865,609
    // 6	119,060,324
    // 7	3,195,901,860
    // 8	84,998,978,956
    // 9	2,439,530,234,167
    // 10	69,352,859,712,417
    int depth = 6;
    int nummoves = 0;
    clock_t tStart = clock();
    cout << "Depth - num" << endl;
    for(int i = 1; i <= depth; i++) {
        nummoves =  moveGenerationTest(b, i);
        cout << i << " - " << nummoves << endl;
        printf("Time taken: %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    
    }
    return 0;
}