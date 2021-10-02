from math import pi
import chess
import io
import chess.pgn
import chess.polyglot
import random





def makezobrist():
    zobrist = []
    for i in range(12):
        temparray = []
        for j in range(64):
            temparray.append(random.getrandbits(64))
        zobrist.append(temparray)
    
    temparray = []
    for i in range(13):
        temparray.append(random.getrandbits(64))
        #side to move, castling, en pissant
    zobrist.append(temparray)
    return zobrist

def board2zobrist(boardd,zobristarray):
    #getting all pieces
    zhash = 0
    for i in range(64):
        piecetype = boardd.piece_type_at(i)

        if piecetype != None:
            
            color = boardd.color_at(i)

            if not color:
                piecetype += 6
                #increasing the row if the piece is black
            
            zhash = zhash^zobristarray[piecetype-1][i]
    
    for i in range(13):
        zhash = zhash^zobristarray[12][i]
    #for side to move

    return zhash

def makezobristmove(boardd,move,zval,zarray):
    fromsquare = move.from_square
    tosquare = move.to_square
    piecemoving = boardd.piece_type_at(fromsquare)
    color = boardd.color_at(fromsquare)
    #color = boardd.turn
    iscapture = boardd.is_capture(move)
    iscastle = boardd.is_castling(move)
    promotion = move.promotion

    #removing piece from square it is on
    if color:
        zval=zval^zarray[piecemoving-1][fromsquare]
    else:
        zval=zval^zarray[piecemoving+5][fromsquare]
    
    if promotion != None:
        piecemoving = promotion
    
    #adding piece to new location
    if color:
        zval = zval^zarray[piecemoving-1][tosquare]
    else:
        zval = zval^zarray[piecemoving+5][tosquare]
    
    #is capture, remove old piece
    if iscapture:
        if not boardd.is_en_passant(move):
            removedpiece = boardd.piece_type_at(tosquare)
            if not color:
                removedpiece = removedpiece+6
            
            zval = zval^zarray[removedpiece-1][tosquare]
        else: #is enpassant
            if color:
                removedpiece = 1
                newtosquare = tosquare-8
            else:
                removedpiece = 7
                newtosquare = tosquare+8
            zval = zval^zarray[removedpiece-1][newtosquare]
    
    if iscastle:
        if color:
            if boardd.is_kingside_castling(move):
                zval = zval^zarray[3][7]^zarray[3][5]
            else:
                zval = zval^zarray[3][0]^zarray[3][3]
        else:
            if boardd.is_kingside_castling(move):
                zval = zval^zarray[9][63]^zarray[9][61]
            else:
                zval = zval^zarray[9][56]^zarray[9][59]
    
    #for changing move
    zval = zval^zarray[12][0]
    
    return zval

def makezobristmoveandmaterial(boardd,move,zval,zarray,materialadv):
    fromsquare = move.from_square
    tosquare = move.to_square
    piecemoving = boardd.piece_type_at(fromsquare)
    color = boardd.color_at(fromsquare)
    #color = boardd.turn
    iscapture = boardd.is_capture(move)
    iscastle = boardd.is_castling(move)
    promotion = move.promotion

    #removing piece from square it is on
    if color:
        zval=zval^zarray[piecemoving-1][fromsquare]
    else:
        zval=zval^zarray[piecemoving+5][fromsquare]
    
    if promotion != None:
        piecemoving = promotion
    
    #adding piece to new location
    if color:
        zval = zval^zarray[piecemoving-1][tosquare]
    else:
        zval = zval^zarray[piecemoving+5][tosquare]
    
    #is capture, remove old piece
    capturevals = [1,3,3,5,9,200,-1,-3,-3,-5,-9,-200]
    if iscapture:
        if not boardd.is_en_passant(move):
            removedpiece = boardd.piece_type_at(tosquare)
            if color:
                removedpiece = removedpiece+6
            
            zval = zval^zarray[removedpiece-1][tosquare]
            materialadv -= capturevals[removedpiece-1] 
        else: #is enpassant
            if not color:
                removedpiece = 1
                newtosquare = tosquare-8
                materialadv +=1
            else:
                removedpiece = 7
                newtosquare = tosquare+8
                materialadv -=1
            zval = zval^zarray[removedpiece-1][newtosquare]

    
    if iscastle:
        if color:
            if boardd.is_kingside_castling(move):
                zval = zval^zarray[3][7]^zarray[3][5]
            else:
                zval = zval^zarray[3][0]^zarray[3][3]
        else:
            if boardd.is_kingside_castling(move):
                zval = zval^zarray[9][63]^zarray[9][61]
            else:
                zval = zval^zarray[9][56]^zarray[9][59]
    
    #for changing move
    zval = zval^zarray[12][0]
    
    return zval,materialadv





'''
zobristarray = makezobrist()
zval = board2zobrist(boardd,zobristarray)
move = boardd.peek()
tempboard = boardd.copy()
tempboard.pop()
print(move.promotion)
print(move.from_square)
print(move.to_square)
print(makezobristmove(tempboard,move,zval,zobristarray))
'''
