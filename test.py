import chess
import io
import chess.pgn
import chess.polyglot


#pgn = io.StringIO("1. e4 ")
#pgn = io.StringIO("1. Nh3 Nh6 2. a3")
pgn = io.StringIO("1. d4 f5 2. g3 Nf6 3. Bg2 g6 4. Nf3 d6 5. b4 Ne4 6. Nfd2 e5 7. f3 Qg5 8. Nxe4 Qh5 9. Nf6+ Ke7 10. Nxh5 a5 11. Nd2 f4 12. bxa5 Rxa5 13. gxf4 Nc6 14. d5 Nd4 ")

game = chess.pgn.read_game(pgn)
#print(game.end().board())
boardd = game.end().board()
#boardd = chess.Board()

print(boardd)
print((list(boardd.legal_moves)))
#print(list(boardd.pop.legal_moves)
legalmoves = list(boardd.legal_moves)

print(boardd.is_capture(legalmoves[0]))
print('')
print('')
movestack = boardd.move_stack

print(movestack)
print(len(movestack))
print(movestack[0].from_square)

