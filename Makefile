CC = g++
CFLAGS = -std=c++11 -c -g -Og -Wall -Werror -pedantic
OBJ = main.o StringSound.o CircularBuffer.o
DEPS = main.cpp StringSound.cpp StringSound.h CircularBuffer.cpp CircularBuffer.h
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXE = KSGuitarSim

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJ) $(EXE)
