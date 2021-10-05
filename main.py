from re import A
import chess
from chess.engine import BestMove
import chess.pgn
import io
from copy import deepcopy
import random
import chess.polyglot
import time
from zobristfunctions import makezobrist,board2zobrist2,makezobristmove,makezobristmoveandmaterial

printlogs = True
depthh = 2
if printlogs: log = open('log.txt','w')
reader = chess.polyglot.open_reader("baron30.bin")

#
def initialize():
    global zarray
    global transtable
    global gamezvals

    gamezvals = []

    zarray = makezobrist()
    transtable = [[] for i in range(10000000)]

def gameover(boardd):
    result = boardd.outcome().result()
    turn = boardd.turn
    if printlogs: print('found position results in game over', file=log)
    if result == "1-0":
        if turn:
            return 100000000
        else:
            return -100000000
    elif result == "0-1":
        if turn:
            return -100000000
        else:
            return 100000000
    else:
        return 0  



def rootsearch(boardd,depth):

    #'''
    if reader.get(boardd) != None:
        print('book move')
        return reader.choice(boardd).move
    #'''

    global zarray
    zval,materialadv = board2zobrist2(boardd,zarray)


    legalmoves = list(boardd.legal_moves)
    lenlegal = len(legalmoves)

    if lenlegal == 1:
        return legalmoves[0]


    #need to add pruning / move ordering, should be pretty easy, might move the makezobristmoveandmaterial function
    allevals = []
    bestmove = None
    alpha = -999999999
    beta = 999999999
    for i in range(lenlegal):
        move = legalmoves[i]
        newzval,newmaterial = makezobristmoveandmaterial(boardd,move,zval,zarray,materialadv)
        boardd.push(move)
        if boardd.is_repetition(2):
            boardd.pop()
        else:
            evall = -alphabeta(boardd,newzval,newmaterial,depth,-beta,-alpha)
            allevals.append(evall)
            if evall>alpha:
                alpha=evall
                bestmove = move
 
            boardd.pop()
    
    if printlogs: print("\n\n")
    #if printlogs: print("LEGAL MOVES:",legalmoves,"EVALS:",allevals)
    if printlogs: print("SENDING MOVE:",boardd.ply(),"eval:",alpha,'move:',bestmove)

    if bestmove != None:
        return bestmove
    else:
        return legalmoves[0]


def alphabeta(boardd,zval,materialadv,depth,alpha,beta):

    if boardd.is_game_over():
        evall = gameover(boardd)
        return evall

    #cheking transtable
    global transtable
    FEN = boardd.fen()
    legalmoves = []
    table = transtable[zval%len(transtable)]
    if not table == []:
        if zval==table[0]:
            if table[1][0:table[1].index(' ')]!=FEN[0:FEN.index(' ')]:
                print('ERROR:',table[1],":",FEN)
            else:
                if table[2] <= depth:
                    return table[3]
                else:
                    legalmoves = table[4]
                    evals = table[5]
    
    #need table stuff pt 1
    if depth ==0:
        #quick = quiesce(boardd,zval,materialadv,alpha, beta )
        quick = evaluation(boardd,materialadv)
        return quick

    legalmoves = list(boardd.legal_moves)
    evals = []

    for i in range(len(legalmoves)):
        move = legalmoves[i]
        newzval,newmaterial = makezobristmoveandmaterial(boardd,move,zval,zarray,materialadv)
        boardd.push(move)
        score =  -alphabeta(boardd,newzval,newmaterial,depth-1, -beta, -alpha)
        evals.append(score)
        if score >= beta:
            boardd.pop()
            return beta
        if score > alpha:
            alpha = score;
        boardd.pop()

    transtable[zval%len(transtable)] = [zval,FEN,depth,alpha,legalmoves,evals]
    return alpha

def quiesce(boardd,zval,materialadv,alpha,beta):
    
    if printlogs: print("INSIDE QUIESCE. zval,material",zval,materialadv,file=log)
    table = transtable[zval%len(transtable)]
    FEN = boardd.fen()
    if not table == []:
        if zval==table[0]:
            if table[1][0:table[1].index(' ')]!=FEN[0:FEN.index(' ')]:
                print('ERROR:',table[1],":",FEN)
            else:
                if table[2] <= -1:
                    if printlogs: print("Quiesce: found table entry returning:",table[3],file=log)
                    return table[3]
                else:
                    legalmoves = table[4]
                    evals = table[5]
    
    stand_pat = evaluation(boardd,materialadv)
    if stand_pat >= beta:
        if printlogs: print("quiesce: found stand_pat:",stand_pat,">= beta:",beta,"returning beta",file=log)
        return beta
    if alpha < stand_pat:
        if printlogs: print("quiesce: alpha:",alpha,"<",stand_pat,"alpha=stand_pat",file=log)
        alpha=stand_pat
    
    legalmoves = list(boardd.legal_moves)
    
    evals = [stand_pat]
    
    for i in range(len(legalmoves)):
        move = legalmoves[i]
        newzval,newmaterial = makezobristmoveandmaterial(boardd,move,zval,zarray,materialadv)
        if (boardd.is_capture(move) or boardd.gives_check(move)) and abs(newmaterial-materialadv)>alpha: #not sure about last part
            if printlogs: print('quiesce: testing out next move:',move,file=logs)
            boardd.push(move)
            score = -quiesce(boardd,newzval,newmaterial,-beta,-alpha)
            evals.append(score)
            boardd.pop()

            if score >= beta:

                return beta
            if score > alpha:
                alpha=score

    transtable[zval%len(transtable)] = [zval,FEN,-1,alpha,legalmoves,evals]
    return alpha

def evaluation(boardd,materialadv):
    #return materialadv*1000
    if boardd.turn:
        if printlogs: print(boardd.fen(),'white to move, eval:',materialadv*1000,file=log)
        return materialadv*1000
    else:
        if printlogs: print(boardd.fen(),'black to move, eval:',-materialadv*1000,file=log)
        return -materialadv*1000

def playselfgame():
    initialize()
    boardd = chess.Board()
    game = chess.pgn.Game()
    game.setup(boardd)  
    node = game

    while not boardd.is_game_over():
        bestmove = rootsearch(boardd,depthh)
        node = node.add_variation(bestmove)
        boardd.push(bestmove)
        if printlogs: print(boardd,file=log)
        print(game)
    print('#################')
    print('DONE')
    print(boardd.result())

playselfgame()


    
    


