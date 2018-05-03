



SRC := $(wildcard *.cpp)


CC := g++ -std=c++11

INCLDUE :=  -I ./include/  ./
LIB     := -L./lib/  -L ./

object := test

$(object):
	$(CC) -o $@ $(SRC)


clean:
	rm -rf *.o 







