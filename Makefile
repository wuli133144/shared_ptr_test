



SRC := $(wildcard *.cpp)


CC := clang++  
LDFLAGS_COMMON = -std=c++11
INCLUDE :=  -I ./include/   -I./include/util/  -I ./include/sigslot
LIB     := -L./lib/  -L ./   -ltarsutil

object := test

$(object):
	$(CC)  -std=c++11  -o $@   $(INCLUDE) $(SRC) $(LIB)


clean:
	rm -rf *.o 







