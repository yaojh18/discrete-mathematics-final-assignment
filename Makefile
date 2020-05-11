all: data.h data.cpp init.h init.cpp loader.h loader.cpp main.cpp
	g++ main.cpp loader.cpp init.cpp data.cpp -o main