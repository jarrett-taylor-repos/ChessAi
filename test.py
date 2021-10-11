from math import pi
from re import A
import chess
import io
import chess.pgn
import chess.polyglot
import random
import time
from zobristfunctions import makezobrist,board2zobrist,makezobristmove3


#pgn = io.StringIO("1. e4 ")
pgn = io.StringIO("1. h4 h5 2. Rh3")
pgn = io.StringIO("1. g4 h5 2. gxh5 Rh6 3. Nf3 Rf6 4. h6 e6 5. h7 d6 6. hxg8=Q")
pgn = io.StringIO("1. e4 e6 2. Nf3 Nf6 3. Bd3 Bd6 4. O-O")
#pgn = io.StringIO("1. d4 f5 2. g3 Nf6 3. Bg2 g6 4. Nf3 d6 5. b4 Ne4 6. Nfd2 e5 7. f3 Qg5 8. Nxe4 Qh5 9. Nf6+ Ke7 10. Nxh5 a5 11. Nd2 f4 12. bxa5 Rxa5 13. gxf4 Nc6 14. d5 Nd4 ")

game = chess.pgn.read_game(pgn)
#print(game.end().board())
boardd = game.end().board()
boardd = chess.Board()

boardd = chess.Board("6k1/p7/1p6/6N1/2P5/P7/2r2pPP/4R2K b - - 0 44")

legalmoves = list(boardd.legal_moves)
for i in range(len(legalmoves)):
    print(legalmoves[i])