all:
	g++ -pthread CASConsensus.cpp Node.cpp SeqObject.cpp Universal.cpp main.cpp -o program

clean:
	rm -f  *.o

# all: program

# program: CASConsensus.o Node.o SeqObject.o Universal.o main.o
# 	g++ -pthread CASConsensus.o Node.o SeqObject.o Universal.o main.o -o program

# CASConsensus.o: CASConsensus.cpp CASConsensus.h
# 	g++ -c CASConsensus.cpp

# Node.o: Node.cpp Node.h
# 	g++ -c Node.cpp

# SeqObject.o: SeqObject.cpp SeqObject.h
# 	g++ -c SeqObject.cpp

# Universal.o: Universal.cpp Universal.h
# 	g++ -c Universal.cpp

# main.o: main.cpp
# 	g++ -c main.cpp

# clean:
# 	rm -f program *.o
