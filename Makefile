all:
	g++ -pthread CASConsensus.cpp Node.cpp SeqObject.cpp LFUniversal.cpp main2.cpp -o programLF
	g++ -pthread CASConsensus.cpp Node.cpp SeqObject.cpp Universal.cpp main.cpp -o program


clean:
	rm -f  program progrmaLF *.o

# all2: