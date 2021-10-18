#include "Chessboard.cpp"

class Game {
    private:
        ChessBoard chessboard;
        //store all moves and moves information
        //could creare class for this to all for better information tracking
        pair<Notation,Notation> moves[1000];
        pair<Piece,Color> capturedPieces[1000];
        string allFENs[1000];

    public:
        Game();
        
        ChessBoard getBoard();

        void Move();

        void printGame();
};

Game::Game() {
    for(int i = 0; i < 1000; i++) {
        moves[i] = make_pair(MOVE, MOVE);
        allFENs[i] = "";
    }
};


void Game::Move() {
    chessboard.Move();
}

ChessBoard Game::getBoard() {
    return chessboard;
}