
all: chess

clean:
	-rm main.o chess.exe chess

chess: main.o
	g++ -g -o chess main.cpp

main.o:
	g++ -c -g main.cpp