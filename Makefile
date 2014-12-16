all: Main.cpp binarysearchtree.h
	g++ -stdlib=libc++ -std=c++11 Main.cpp -o Main
