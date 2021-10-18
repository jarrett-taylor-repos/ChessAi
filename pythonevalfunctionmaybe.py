from re import A
import chess
import chess.pgn
import io
from copy import deepcopy
import random
import chess.polyglot
import time
from zobristfunctions import makezobrist,board2zobrist,makezobristmove,makezobristmoveandmaterial

printlogs = True

board1 = chess.Board()
#print(board1.fen())
log2 = open('log3.txt','w')
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

def findlocationsofpieces(boardd):
    whitelocs = []
    blacklocs = []
    allwhitelocs = chess.SquareSet()
    allblacklocs = chess.SquareSet()

    for i in range(1,7):
        white = boardd.pieces(i,chess.WHITE)
        black = boardd.pieces(i,chess.BLACK)
        whitelocs.append(white)
        blacklocs.append(black)
        allwhitelocs.union(white)
        allblacklocs.union(black)

    return whitelocs,blacklocs,allwhitelocs,allblacklocs

def findattacks(boardd,whitelocs,blacklocs):
    whiteattacks = []
    whiteattackers = []
    whitedefenders = []
    blackattacks = []
    blackattackers = []
    blackdefenders = []

    for i in range(len(whitelocs)):
        tempattacks = []
        tempattackers = []
        tempdefenders = []
        for j in range(len(list(whitelocs[i]))):
            tempattacks.append(boardd.attacks(list(whitelocs[i])[j]))
            tempattackers.append(boardd.attackers(chess.BLACK,list(whitelocs[i])[j]))
            tempdefenders.append(boardd.attackers(chess.WHITE,list(whitelocs[i])[j]))
        whiteattacks.append(tempattacks)
        whiteattackers.append(tempattackers)
        whitedefenders.append(tempdefenders)
    
    for i in range(len(blacklocs)):
        tempattacks = []
        tempattackers = []
        tempdefenders = []
        for j in range(len(list(blacklocs[i]))):
            tempattacks.append(boardd.attacks(list(blacklocs[i])[j]))
            tempattackers.append(boardd.attackers(chess.WHITE,list(blacklocs[i])[j]))
            tempdefenders.append(boardd.attackers(chess.BLACK,list(whitelocs[i])[j]))
        blackattacks.append(tempattacks)
        blackattackers.append(tempattackers)
        blackdefenders.append(tempdefenders)

    return whiteattacks, whiteattackers, whitedefenders, blackattacks,blackattackers, blackdefenders

def findhanging(whiteattackers,whitedefenders,blackattackers,blackdefenders):
    whitehanging = []
    blackhanging = []
    sumhanging = 0
    

    for i in range(len(whiteattackers)):
        for j in range(len(whiteattackers[i])):
            if len(list(whiteattackers)) >0 and len(list(whitedefenders)==0):
                    sumhanging += piecevalues[i]

    for i in range(len(blackattackers)):
        for j in range(len(blackattackers[i])):
            if len(list(blackattackers)) >0 and len(list(blackdefenders)==0):
                    sumhanging -= piecevalues[i]

    return sumhanging

def findattackadv(boardd,whiteloc,whiteattackers,whitedefenders,blackloc,blackattackers,blackdefenders): #FINISH THIS
    attackadv = 0
    for i in range(len(whiteattackers)):
        for j in range(len(whiteattackers[i])):
            attackerslist = list(whiteattackers[i][j])
            if len(attackerslist) != 0:
                defenderslist = list(whitedefenders[i][j])

                #find the material value of all the attackers and defenders
                attackersvalues = []
                for k in range(len(attackerslist)):
                    attackersvalues.append(piecevalues[boardd.piece_type_at(attackerslist[k])])
                attackersvalues.sort()

                defendersvalues = []
                for k in range(len(defenderslist)):
                    defendersvalues.append(piecevalues[boardd.piece_type_at(defenderslist[k])])
                defendersvalues.sort()
                defendersvalues.insert(0,piecevalues[boardd.piece_type_at(list(whiteloc[i][j]))])

                attackadv = 0
                for k in range([len(attackersvalues),len(defendersvalues)].min()):
                    attackadv





                
                

def evalpos(boardd):
    #print('evaluating postion',boardd.move_stack,file=log)
    global totalevals
    global timespenteval
    totalevals = totalevals+1
    t2 = time.time()
    if printlogs: print('zzevaluating board:',boardd.fen(),file=log2)

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


        
        #is king pinned
        isblackpinned = False
        iswhitepinned =False

        #going through all white pieces to find whiteattacks and ifpinned.
        for i in range(len(allwhiteloc)):
            pieceloc = list(allwhiteloc)[i]
            
            #is pinned
            if boardd.is_pinned(chess.WHITE,pieceloc):
                iswhitepinned=True

        #same for black pieces
        for i in range(len(allblackloc)):
            pieceloc = list(allblackloc)[i]
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


        evalu = materialadvantagecalc(boardd.fen())*1000
        if printlogs: print("evalu after materialadv adjustment:",evalu,file=log)
        evalu = evalu+(isblackpinned-iswhitepinned)*100
        if printlogs: print("evalu after ispinned adjustment:",evalu,file=log)
        evalu += (avgwhitepawnrank-avgblackpawnrank)*30
        if printlogs: print("evalu after pawnforwardship adjustment:",evalu,file=log)
        timespenteval += (time.time()-t2)
        return evalu

def evalpos2(boardd,materialadv):

    allwhitepawns = list(boardd.pieces(1,chess.WHITE))
    allblackpawns = list(boardd.pieces(1,chess.BLACK).mirror())

    avgwhitepawn = 0
    avgblackpawn = 0
    for i in range(len(allwhitepawns)):
        avgwhitepawn += chess.square_rank(allwhitepawns[i])/len(allwhitepawns)

    for i in range(len(allblackpawns)):
        avgblackpawn += chess.square_rank(allblackpawns[i])/len(allblackpawns)


    return materialadv*1000+avgwhitepawn*200-avgblackpawn*200
    

def Quiesce(boardd,materialadv,zval,alpha,beta):
    global zarray
    stand_pat = evalpos2(boardd,materialadv)
    if( stand_pat >= beta ):
        return beta
    if( alpha < stand_pat ):
        alpha = stand_pat;

    alllegalmoves = list(boardd.legal_moves)
    capturemoves = list()
    for i in range(len(alllegalmoves)):
        if boardd.is_capture(alllegalmoves[i]):
            capturemoves.append(alllegalmoves[i])
    
    for i in range(len(capturemoves)):
        newzval,newmaterialadv = makezobristmoveandmaterial(boardd,capturemoves[i],zval,zarray,materialadv)
        boardd.push(capturemoves[i])
        score = -Quiesce(boardd,newmaterialadv,newzval,-beta, -alpha)
        boardd.pop()

        if( score >= beta ):
            return beta
        if( score > alpha ):
           alpha = score
    
    return alpha

def gameover(boardd):
    result = boardd.outcome().result()
    if printlogs: print('found position results in game over', file=log)
    if result == "1-0":
        return 100000000
    elif result == "0-1":
        return -100000000
    else:
        return 0


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

def pruning2(boardd,depth):

    

    tempboard = boardd.copy()
    legalmoves = list(boardd.legal_moves)
    prunedlegalmoves = list()
    morepruned = list()
    turn = boardd.turn
    evals = []
    isrep = []
    toprun = []
    for i in range(len(legalmoves)):
        tempboard.push(legalmoves[i])
        evals.append(evalpos(tempboard))
        if tempboard.is_repetition(1):
            isrep.append(True)
        else: isrep.append(False)
        tempboard.pop()

    #depthvals
    numfordepth = [len(evals),max([round(len(evals)/2),5]),max([round(len(evals)/4),4]),4,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2]
    #numfordepth = [len(evals),len(evals),len(evals),len(evals),len(evals),len(evals),len(evals),len(evals)]
    
    for i in range(min([numfordepth[depth],len(evals)])):#round(len(evals)/2)+1):
        if turn==chess.WHITE:
            index = evals.index(max(evals))
        else:
            index = evals.index(min(evals))
        prunedlegalmoves.append(legalmoves[index])
        if not isrep[index]:
            morepruned.append(legalmoves[index])
        legalmoves.pop(index)
        evals.pop(index)
    
    if len(morepruned)==0: 
        return prunedlegalmoves

    return morepruned
            
        


def pruning(boardd):

    tempboard = boardd.copy()
    legalmoves = list(boardd.legal_moves)
    prunedlegalmoves = list()
    turn = boardd.turn

    for i in range(len(legalmoves)):
        toprune = False
        tempboard.push(legalmoves[i])

        if tempboard.is_repetition(1):
            toprune = True
        else:
            '''
            whitelocs,blacklocs,allwhitelocs,allblacklocs = findlocationsofpieces(tempboard)
            whiteattacks, whiteattackers, whitedefenders, blackattacks,blackattackers, blackdefenders = findattacks(boardd,whitelocs,blacklocs)
            sumhanging = findhanging(whiteattackers,whitedefenders,blackattackers,blackdefenders)
            changeinmaterial = materialadvantagecalc(tempboard)-materialadvantagecalc(boardd)
            
            if turn==chess.WHITE:
                if sumhanging >= changeinmaterial:
                    toprune = True
            else:
                if sumhanging <= changeinmaterial:
                    toprune = True
            '''
            #add the stuff above to eval, and then go from there

            #if not toprune:



        if not toprune:
            prunedlegalmoves.append(legalmoves[i])

        tempboard.pop()
    
    return legalmoves
    


def findsinglebestmove(boardd,depth,currentdepth=0,minormaxofabove=None):
    
    if depth==currentdepth:
        legalmoves = list(boardd.legal_moves)
    else:
        #legalmoves = list(boardd.legal_moves)
        legalmoves = pruning2(boardd,currentdepth)
    
    
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

        bestmovenumberarray.append(evalofmove)
        if printlogs: print("depth:",currentdepth,"turn:",tempboard.ply(),"bestmovenumberarray now:",bestmovenumberarray,"for moves",legalmoves,file=log)

        global totalbreaks
        ##NOT SURE ABOUT THIS PART
        if boardd.turn==chess.WHITE:
            minormaxofthis = max(bestmovenumberarray)
            if printlogs: print("taking max to find minormaxofthis",file=log)
            if minormaxofabove!=None:
                if evalofmove-50 > minormaxofabove:
                    l=True
                    if printlogs: print('exiting loop because eval of ',evalofmove,"is greater than",minormaxofabove,file=log)
                    global totalbreaks
                    totalbreaks += 1
                    return evalofmove
        else:
            minormaxofthis = min(bestmovenumberarray)
            if printlogs: print('taking min to find minormaxofthis',file=log)
            if minormaxofabove!=None:
                if evalofmove+50 < minormaxofabove:
                    l=True
                    if printlogs: print('exiting loop because eval of ',evalofmove,"is less than",minormaxofabove,file=log)
                    totalbreaks += 1
                    return evalofmove
        if printlogs: print('',file=log)
        tempboard.pop()
    
    if currentdepth == 0:
        if boardd.turn==chess.WHITE:
            besteval = (max(bestmovenumberarray))
            if printlogs: print('white move, taking max of bestmovenumberarray:', besteval,file=log)
        else:
            besteval = (min(bestmovenumberarray))
            if printlogs: print('black move, taking min of bestmovenumberarray:', besteval,file=log)
        #return legalmoves[bestmovenumberarray.index(besteval)]
        
        locationsofbest = [index for index, element in enumerate(bestmovenumberarray) if element == besteval]
        #locationsofbest = bestmovenumberarray.index(besteval)
        if printlogs: print('found best moves at:',locationsofbest,"with eval:",besteval,file=log)
        randomnum = random.randint(0,len(locationsofbest)-1)
        if printlogs: print("SENDING MOVE",boardd.ply()+1,":", legalmoves[locationsofbest[randomnum]],file=log)
        #return(legalmoves[locationsofbest])
        return legalmoves[locationsofbest[randomnum]]
    else:
        if boardd.turn==chess.WHITE:
            return max(bestmovenumberarray)
        else:
            return min(bestmovenumberarray)

def findsinglebestmove2(boardd,depth,zval,currentdepth=0,alpha=-999999999,beta=999999999):
    
    ##testing transtable
    t1 = time.time()
    global time1
    global time2
    global time3

    global transtable
    table = transtable[zval%len(transtable)]
    if len(table)>0 and not boardd.is_game_over():
        if zval==table[0] and boardd.fen()[0:len(boardd.fen())-3]==table[1][0:len(table[1])-3]:
            if boardd.fen()[0:len(boardd.fen())-3] != table[1][0:len(table[1])-3]:
                print("ERROR: board:",boardd.fen(),"table:",table[1])
            else:

                if currentdepth == 0:
                    if table[2] < 2:
                        #remove thee below if later
                        if not table[4] in list(boardd.legal_moves):
                            print("HELP")
                        else:
                            #print('here1')
                            return table[4]
                elif currentdepth != 0 and currentdepth < depth:
                    if table[2] <= currentdepth+1:
                        #print('here2')
                        return table[3]
                elif currentdepth==depth:
                    if table[2] <= currentdepth:
                        #print('here3')
                        return table[3]
                else: #currentdepth>depth
                    #print('here4')
                    return table[3]
            
    time1+=time.time()-t1
    t1 = time.time()
    ##FINDING LEGAL MOVES
    if depth==currentdepth:
        legalmoves = list(boardd.legal_moves)

    elif currentdepth>depth:
        templegalmoves = list(boardd.legal_moves)
        legalmoves = []

        #doing movestack stuff, want to change
        movestack = boardd.move_stack
        movestack = movestack[len(movestack)-currentdepth-1:len(movestack)]
        squares = []
        for i in range(len(movestack)):
            squares.append(movestack[i].from_square)
            squares.append(movestack[i].to_square)
        
        for i in range(len(templegalmoves)):
            if boardd.is_capture(templegalmoves[i]) and (templegalmoves[i].from_square in squares or templegalmoves[i].to_square in squares):
                legalmoves.append(templegalmoves[i])   
                
        legalmoves = []
    else:
        #legalmoves = list(boardd.legal_moves)
        legalmoves = pruning(boardd)
        #legalmoves = pruning2(boardd,currentdepth)

    if printlogs: print('at depth:',currentdepth,'alpha=',alpha,'beta=',beta,'fen:',boardd.fen(),'testing legal moves:',legalmoves,file=log)

    bestmovenumberarray = []
    tempboard = boardd.copy()
    bestmovenumberarray = []


    if currentdepth > depth:
        
        bestmovenumberarray.append(evalpos(boardd))
        if printlogs: print('currentdepth>depth, bestmovenumberarray now:',bestmovenumberarray,file=log)
    time2+=time.time()-t1
    t1 = time.time()

    #White move
    if boardd.turn:
        for i in range(len(legalmoves)):
            move = legalmoves[i]
            tempboard.push(move)
            

            movestack = tempboard.move_stack
            if printlogs: print("testing tempboard: ",movestack[len(movestack)-currentdepth-1:len(movestack)],'FEN:',tempboard.fen(),file=log)            
            newzval = makezobristmove(boardd,move,zval,zarray)
            if tempboard.is_game_over():
                evalu = evalpos(tempboard) 
            else:
                evalu = findsinglebestmove2(tempboard,depth,newzval,currentdepth+1,alpha,beta)

            if printlogs: print('evaluation for tempboard: ',movestack[len(movestack)-currentdepth-1:len(movestack)],'is',evalu,file=log)   
            bestmovenumberarray.append(evalu)
            alpha = max(bestmovenumberarray)
            if printlogs: print('alpha now:',alpha,'bestmovenumberarraynow:',bestmovenumberarray,'for moves',legalmoves,file=log)
            if evalu >= beta:
                if printlogs: print('breaking because evalu:',evalu,'is greater than beta:',beta,file=log)
                break
            tempboard.pop()
        besteval = max(bestmovenumberarray)
        


    #black move
    else:
        for i in range(len(legalmoves)):
            move = legalmoves[i]
            tempboard.push(move)
            
            #logging
            movestack = tempboard.move_stack
            if printlogs: print("testing tempboard: ",movestack[len(movestack)-currentdepth-1:len(movestack)],file=log)
            newzval = makezobristmove(boardd,move,zval,zarray)

            if tempboard.is_game_over():
                evalu = evalpos(tempboard)
            else:
                evalu = findsinglebestmove2(tempboard,depth,newzval,currentdepth+1,alpha,beta)

            if printlogs: print('evaluation for tempboard: ',movestack[len(movestack)-currentdepth-1:len(movestack)],'is',evalu,file=log)
            bestmovenumberarray.append(evalu)
            beta = min(bestmovenumberarray)
            if printlogs: print('beta now:',beta,'bestmovenumberarraynow:',bestmovenumberarray,'for moves',legalmoves,file=log)
            if evalu <= alpha:
                if printlogs: print('breaking because evalu:',evalu,'is less than alpha:',alpha,file=log)
                break
            tempboard.pop()
        
        besteval = min(bestmovenumberarray)

    #sending to table.
    if currentdepth>depth:
        transtable[zval%len(transtable)] = [zval,boardd.fen(),currentdepth,besteval,[]]
    else:
        transtable[zval%len(transtable)] = [zval,boardd.fen(),currentdepth,besteval,legalmoves[bestmovenumberarray.index(besteval)]]
    time3 += time.time()-t1
    #sending up move
    if currentdepth != 0:
        return besteval
    else:
        #locationsofbest = [index for index, element in enumerate(bestmovenumberarray) if element == besteval]
        #randomnum = random.randint(0,len(locationsofbest)-1)
        #bestmove = legalmoves[locationsofbest[randomnum]]
        bestmove = legalmoves[bestmovenumberarray.index(besteval)]
        if printlogs: print('found best move',boardd.ply(),':',bestmove,'with eval:',besteval,'bestmovenumberarray:',bestmovenumberarray,'legal moves:',legalmoves,file=log)
        if printlogs: print('',file=log)
        return bestmove

def findsinglebestmove3(boardd,depth,zval,materialadv=0,currentdepth=0,alpha=-999999999,beta=999999999):

    #is game over
    if boardd.is_game_over():
        if printlogs: print('found game over,returning',file=log)
        return boardd.peek(),gameover(boardd)

    #turn and FEN
    turn = boardd.turn
    FEN = boardd.fen()

    #printinglogs
    movestack = boardd.move_stack
    if printlogs:print("inside func, stack:",movestack[len(movestack)-currentdepth-1:len(movestack)],"materialadv:",materialadv,"FEN:",FEN,"depth:",currentdepth,file=log)
    


    
    #looking for previous analysis
    oldlegal = []
    legalmoves = []
    global transtable
    global gamezvals
    global zarray
    table = transtable[zval%len(transtable)]
    if not table == []:
        if table[0] == zval:
            if not table[1][0:table[1].index(' ')]==FEN[0:FEN.index(' ')]:
                print("ERROR: borad:",FEN,"t:",table[1])

            else:
                #if depths are similar in analysis
                if table[2] <= currentdepth: #maybe change 
                    if printlogs:print('found table entry returning',table[3],table[4],file=log)
                    return table[3],table[4]

                else:
                    oldlegal = table[5]
                    previousevals = table[6]
    
    #AT DEPTH
    if currentdepth==depth:
        
        evall = evalpos2(boardd,materialadv)
        '''
        if turn:
            evall = Quiesce(boardd,materialadv,zval,alpha,beta)
        else:
            evall = Quiesce(boardd,materialadv,zval,-beta,-alpha)
        '''
        if printlogs:print("at depth, returning with eval:",evall,file=log)
        transtable[zval%len(transtable)] = [zval,boardd.fen(),currentdepth,None,evall,[],[]]
        return None,evall

    #ORDERING MOVES: TODO
    if oldlegal==[]:
        legalmoves = list(boardd.legal_moves)

        for move in legalmoves:
            z = makezobristmove(boardd,move,zval,zarray)
            if z in gamezvals:
                legalmoves.pop(legalmoves.index(move))
        #add ordering stuff?
    else:
        
        #previous alpha or betacutoff
        if len(previousevals)<len(oldlegal):
            breaker = len(previousevals)-1
            legalmoves.append(oldlegal[breaker])
            oldlegal.pop(breaker)
            previousevals.pop(breaker)
        
        for i in range(len(previousevals)):
            if turn:
                besteval = previousevals.index(max(previousevals))
            else:
                besteval = previousevals.index(min(previousevals))
            
            legalmoves.append(oldlegal[besteval])
            oldlegal.pop(besteval)
            previousevals.pop(besteval)
        
        #adding moves that didn't get eval
        for i in range(len(oldlegal)):
            legalmoves.append(oldlegal[i])
    
    tempboard = boardd.copy()
    bestmovearray = []

    for i in range(len(legalmoves)):
        move = legalmoves[i]
        tempboard.push(move)
        newzval,newmaterialadv = makezobristmoveandmaterial(boardd,move,zval,zarray,materialadv)

            

        movething,evall = findsinglebestmove3(tempboard,depth,newzval,newmaterialadv,currentdepth+1,alpha,beta)

        if turn:
            bestmovearray.append(evall)
            if evall>=beta:
                break
            alpha = max(bestmovearray)
        else:
            bestmovearray.append(evall)
            if evall<=alpha:
                break
            beta = min(bestmovearray)
    
        tempboard.pop()

    if turn:
        bestval = max(bestmovearray)
    else:
        bestval = min(bestmovearray)
    bestmove = legalmoves[bestmovearray.index(bestval)]
    transtable[zval%len(transtable)] = [zval,FEN,currentdepth,bestmove,bestval,legalmoves,bestmovearray]



    return bestmove,bestval
    

    

def playmove(boardd,nodee,zval):
    global totalevals
    global timespenteval

    global time1
    global time2 
    global time3
    time1 = 0
    time2 = 0
    time3 = 0
    totalevals = 0
    totalbreaks = 0
    totaltime = 0
    timespenteval = 0

    t = time.time()
    if reader.get(boardd) != None:
        #print('bookmove')
        bestmove = reader.choice(boardd).move
        nodee = nodee.add_variation(bestmove)
        print('doingbookmove')
    else:
        #bestmove = (findsinglebestmove(boardd,2))
        #bestmove = findsinglebestmove2(boardd,3,zval)
        materialadv = materialadvantagecalc(boardd.fen())
        bestmove,evall = findsinglebestmove3(boardd,2,zval,materialadv)
        if printlogs: print("SENDING MOVE",boardd.ply(),":",bestmove,file=log)
        nodee = nodee.add_variation(bestmove)
    
    zval = makezobristmove(boardd,bestmove,zval,zarray)
    gamezvals.append(zval)
    boardd.push(bestmove)
    if printlogs: print(boardd,file=log)
    if printlogs: print('------------------',file=log)
    print(totalevals,time.time()-t,timespenteval,time.time()-t-timespenteval)
    print(timespenteval)
    print(time1,time2,time3)
    return boardd,nodee,zval
 

def initialize():
    global zarray
    global transtable
    global gamezvals

    gamezvals = []

    zarray = makezobrist()
    transtable = [[] for i in range(10000000)]
    print(len(transtable))

#def playgame(materialadvmult,attacksmult,pinnedmult,pawnranksmult):
    #bmaterial

materialadvmult = 1000
attacksmult = 50
pinnedmult = 300
pawnranksmult = 75

piecevalues = [1,3,3,5,9,100]

for i in range(1):
    board4 = chess.Board()
    game = chess.pgn.Game()
    game.setup(board4)
    node = game
    movenum = 0

    #zobrist stuff
    initialize()
    global zarray
    zval = board2zobrist(board4,zarray)


    while not board4.is_game_over():
        movenum +=1
        board4,node,zval = playmove(board4,node,zval)
        print(game)
        print('')
        print(game,file=log2)


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