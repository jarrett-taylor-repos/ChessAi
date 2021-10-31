#include "Board.cpp"
#include <chrono>
using namespace std::chrono;
#include <time.h>
#include <thread>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using namespace std::chrono_literals;

int main() {
    int iter = 100;
    vector<duration<double, std::milli>> construct;
    vector<duration<double, std::milli>> copy;
    vector<duration<double, std::milli>> fen;
    vector<duration<double, std::milli>> makemove;
    for(int i = 0; i < iter; i++) {
        auto t1 = high_resolution_clock::now();
        Board b;
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        construct.push_back(ms_double);
        //cout << "Time taken to construct board: " << ms_double.count() << "ms" << endl;

        t1 = high_resolution_clock::now();
        Board testcopy = b;
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        copy.push_back(ms_double);
        //cout << "Time taken to copy board: " << ms_double.count() << "ms"<< endl;


        string testPos1 = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
        t1 = high_resolution_clock::now();
        Board testfen(testPos1);
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        fen.push_back(ms_double);
        //cout << "Time taken to load board from fen: " << ms_double.count() << "ms"<< endl;

        
        t1 = high_resolution_clock::now();
        b.makeMove(d2, d4);
        t2 = high_resolution_clock::now();
        ms_double = t2 - t1;
        makemove.push_back(ms_double);
        //cout << "Time taken to make a move: " << ms_double.count() << "ms"<< endl;
    }
    duration<double, std::milli> construct_total;
    duration<double, std::milli> copy_total;
    duration<double, std::milli> fen_total;
    duration<double, std::milli> makemove_total;
    for(int i = 0; i < iter; i++) {
        construct_total += construct[i];
        copy_total += copy[i];
        fen_total += fen[i];
        makemove_total += makemove[i];
    }
    cout << "Average Time taken to construct board: " << construct_total.count()/(double)iter << "ms" << endl;
    cout << "Average Time taken to copy board: " << copy_total.count()/(double)iter << "ms" << endl;
    cout << "Average Time taken to load board by fen: " << fen_total.count()/(double)iter << "ms" << endl;
    cout << "Average Time taken to makemove board: " << makemove_total.count()/(double)iter << "ms" << endl;


    return 0;
}