import chess

board1 = chess.Board()
#print(board1.fen())



def materialadvantagecalc(FEN):
    materialadvantage=0
    for i in range(len(FEN)):
        FENpos = FEN[i]
        if FENpos == 'w':
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
    if boardd.outcome() != None:
        result = boardd.outcome().result()
        if result == "1-0":
            return 1000
        elif result == "0-1":
            return -1000
        else:
            return 0
    else: # materialadvantagecalc(boardd.pop().fen()) != materialadvantagecal(boardd.fen()):
        return materialadvantagecalc(boardd.fen())
    
def findbestmovenumberarray(boardd):
    legalmoves = list(boardd.legal_moves)
    bestmovenumberarray = []
    #print(legalmoves)
    #print(board1)
    print(legalmoves[0])
    print(type(boardd))
    #boardd.push(legalmoves[0])




#print(materialadvantagecalc("rnbqkbnr/ppp1pppp/8/8/8/8/PPPPPPPP/1NBQKBNR w Kkq - 0 1"))

#print(board1.legal_moves)
#print(list(board1.legal_moves)[0])
legalmoves = list(board1.legal_moves)
#print(legalmoves)
#print(board1)
#print(legalmoves[0])

#print(board1)
findbestmovenumberarray(board1)

board1.push(legalmoves[0])
print(type(board1))