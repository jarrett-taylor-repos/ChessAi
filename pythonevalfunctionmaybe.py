import chess
import chess.pgn
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
        if FENpos == 'k':
            materialadvantage += -3
        if FENpos == 'b':
            materialadvantage += -3
        if FENpos == 'r':
            materialadvantage += -5
        if FENpos == 'q':
            materialadvantage += -9
        if FENpos == 'P':
            materialadvantage += 1
        if FENpos == 'K':
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
        print(boardd)
        print('ahh')
        print(result)
        if result == "1-0":
            return 1000
        elif result == "0-1":
            return -1000
        else:
            print(boardd.outcome())
            print('AHHHHHHHHHHHHHHHHHHHHHHHHHHH')
            if boardd.turn==chess.WHITE:
                return -100
            else:
                return 100
    else: # materialadvantagecalc(boardd.pop().fen()) != materialadvantagecal(boardd.fen()):
        return materialadvantagecalc(boardd.fen())
    
def findsinglebestmove(boardd,depth,currentdepth=0):
    legalmoves = list(boardd.legal_moves)
    bestmovenumberarray = []
    for i in range(len(legalmoves)):
        tempboard = chess.Board(boardd.fen())
        tempboard.push(legalmoves[i])
        if depth==currentdepth:
            bestmovenumberarray.append(evalpos(tempboard))
        else:
            if tempboard.is_game_over():
                bestmovenumberarray.append(evalpos(tempboard))
                print('HERE')
                print(bestmovenumberarray)
            else:
                bestmovenumberarray.append(findsinglebestmove(tempboard,depth,currentdepth+1))

        #if currentdepth==0:
            #print(i)
            #print(len(legalmoves))
    
    
    if currentdepth == 0:
        if boardd.turn==chess.WHITE:
            besteval = (max(bestmovenumberarray))
        else:
            besteval = (min(bestmovenumberarray))
        print(bestmovenumberarray)
        print(boardd.legal_moves)
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
    bestmove = (findsinglebestmove(board4,2))
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