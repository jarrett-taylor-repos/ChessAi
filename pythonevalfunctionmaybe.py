import chess
import chess.pgn
import io
from copy import deepcopy
import random
import chess.polyglot
board1 = chess.Board()
#print(board1.fen())
log = open('log.txt','w')
print("LOG IS NEW",file=log)
reader = chess.polyglot.open_reader("baron30.bin")


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
    print('calculated material advantage of ', FEN, 'as', materialadvantage,file=log)
    return materialadvantage




def evalpos(boardd):
    #print('evaluating postion',boardd.move_stack,file=log)
    global totalevals
    totalevals = totalevals+1
    if boardd.is_game_over():
        result = boardd.outcome().result()
        print('found position results in game over', file=log)
        if result == "1-0":
            return 100000000
        elif result == "0-1":
            return -100000000
        else:
            return 0
            if boardd.turn==chess.WHITE:
                return -100
            else:
                return 100
    else: # materialadvantagecalc(boardd.pop().fen()) != materialadvantagecal(boardd.fen()):
        #game not over
        evalu = materialadvantagecalc(boardd.fen())*1000

        ogboard = boardd.copy()
        ogboard.pop()
        movee = boardd.peek()
        turnn = ogboard.turn
        turnadj = 1
        if turnn==chess.BLACK:
            turnadj = -1
        
        allsquares = chess.SQUARES

        #all locations of white and black pieces (also using function to find all pawns)
        allwhiteloc = boardd.pieces(1,chess.WHITE)
        allwhitepawns = allwhiteloc
        allblackloc = boardd.pieces(1,chess.BLACK)
        allblackpawns = allblackloc
        for i in range(2,7):
            allwhiteloc = allwhiteloc.union(boardd.pieces(i,chess.WHITE))
            allblackloc = allblackloc.union(boardd.pieces(i,chess.BLACK))

        #set of squares that the color is attacking
        whiteattacks = chess.SquareSet()
        blackattacks = chess.SquareSet()
        
        #is king pinned
        isblackpinned = False
        iswhitepinned =False

        #going through all white pieces to find whiteattacks and ifpinned.
        for i in range(len(allwhiteloc)):
            pieceloc = list(allwhiteloc)[i]
            
            #attacks
            whiteattacks = whiteattacks.union(boardd.attacks(pieceloc))
            
            #is pinned
            if boardd.is_pinned(chess.WHITE,pieceloc):
                iswhitepinned=True

        #same for black pieces
        for i in range(len(allblackloc)):
            pieceloc = list(allblackloc)[i]
            blackattacks = blackattacks.union(boardd.attacks(pieceloc))
            if boardd.is_pinned(chess.BLACK,pieceloc):
                isblackpinned=True

        #finding average rank of pawns (see allwhitepawns assignment above)
        avgwhitepawnrank = 0
        avgblackpawnrank = 0
        for i in range(len(allwhitepawns)):
            avgwhitepawnrank += (chess.square_rank(list(allwhitepawns)[i])-1)/len(allwhitepawns)

        #same for black
        for i in range(len(allblackpawns)):
            avgblackpawnrank += (7-chess.square_rank(list(allblackpawns)[i]))/len(allblackpawns)


        
        evalu = evalu+len(whiteattacks)*50-len(blackattacks)*50
        evalu = evalu+isblackpinned*300+iswhitepinned*-300
        evalu += avgwhitepawnrank*10000-avgblackpawnrank*10000
        return evalu
    
def findsinglebestmove(boardd,depth,currentdepth=0,minormaxofabove=None):
    legalmoves = list(boardd.legal_moves)
    bestmovenumberarray = []
    tempboard = deepcopy(boardd)
    minormaxofthis = None

    ##logging
    print("entering new depth: ",currentdepth,"minormaxofabove=",minormaxofabove,file=log)

    for i in range(len(legalmoves)):
        
        tempboard.push(legalmoves[i])
        
        #logging
        movestack = tempboard.move_stack
        print("testing tempboard: ",movestack[len(movestack)-currentdepth-1:len(movestack)],file=log)

        if depth==currentdepth:
            
            evalofmove = (evalpos(tempboard))
            print('at depth, found evaluation:',evalofmove,file=log)
        else:
            if tempboard.is_game_over():
                evalofmove = (evalpos(tempboard))
                print('found game is over, eval:',evalofmove,file=log)
            else:
                evalofmove = (findsinglebestmove(tempboard,depth,currentdepth+1,minormaxofthis))
                print('EXITING LEVEL, eval:',evalofmove,file=log)
        bestmovenumberarray.append(evalofmove)
        print("turn: ",tempboard.ply(),"bestmovenumberarray now:",bestmovenumberarray,"for moves",legalmoves,file=log)

        ##NOT SURE ABOUT THIS PART
        if boardd.turn==chess.WHITE:
            minormaxofthis = max(bestmovenumberarray)
            print("taking max to find minormaxofthis",file=log)
            if minormaxofabove!=None:
                if evalofmove > minormaxofabove:
                    l=True
                    print('exiting loop because eval of ',evalofmove,"is greater than",minormaxofabove,file=log)
                    return evalofmove
        else:
            minormaxofthis = min(bestmovenumberarray)
            print('taking min to find minormaxofthis',file=log)
            if minormaxofabove!=None:
                if evalofmove < minormaxofabove:
                    l=True
                    print('exiting loop because eval of ',evalofmove,"is less than",minormaxofabove,file=log)
                    return evalofmove
        print('',file=log)
        tempboard.pop()
    
    if currentdepth == 0:
        if boardd.turn==chess.WHITE:
            besteval = (max(bestmovenumberarray))
        else:
            besteval = (min(bestmovenumberarray))
        #return legalmoves[bestmovenumberarray.index(besteval)]
        
        #locationsofbest = [index for index, element in enumerate(bestmovenumberarray) if element == besteval]
        locationsofbest = bestmovenumberarray.index(besteval)
        print('found best moves at:',locationsofbest,"with eval:",besteval,file=log)
        print("SENDING MOVE ",boardd.ply(),":", legalmoves[locationsofbest],file=log)
        return(legalmoves[locationsofbest])
        return legalmoves[locationsofbest[random.randint(0,len(locationsofbest)-1)]]
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
    
    totalevals = 0

    if reader.get(board4) != None:
        bestmove = reader.get(board4).move
        node = node.add_variation(bestmove)
        print('doingbookmove')
    else:
        bestmove = (findsinglebestmove(board4,2))
        node = node.add_variation(bestmove)
    board4.push(bestmove)
    print('')
    print(totalevals)
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