####################################################
#  Make File for Printer_SRC and IpGet system      #
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
INCLUDES =$(wildcard include/*.h)
MAIN=ipget

#Store if user is root info
IS_ROOT=$(shell whoami)

.PHONY: clean

all:  $(MAIN)
	@echo Program is sucessfull compiled;


$(MAIN): $(SOURCE)
	
	$(CXX) $(CFLAGS) -o $(MAIN) $^

static: $(SOURCE)

	$(CXX) $(CFLAGS) -o $(MAIN) -static $^
	
	
install:

	if [ "$(shell whoami)" = "root" ]; then \
		install -c -m 755  $(MAIN) /usr/bin; \
	else \
		sudo /usr/bin/install -c -m 755  $(MAIN) /usr/bin; \
	fi;

clean:
	rm -f $(MAIN) *.o

config:
	@echo Searching Dependences unsolved... 
	@./configure
	


