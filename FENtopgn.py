from math import pi
from re import A, X
import chess
import io
import chess.pgn
import chess.polyglot
import random
import time
import multiprocessing
from zobristfunctions import makezobrist,board2zobrist,makezobristmove3

file = open("FENS.txt",'r')

firstline = file.readline()
b = chess.Board(firstline)
game = chess.pgn.Game()
game.setup(b)  
node = game

lines = file.readlines()

for i in range(len(lines)):
    moves = list(b.legal_moves)
    for j in range(len(moves)):
        b.push(moves[j])
        FEN = b.fen()
        if lines[i][0:lines[i].index(' ')]==FEN[0:FEN.index(' ')]:
            node = node.add_variation(moves[j])
            break
        b.pop()


#node = node.add_variation(bestmove)
#b.push(bestmove)


print(game)