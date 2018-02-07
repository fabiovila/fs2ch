CPP 	= 		g++
LD  	= 		ld
LIB		=		/usr/lib
CPPFLAGS += 	-std=c++14 
LDFLAGS  +=   	-lstdc++   

DEBUG = -g

TARGETS = $(patsubst %.cpp, %, $(wildcard *.cpp))
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

.PHONY: all $(OBJECTS) $(TARGETS)

all: new-file $(OBJECTS) $(TARGETS)
	@./test
	diff ./output/jquery-3.3.1.min.js.zip ./input/jquery-3.3.1.min.js.zip
	diff ./output/jquery-3.3.1.min.js ./input/jquery-3.3.1.min.js
	diff ./output/image-origin.txt ./input/image-origin.txt
	diff ./output/pexels-photo-24821.jpg ./input/pexels-photo-24821.jpg
	@echo FINISHED

$(OBJECTS): %.o: %.cpp
	@$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGETS): %: %.o
	@$(CPP)	$(LDFLAGS) -o $@ $^  
	
new-file:
	@rm -f fs-test.h
	@mkdir -p output
	@rm -f output/*
	@../fs2ch input fs-test.h

