



SRC := $(wildcard *.cpp)


CC := g++ -std=c++11

INCLUDE :=  -I ./include/   -I./include/util/  -I ./include/sigslot
LIB     := -L./lib/  -L ./   -ltarsutil

object := test

$(object):
	$(CC) -o $@  $(INCLUDE) $(SRC) $(LIB)


clean:
	rm -rf *.o 







