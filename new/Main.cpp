#include "Board.cpp"

int main() {
    Board b;
    b.print();
    b.makeMoveAndPrint(e2, e4);
    b.makeMoveAndPrint(e7, e5);
    b.makeMoveAndPrint(d1, f3);
    b.makeMoveAndPrint(a7, a6);
    b.makeMoveAndPrint(f1, c4);
    b.makeMoveAndPrint(b8, c6);
    b.makeMoveAndPrint(f3, f7);
    b.makeMoveAndPrint(a8, b8);//should be checkmate
}