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
using namespace std;

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };
enum stringSquare { a1, a2, a3, a4, a5, a6, a7, a8, 
               b1, b2, b3, b4, b5, b6, b7, b8,
               c1, c2, c3, c4, c5, c6, c7, c8,
               d1, d2, d3, d4, d5, d6, d7, d8,
               e1, e2, e3, e4, e5, e6, e7, e8, 
               f1, f2, f3, f4, f5, f6, f7, f8, 
               g1, g2, g3, g4, g5, g6, g7, g8, 
               h1, h2, h3, h4, h5, h6, h7, h8, OO, OOO, MOVE};

//overload for stringSquare enum
std::ostream& operator<<(std::ostream& out, const stringSquare value){
    static std::map<stringSquare, std::string> strings;
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

bool isPairInList(pair<int, int> p, vector<pair<int, int>> vect) {
  for(int i = 0; i < vect.size(); i++) {
    bool p1 = (p.first == vect[i].first);
    bool p2 = (p.second == vect[i].second);

    if(p1 && p2) {
      return true;
    }
  }
  return false;
}

vector<int> getFileRank(int num) {
  int file, rank;
  vector<int> nums;
  file = num % 8;
  rank = floor(num/8);
  nums.push_back(file);
  nums.push_back(rank);
  return nums;

}

bool isInList(int a, vector<int> l) {
  for(int i = 0; i < sizeof(l); i++) {
    if(l[i] == a) {
      return true;
    }
  }
  return false;
}

Piece getPieceByLetter(char c) {
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

Color getColorByLetter(char c) {
    if(isupper(c)) {
        return WHITE;
    } else if (islower(c)) {
        return BLACK;
    } else {
        return NONE;
    }
}