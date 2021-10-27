#include "Helper.cpp"


class Square {
  private:
    Piece piece;
    Color color;
    int x, y; //file, rank
  
  public:
    Square();
    Square(const Square &s1);

    void setPieceandColor(Piece p, Color col);
    void setEmpty();
    void setxy(int a, int b);

    Color getColor();
    Piece getPiece();
    int getx();
    int gety();
    string printString();

    void printSquare();
};

//constructor
Square::Square()  {
  piece = EMPTY;
  color = NONE;
}

Square::Square(const Square &s1) {
  piece = s1.piece;
  color = s1.color;
  x = s1.x;
  y = s1.y;
}
//set 
void Square::setPieceandColor(Piece p, Color col) {
  piece = p;
  color = col; 
}

void Square::setEmpty() {
  piece = EMPTY;
  color = NONE;
}

void Square::setxy(int a, int b) {
  x = a;
  y = b;
}


//get
Color Square::getColor() {
  return color;
}
Piece Square::getPiece() {
  return piece;
}
int Square::getx() {
  return x;
}
int Square::gety() {
  return y;
}

string Square::printString() {
  string s = "";
  switch(piece) {
    case KING:
      (color == WHITE) ? s= "K" : s=  "k";
      break;
    case QUEEN:
      (color == WHITE) ? s=  "Q" : s=  "q";
      break;
    case ROOK:
      (color == WHITE) ? s=  "R" : s=  "r";
      break;
    case BISHOP:
      (color == WHITE) ? s=  "B" : s=  "b";
      break;
    case KNIGHT:
      (color == WHITE) ? s=  "N" : s=  "n";
      break;
    case PAWN:
      (color == WHITE) ? s=  "P" : s=  "p";
      break;
    case EMPTY:
      s=".";
      break; 
    default:
      s= "default";
      break;
  }
  return s;
}


//print
void Square::printSquare() {
  switch(piece) {
    case KING:
      (color == WHITE) ? cout << "K" : cout << "k";
      break;
    case QUEEN:
      (color == WHITE) ? cout << "Q" : cout << "q";
      break;
    case ROOK:
      (color == WHITE) ? cout << "R" : cout << "r";
      break;
    case BISHOP:
      (color == WHITE) ? cout << "B" : cout << "b";
      break;
    case KNIGHT:
      (color == WHITE) ? cout << "N" : cout << "n";
      break;
    case PAWN:
      (color == WHITE) ? cout << "P" : cout << "p";
      break;
    case EMPTY:
      cout << ".";
      break; 
    default:
      cout << "default";
      break;
  }
}