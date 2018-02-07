CPP 	= 		g++
LD  	= 		ld
LIB		=		/usr/lib
CPPFLAGS += 	-g -std=c++14 
LDFLAGS  +=   	-lstdc++  -lboost_system  -lboost_filesystem  

DEBUG = -g

TARGETS = $(patsubst %.cpp, %, $(wildcard *.cpp))
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: $(OBJECTS) $(TARGETS) 
	@echo FINISHED

$(OBJECTS): %.o: %.cpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGETS): %: %.o
	$(CPP)	$(LDFLAGS) -o $@ $^  

clean:
	rm -f *.o

