#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <list>
#include <algorithm>
#include <iterator>
#include <map>
#include <ctype.h>
#include <stdio.h>
#include <cmath>
#include <string.h> 
#include <string>
#include <iterator>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };
enum Notation { a1, a2, a3, a4, a5, a6, a7, a8, b1, b2, b3, b4, b5, b6, b7, b8, c1, c2, c3, c4, c5, c6, c7, c8, d1, d2, d3, d4, d5, d6, d7, d8, e1, e2, e3, e4, e5, e6, e7, e8, f1, f2, f3, f4, f5, f6, f7, f8, g1, g2, g3, g4, g5, g6, g7, g8, h1, h2, h3, h4, h5, h6, h7, h8, a8Q, a8R, a8N, a8B, b8Q, b8R, b8N, b8B, c8Q, c8R, c8N, c8B, d8Q, d8R, d8N, d8B, e8Q, e8R, e8N, e8B, f8Q, f8R, f8N, f8B, g8Q, g8R, g8N, g8B, h8Q, h8R, h8N, h8B, a1q, a1r, a1n, a1b, b1q, b1r, b1n, b1b, c1q, c1r, c1n, c1b, d1q, d1r, d1n, d1b, e1q, e1r, e1n, e1b, f1q, f1r, f1n, f1b, g1q, g1r, g1n, g1b, h1q, h1r, h1n, h1b, MOVE };
static const char *notation_str[] = {
  "a1","a2","a3","a4","a5","a6","a7","a8","b1","b2","b3","b4","b5","b6","b7","b8","c1","c2","c3","c4","c5","c6","c7","c8","d1","d2","d3","d4","d5","d6","d7","d8","e1","e2","e3","e4","e5","e6","e7","e8","f1","f2","f3","f4","f5","f6","f7","f8","g1","g2","g3","g4","g5","g6","g7","g8","h1","h2","h3","h4","h5","h6","h7","h8","a8Q","a8R","a8N","a8B","b8Q","b8R","b8N","b8B","c8Q","c8R","c8N","c8B","d8Q","d8R","d8N","d8B","e8Q","e8R","e8N","e8B","f8Q","f8R","f8N","f8B","g8Q","g8R","g8N","g8B","h8Q","h8R","h8N","h8B","a1q","a1r","a1n","a1b","b1q","b1r","b1n","b1b","c1q","c1r","c1n","c1b","d1q","d1r","d1n","d1b","e1q","e1r","e1n","e1b","f1q","f1r","f1n","f1b","g1q","g1r","g1n","g1b","h1q","h1r","h1n","h1b","MOVE"
};

void print_map(std::unordered_map<string, int> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

string notationToString(int enum_val) {
    string tmp(notation_str[enum_val]);
    return tmp;
}

//overload for Notation enum
std::ostream& operator<<(std::ostream& out, const Notation value){
    static std::map<Notation, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(a1);INSERT_ELEMENT(a2);INSERT_ELEMENT(a3);INSERT_ELEMENT(a4);INSERT_ELEMENT(a5);INSERT_ELEMENT(a6);INSERT_ELEMENT(a7);INSERT_ELEMENT(a8);
        INSERT_ELEMENT(b1);INSERT_ELEMENT(b2);INSERT_ELEMENT(b3);INSERT_ELEMENT(b4);INSERT_ELEMENT(b5);INSERT_ELEMENT(b6);INSERT_ELEMENT(b7);INSERT_ELEMENT(b8);
        INSERT_ELEMENT(c1);INSERT_ELEMENT(c2);INSERT_ELEMENT(c3);INSERT_ELEMENT(c4);INSERT_ELEMENT(c5);INSERT_ELEMENT(c6);INSERT_ELEMENT(c7);INSERT_ELEMENT(c8);
        INSERT_ELEMENT(d1);INSERT_ELEMENT(d2);INSERT_ELEMENT(d3);INSERT_ELEMENT(d4);INSERT_ELEMENT(d5);INSERT_ELEMENT(d6);INSERT_ELEMENT(d7);INSERT_ELEMENT(d8);
        INSERT_ELEMENT(e1);INSERT_ELEMENT(e2);INSERT_ELEMENT(e3);INSERT_ELEMENT(e4);INSERT_ELEMENT(e5);INSERT_ELEMENT(e6);INSERT_ELEMENT(e7);INSERT_ELEMENT(e8);
        INSERT_ELEMENT(f1);INSERT_ELEMENT(f2);INSERT_ELEMENT(f3);INSERT_ELEMENT(f4);INSERT_ELEMENT(f5);INSERT_ELEMENT(f6);INSERT_ELEMENT(f7);INSERT_ELEMENT(f8);
        INSERT_ELEMENT(g1);INSERT_ELEMENT(g2);INSERT_ELEMENT(g3);INSERT_ELEMENT(g4);INSERT_ELEMENT(g5);INSERT_ELEMENT(g6);INSERT_ELEMENT(g7);INSERT_ELEMENT(g8);
        INSERT_ELEMENT(h1);INSERT_ELEMENT(h2);INSERT_ELEMENT(h3);INSERT_ELEMENT(h4);INSERT_ELEMENT(h5);INSERT_ELEMENT(h6);INSERT_ELEMENT(h7);INSERT_ELEMENT(h8);
        INSERT_ELEMENT(a8Q);INSERT_ELEMENT(a8R);INSERT_ELEMENT(a8B);INSERT_ELEMENT(a8N);
        INSERT_ELEMENT(b8Q);INSERT_ELEMENT(b8R);INSERT_ELEMENT(b8B);INSERT_ELEMENT(b8N);
        INSERT_ELEMENT(c8Q);INSERT_ELEMENT(c8R);INSERT_ELEMENT(c8B);INSERT_ELEMENT(c8N);
        INSERT_ELEMENT(d8Q);INSERT_ELEMENT(d8R);INSERT_ELEMENT(d8B);INSERT_ELEMENT(d8N);
        INSERT_ELEMENT(e8Q);INSERT_ELEMENT(e8R);INSERT_ELEMENT(e8B);INSERT_ELEMENT(e8N);
        INSERT_ELEMENT(f8Q);INSERT_ELEMENT(f8R);INSERT_ELEMENT(f8B);INSERT_ELEMENT(f8N);
        INSERT_ELEMENT(g8Q);INSERT_ELEMENT(g8R);INSERT_ELEMENT(g8B);INSERT_ELEMENT(g8N);
        INSERT_ELEMENT(h8Q);INSERT_ELEMENT(h8R);INSERT_ELEMENT(h8B);INSERT_ELEMENT(h8N);
        INSERT_ELEMENT(a1q);INSERT_ELEMENT(a1r);INSERT_ELEMENT(a1b);INSERT_ELEMENT(a1n);
        INSERT_ELEMENT(b1q);INSERT_ELEMENT(b1r);INSERT_ELEMENT(b1b);INSERT_ELEMENT(b1n);
        INSERT_ELEMENT(c1q);INSERT_ELEMENT(c1r);INSERT_ELEMENT(c1b);INSERT_ELEMENT(c1n);
        INSERT_ELEMENT(d1q);INSERT_ELEMENT(d1r);INSERT_ELEMENT(d1b);INSERT_ELEMENT(d1n);
        INSERT_ELEMENT(e1q);INSERT_ELEMENT(e1r);INSERT_ELEMENT(e1b);INSERT_ELEMENT(e1n);
        INSERT_ELEMENT(f1q);INSERT_ELEMENT(f1r);INSERT_ELEMENT(f1b);INSERT_ELEMENT(f1n);
        INSERT_ELEMENT(g1q);INSERT_ELEMENT(g1r);INSERT_ELEMENT(g1b);INSERT_ELEMENT(g1n);
        INSERT_ELEMENT(h1q);INSERT_ELEMENT(h1r);INSERT_ELEMENT(h1b);INSERT_ELEMENT(h1n);
        INSERT_ELEMENT(MOVE);
#undef INSERT_ELEMENT
    }   

    return out << strings[value];
}

//overload for Color enum
std::ostream& operator<<(std::ostream& out, const Color value){
    static std::map<Color, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(BLACK);INSERT_ELEMENT(WHITE);INSERT_ELEMENT(NONE);
#undef INSERT_ELEMENT
    }   

    return out << strings[value];
}

//overload for Piece enum
std::ostream& operator<<(std::ostream& out, const Piece value){
    static std::map<Piece, std::string> strings;
    if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
        INSERT_ELEMENT(KING);
        INSERT_ELEMENT(QUEEN);
        INSERT_ELEMENT(BISHOP);
        INSERT_ELEMENT(KNIGHT);
        INSERT_ELEMENT(ROOK);
        INSERT_ELEMENT(PAWN);
        INSERT_ELEMENT(EMPTY);
#undef INSERT_ELEMENT
    }   

    return out << strings[value];
}


void coutTab(int num) {
  for(int i = 0; i < num; i++) {
    cout << "     ";
  }
  
  return;
}

bool isPairOfIntInVector(pair<int, int> p, vector<pair<int, int>> vect) {
  for(int i = 0; i < vect.size(); i++) {
    bool p1 = (p.first == vect[i].first);
    bool p2 = (p.second == vect[i].second);

    if(p1 && p2) {
      return true;
    }
  }
  return false;
}

bool isNotationInVector(Notation strsq, vector<pair<Notation, Notation>> vect) {
  for(int i = 0; i < vect.size(); i++) {
    //cout << strsq << ", " << vect[i].second << endl;
    bool p1 = (strsq == vect[i].second);
    //cout << p1 << endl;
    if(p1) {
      return true;
    }
  }
  return false;
}

bool isPairMoveinVector(pair<Notation, Notation> p, vector<pair<Notation, Notation>> vect) {
  for(int i = 0; i < vect.size(); i++) {
    bool p1 = (p.first == vect[i].first);
    bool p2 = (p.second == vect[i].second);

    if(p1 && p2) {
      return true;
    }
  }
  return false;
}


bool isInRange(int x, int y) {
    return (x < 8) && (x >= 0) && (y < 8) && (y >= 0);
}

bool inRange(int a, int b, int x) {        
  return (a <= x && x <= b) ||
    (b <= x && x <= a);         
}  


vector<int> getFileRank(int num) { //needed?
  int file, rank;
  vector<int> nums;
  file = num % 8;
  rank = floor(num/8);
  nums.push_back(file);
  nums.push_back(rank);
  return nums;

}

bool isIntInVector(int a, vector<int> l) {
  for(int i = 0; i < sizeof(l); i++) {
    if(l[i] == a) {
      return true;
    }
  }
  return false;
}

Piece getPieceFromChar(char c) {
  if(c=='K' || c=='k') {
    return KING;
  } else if (c == 'Q' || c=='q') {
    return QUEEN;
  } else if (c == 'R' || c=='r') {
    return ROOK;
  } else if (c == 'B' || c=='b') {
    return BISHOP;
  } else if (c == 'N' || c=='n') {
    return KNIGHT;
  } else if (c == 'P' || c=='p') {
    return PAWN;
  } else {
    return EMPTY;
  }
}

Color getColorFromChar(char c) {
    if(isupper(c)) {
        return WHITE;
    } else if (islower(c)) {
        return BLACK;
    } else {
        return NONE;
    }
}

vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

Notation stringToNotation(string s) {
  if(s=="a1") return a1;
  if(s=="a2") return a2;
  if(s=="a3") return a3;
  if(s=="a4") return a4;
  if(s=="a5") return a5;
  if(s=="a6") return a6;
  if(s=="a7") return a7;
  if(s=="a8") return a8;
  if(s=="b1") return b1;
  if(s=="b2") return b2;
  if(s=="b3") return b3;
  if(s=="b4") return b4;
  if(s=="b5") return b5;
  if(s=="b6") return b6;
  if(s=="b7") return b7;
  if(s=="b8") return b8;
  if(s=="c1") return c1;
  if(s=="c2") return c2;
  if(s=="c3") return c3;
  if(s=="c4") return c4;
  if(s=="c5") return c5;
  if(s=="c6") return c6;
  if(s=="c7") return c7;
  if(s=="c8") return c8;
  if(s=="d1") return d1;
  if(s=="d2") return d2;
  if(s=="d3") return d3;
  if(s=="d4") return d4;
  if(s=="d5") return d5;
  if(s=="d6") return d6;
  if(s=="d7") return d7;
  if(s=="d8") return d8;
  if(s=="e1") return e1;
  if(s=="e2") return e2;
  if(s=="e3") return e3;
  if(s=="e4") return e4;
  if(s=="e5") return e5;
  if(s=="e6") return e6;
  if(s=="e7") return e7;
  if(s=="e8") return e8;
  if(s=="f1") return f1;
  if(s=="f2") return f2;
  if(s=="f3") return f3;
  if(s=="f4") return f4;
  if(s=="f5") return f5;
  if(s=="f6") return f6;
  if(s=="f7") return f7;
  if(s=="f8") return f8;
  if(s=="g1") return g1;
  if(s=="g2") return g2;
  if(s=="g3") return g3;
  if(s=="g4") return g4;
  if(s=="g5") return g5;
  if(s=="g6") return g6;
  if(s=="g7") return g7;
  if(s=="g8") return g8;
  if(s=="h1") return h1;
  if(s=="h2") return h2;
  if(s=="h3") return h3;
  if(s=="h4") return h4;
  if(s=="h5") return h5;
  if(s=="h6") return h6;
  if(s=="h7") return h7;
  if(s=="h8") return h8;
  if(s=="a8Q") return a8Q;
  if(s=="a8R") return a8R;
  if(s=="a8N") return a8N;
  if(s=="a8B") return a8B;
  if(s=="b8Q") return b8Q;
  if(s=="b8R") return b8R;
  if(s=="b8N") return b8N;
  if(s=="b8B") return b8B;
  if(s=="c8Q") return c8Q;
  if(s=="c8R") return c8R;
  if(s=="c8N") return c8N;
  if(s=="c8B") return c8B;
  if(s=="d8Q") return d8Q;
  if(s=="d8R") return d8R;
  if(s=="d8N") return d8N;
  if(s=="d8B") return d8B;
  if(s=="e8Q") return e8Q;
  if(s=="e8R") return e8R;
  if(s=="e8N") return e8N;
  if(s=="e8B") return e8B;
  if(s=="f8Q") return f8Q;
  if(s=="f8R") return f8R;
  if(s=="f8N") return f8N;
  if(s=="f8B") return f8B;
  if(s=="g8Q") return g8Q;
  if(s=="g8R") return g8R;
  if(s=="g8N") return g8N;
  if(s=="g8B") return g8B;
  if(s=="h8Q") return h8Q;
  if(s=="h8R") return h8R;
  if(s=="h8N") return h8N;
  if(s=="h8B") return h8B;
  if(s=="a1q") return a1q;
  if(s=="a1r") return a1r;
  if(s=="a1n") return a1n;
  if(s=="a1b") return a1b;
  if(s=="b1q") return b1q;
  if(s=="b1r") return b1r;
  if(s=="b1n") return b1n;
  if(s=="b1b") return b1b;
  if(s=="c1q") return c1q;
  if(s=="c1r") return c1r;
  if(s=="c1n") return c1n;
  if(s=="c1b") return c1b;
  if(s=="d1q") return d1q;
  if(s=="d1r") return d1r;
  if(s=="d1n") return d1n;
  if(s=="d1b") return d1b;
  if(s=="e1q") return e1q;
  if(s=="e1r") return e1r;
  if(s=="e1n") return e1n;
  if(s=="e1b") return e1b;
  if(s=="f1q") return f1q;
  if(s=="f1r") return f1r;
  if(s=="f1n") return f1n;
  if(s=="f1b") return f1b;
  if(s=="g1q") return g1q;
  if(s=="g1r") return g1r;
  if(s=="g1n") return g1n;
  if(s=="g1b") return g1b;
  if(s=="h1q") return h1q;
  if(s=="h1r") return h1r;
  if(s=="h1n") return h1n;
  if(s=="h1b") return h1b;
  return MOVE;
}