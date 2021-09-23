import chess
import chess.pgn
import io
from copy import deepcopy
board1 = chess.Board()
#print(board1.fen())



def materialadvantagecalc(FEN):
    materialadvantage=0
    for i in range(len(FEN)):
        FENpos = FEN[i]
        if FENpos == ' ':
            break
        if FENpos == 'p':
            materialadvantage += -1
        if FENpos == 'n':
            materialadvantage += -3
        if FENpos == 'b':
            materialadvantage += -3
        if FENpos == 'r':
            materialadvantage += -5
        if FENpos == 'q':
            materialadvantage += -9
        if FENpos == 'P':
            materialadvantage += 1
        if FENpos == 'N':
            materialadvantage += 3
        if FENpos == 'B':
            materialadvantage += 3
        if FENpos == 'R':
            materialadvantage += 5
        if FENpos == 'Q':
            materialadvantage += 9
    return materialadvantage

def evalpos(boardd):
    if boardd.is_game_over():
        result = boardd.outcome().result()
        if result == "1-0":
            return 1000
        elif result == "0-1":
            return -1000
        else:
            return 0
            if boardd.turn==chess.WHITE:
                return -100
            else:
                return 100
    else: # materialadvantagecalc(boardd.pop().fen()) != materialadvantagecal(boardd.fen()):
        return materialadvantagecalc(boardd.fen())
    
def findsinglebestmove(boardd,depth,currentdepth=0):
    legalmoves = list(boardd.legal_moves)
    bestmovenumberarray = []
    tempboard = deepcopy(boardd)
    for i in range(len(legalmoves)):

        tempboard.push(legalmoves[i])
        if depth==currentdepth:
            bestmovenumberarray.append(evalpos(tempboard))
        else:
            if tempboard.is_game_over():
                bestmovenumberarray.append(evalpos(tempboard))
            else:
                bestmovenumberarray.append(findsinglebestmove(tempboard,depth,currentdepth+1))
        tempboard.pop()
    
    if currentdepth == 0:
        if boardd.turn==chess.WHITE:
            besteval = (max(bestmovenumberarray))
        else:
            besteval = (min(bestmovenumberarray))
        return legalmoves[bestmovenumberarray.index(besteval)]
    else:
        if boardd.turn==chess.WHITE:
            return max(bestmovenumberarray)
        else:
            return min(bestmovenumberarray)











board2 = chess.Board("rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2")
board3 = chess.Board("r1bqkbnr/ppp2ppp/2np4/4p3/2B1P3/5Q2/PPPP1PPP/RNB1K1NR w KQkq - 0 4")
#print(board3.is_game_over())
####print(findsinglebestmove(board3,3))

#print(findbestmove(board1,0))

board4 = chess.Board("rn1q1rk1/1p2bppp/p2pbn2/4p3/4P3/1NN1BP2/PPPQ2PP/2KR1B1R b - - 4 10")
board4 = chess.Board()
game = chess.pgn.Game()
game.setup(board4)
node = game


while board4.is_game_over()==False:
    bestmove = (findsinglebestmove(board4,3))
    node = node.add_variation(bestmove)
    board4.push(bestmove)
    print('')
    print(game)
    print('')



print(board4.outcome())
print(board4.is_game_over())
print(board4.outcome().termination)
print(board4.outcome().result())
print('#######################')
print('DONE')
print(game)
'''
pgn = io.StringIO("1. Nh3 Nh6 2. Ng5 Ng4 3. Nxh7 Rxh7 4. Rg1 Nxh2 5. Rh1 Nf3+ 6. gxf3 Rxh1 7. Nc3 Nc6 8. Nd5 Rb8 9. Nxe7 Bxe7 10. Rb1 Kf8 11. Ra1 Kg8 12. Rb1 Kh8 13. Ra1 Kg8 14. Rb1 Kh8 15. Ra1 Kg8 16. Rb1 Kh8 17. Ra1 Kg8 18. Rb1 Kh8 19. Ra1 Kg8 *")
game = chess.pgn.read_game(pgn)
#print(game.end().board())
board = game.end().board()
board.pop()
print(board)
board.push_uci("h8g8")
print(evalpos(board))
print(board.is_game_over())
print(board)
'''