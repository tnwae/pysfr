CXX=g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic -I../include
OBJS=party_pkmn.o charset.o decoders.o main.o utility.o pack_inventory.o checksum.o

all: $(OBJS)
	@echo "  LD pysfr"
	@$(CXX) -lm -o pysfr $(OBJS)

dumper: charset.o dumper.o decoders.o utility.o
	@echo "  LD dumper"
	@$(CXX) -lm -o dumper charset.o decoders.o dumper.o utility.o

game-dumper: game-dumper.o
	@echo "  LD game-dumper"
	@$(CXX) -o game-dumper game-dumper.o

.SUFFIXES: .cc.o
.c.o: $*.cc
	@echo "  CC $*.cc"
	@$(CXX) $(CXXFLAGS) -c $*.cc

.PHONY: clean
clean:
	@echo "  CLEAN ."
	@rm -f pysfr dumper game-dumper *.o
