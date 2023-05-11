all: calc

calc:
	g++ -c Interface_raw.cpp Interface_raw.hpp `wx-config --cflags` -O2 
	g++ Interface_raw.o `wx-config --libs` -o Interface_raw 

