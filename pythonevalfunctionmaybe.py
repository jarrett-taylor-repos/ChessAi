import chess
import chess.pgn
import io
from copy import deepcopy
import random
import chess.polyglot
import time

printlogs = False

board1 = chess.Board()
#print(board1.fen())
if printlogs: log = open('log.txt','w')
if printlogs: print("LOG IS NEW",file=log)
reader = chess.polyglot.open_reader("baron30.bin")

totalevals = 0
totalbreaks = 0
totaltime = 0
timespenteval = 0

materialadvmult = 1000
attacksmult = 50
pinnedmult = 300
pawnranksmult = 75


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
    if printlogs: print('calculated material advantage of ', FEN, 'as', materialadvantage,file=log)
    return materialadvantage




def evalpos(boardd):
    #print('evaluating postion',boardd.move_stack,file=log)
    global totalevals
    global timespenteval
    totalevals = totalevals+1
    t2 = time.time()

    if boardd.is_game_over():
        result = boardd.outcome().result()
        if printlogs: print('found position results in game over', file=log)
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


        evalu = materialadvantagecalc(boardd.fen())*materialadvmult
        evalu = evalu+(len(whiteattacks)*-len(blackattacks))*50
        evalu = evalu+isblackpinned*300+iswhitepinned*-300
        evalu += avgwhitepawnrank*75-avgblackpawnrank*75
        timespenteval += time.time()-t2
        return evalu

def sortmoves(boardd):
    legalmoves = list(boardd.legal_moves)
    bestmovenumberarray = []
    tempboard = boardd.copy()
    sortedlegalmoves = list()
    
    for i in range(len(legalmoves)):
        tempboard.push(legalmoves[i])
        bestmovenumberarray.append(evalpos(tempboard))
        tempboard.pop()
    
    while len(legalmoves) > 0:
        if boardd.turn==chess.WHITE:
            index = bestmovenumberarray.index(min(bestmovenumberarray))
        else:
            index = bestmovenumberarray.index(min(bestmovenumberarray))
        
        sortedlegalmoves.append(legalmoves[index])
        bestmovenumberarray.pop(index)
        legalmoves.pop(index)
    
    return sortedlegalmoves


def findsinglebestmove(boardd,depth,currentdepth=0,minormaxofabove=None):
    
    if depth==currentdepth:
        legalmoves = list(boardd.legal_moves)
    else:
        legalmoves = sortmoves(boardd)
    
    
    bestmovenumberarray = []
    tempboard = boardd.copy()
    minormaxofthis = None

    ##logging
    if printlogs: print("entering new depth: ",currentdepth,"minormaxofabove=",minormaxofabove,file=log)

    for i in range(len(legalmoves)):
        
        tempboard.push(legalmoves[i])
        
        #logging
        movestack = tempboard.move_stack
        if printlogs: print("testing tempboard: ",movestack[len(movestack)-currentdepth-1:len(movestack)],file=log)

        if depth==currentdepth:
            
            evalofmove = (evalpos(tempboard))
            if printlogs: print('at depth, found evaluation:',evalofmove,file=log)
        else:
            if tempboard.is_game_over():
                evalofmove = (evalpos(tempboard))
                if printlogs: print('found game is over, eval:',evalofmove,file=log)
            else:
                evalofmove = (findsinglebestmove(tempboard,depth,currentdepth+1,minormaxofthis))
                if printlogs: print('EXITING LEVEL, eval:',evalofmove,file=log)

        evalofmove -= 1
        bestmovenumberarray.append(evalofmove)
        if printlogs: print("depth:",currentdepth,"turn:",tempboard.ply(),"bestmovenumberarray now:",bestmovenumberarray,"for moves",legalmoves,file=log)

        global totalbreaks
        ##NOT SURE ABOUT THIS PART
        if boardd.turn==chess.WHITE:
            minormaxofthis = max(bestmovenumberarray)
            if printlogs: print("taking max to find minormaxofthis",file=log)
            if minormaxofabove!=None:
                if evalofmove > minormaxofabove:
                    l=True
                    if printlogs: print('exiting loop because eval of ',evalofmove,"is greater than",minormaxofabove,file=log)
                    global totalbreaks
                    totalbreaks += 1
                    return evalofmove
        else:
            minormaxofthis = min(bestmovenumberarray)
            if printlogs: print('taking min to find minormaxofthis',file=log)
            if minormaxofabove!=None:
                if evalofmove < minormaxofabove:
                    l=True
                    if printlogs: print('exiting loop because eval of ',evalofmove,"is less than",minormaxofabove,file=log)
                    totalbreaks += 1
                    return evalofmove
        if printlogs: print('',file=log)
        tempboard.pop()
    
    if currentdepth == 0:
        if boardd.turn==chess.WHITE:
            besteval = (max(bestmovenumberarray))
        else:
            besteval = (min(bestmovenumberarray))
        #return legalmoves[bestmovenumberarray.index(besteval)]
        
        locationsofbest = [index for index, element in enumerate(bestmovenumberarray) if element == besteval]
        #locationsofbest = bestmovenumberarray.index(besteval)
        if printlogs: print('found best moves at:',locationsofbest,"with eval:",besteval,file=log)
        if printlogs: print("SENDING MOVE",boardd.ply(),":", legalmoves[locationsofbest],file=log)
        #return(legalmoves[locationsofbest])
        return legalmoves[locationsofbest[random.randint(0,len(locationsofbest)-1)]]
    else:
        if boardd.turn==chess.WHITE:
            return max(bestmovenumberarray)
        else:
            return min(bestmovenumberarray)



def playmove(boardd,nodee):
    totalevals = 0
    totalbreaks = 0
    totaltime = 0
    timespenteval = 0

    t = time.time()
    if reader.get(boardd) != None:
        bestmove = reader.choice(boardd).move
        nodee = nodee.add_variation(bestmove)
        #print('doingbookmove')
    else:
        bestmove = (findsinglebestmove(boardd,2))
        nodee = nodee.add_variation(bestmove)
        
    boardd.push(bestmove)
    if printlogs: print(boardd,file=log)
    if printlogs: print('------------------',file=log)
    return boardd,nodee
    #print(totalbreaks,totalevals,time.time()-t,timespenteval,time.time()-t-timespenteval)


#def playgame(materialadvmult,attacksmult,pinnedmult,pawnranksmult):
    #bmaterial

materialadvmult = 1000
attacksmult = 50
pinnedmult = 300
pawnranksmult = 75



board4 = chess.Board()
game = chess.pgn.Game()
game.setup(board4)
node = game


while not board4.is_game_over():
    board4,node = playmove(board4,node)
    print(game)
    print('')
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