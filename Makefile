all: ocrtransport

ocrtransport: ocrtransport.cpp
	g++ -std=c++11 ocrtransport.cpp -o ocrtransport