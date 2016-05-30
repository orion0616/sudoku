CXX = g++
OBJS = main.o sudoku.o

sudoku: $(OBJS)
	$(CXX) -Wall -std=c++11 -O2 -o $@ $(OBJS)
.cc.o:
	$(CXX) -c $<

main.o: sudoku.h
sudoku.o: sudoku.h

clean:
	rm -f *.o
