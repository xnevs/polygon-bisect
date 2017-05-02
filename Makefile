all: a.out

a.out: main.cpp
	g++ -O3 -Wall main.cpp
