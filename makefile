all:
	g++ -o main main.cpp LinkedList.h
win:
	cl /EHsc main.cpp LinkedList.h
