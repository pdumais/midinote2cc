Exceptions=
SOURCES=$(filter-out $(EXCEPTIONS),$(wildcard ./*.cpp))
OBJ=$(SOURCES:.cpp=.o)
CFLAGS=-g -D _DEBUG -std=c++17 -I ./tclap/include

all: app



.cpp.o:
	g++ $(CFLAGS) -c $< -o $@

app: $(OBJ)
	g++ $(OBJ) -lasound -o midinote2cc 

clean:
	-rm midinote2cc
	-rm *.o


