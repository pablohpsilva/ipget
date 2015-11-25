####################################################
#  Make File for Printer_SRC system		   #
#						   #
#						   #
#						   #
#						   # 
####################################################

#Chose Compiler 
CXX=g++

CFLAGS=-g -Wall 
LDFLAGS=-L -lc
SOURCE=$(wildcard src/*.cpp)
#INCLUDES =$(wildcard *.h)
MAIN=ipget


.PHONY: clean

all:  $(MAIN)
	@echo Program is already compiled;


$(MAIN): $(SOURCE)
	
	$(CXX) $(CFLAGS)-o $(MAIN) $^

	
install:
	/usr/bin/install -c -m 755  $(MAIN) /usr/bin; 


clean:
	rm -f $(MAIN) *.o

config:
	@echo Searching Dependences unsolved... 
	@./configure
	


