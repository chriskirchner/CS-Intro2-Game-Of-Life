PROGS := gol

all: $(PROGS)

gol: Menu.o Display.o Gol.o
	g++ -g Menu.o Display.o Gol.o -o gol -lncurses

Menu.o: Menu.cpp
	g++ -c Menu.cpp

Display.o: Display.cpp Display.hpp
	g++ -c Display.cpp

Gol.o: Gol.cpp Gol.hpp
	g++ -c Gol.cpp

clean:
	rm -f $(PROGS) *.o
