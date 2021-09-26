import chess
import io
import chess.pgn
import chess.polyglot

pgn = io.StringIO("1. e4 N")
pgn = io.StringIO("1. Nh3 Nh6 2. a3")
game = chess.pgn.read_game(pgn)
#print(game.end().board())
boardd = game.end().board()
boardd = chess.Board()

whitepawns = boardd.pieces(1,chess.WHITE)
print(list(whitepawns))
print(list(chess.square_rank(whitepawns)))

print('')
print(chess.square_rank(list(whitepawns)[0]))