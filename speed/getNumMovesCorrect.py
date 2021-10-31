import chess

fileread = open('chessPositions.txt', 'r')
filewrite = open('correctChessPos.txt', 'w')

lines_fileread = fileread.readlines()

for line in lines_fileread:
    spaces = line.split(' ')
    fen = spaces[0] + ' ' + spaces[1] + ' ' + spaces[2] + ' ' + spaces[3] + ' ' + spaces[4] + ' ' + spaces[5]
    
    board = chess.Board(fen)
    correct_num_moves = len(list(board.legal_moves))
    if correct_num_moves != int(spaces[7]):
        write_to_line = fen + ' Mine vs stockfish ' + spaces[7].strip() + ', ' + str(correct_num_moves) + '\n'
        filewrite.writelines(write_to_line)