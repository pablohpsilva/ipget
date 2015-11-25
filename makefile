####################################################
#  Make File for Printer_SRC system		   #
#						   #
#						   #
#						   #
#						   # 
####################################################

#Chose Compiler 
CXX=g++

CFLAGS=-g -std=c++11 -Wreturn-local-addr
#CFLAGS=-g -Wreturn-local-addr
LDFLAGS=-L 
SOURCE=$(wildcard src/*.cpp)
#INCLUDES =$(wildcard *.h)
MAIN=ipget


.PHONY: clean

all:  $(MAIN)
	@echo Program is sucessfull compiled;


$(MAIN): $(SOURCE)
	
	$(CXX) $(CFLAGS) -o $(MAIN) $^

static: $(SOURCE)

	$(CXX) $(CFLAGS) -o $(MAIN) -static $^
	
	
install:
	sudo /usr/bin/install -c -m 755  $(MAIN) /usr/bin; 


clean:
	rm -f $(MAIN) *.o

config:
	@echo Searching Dependences unsolved... 
	@./configure
	


