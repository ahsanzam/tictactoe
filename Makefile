#Makefile

all: 
	g++ -g -Wall main.cpp -o main
	./main
clean: 
	rm main