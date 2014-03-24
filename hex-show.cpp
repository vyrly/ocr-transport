#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <algorithm> //std::replace
#include <cassert>
#include <string.h>

// 0123456789ABCDEF
// _N___T_____X_Z__

std::map<char, char> mapping = {{'1','N'},
																{'5','T'},
																{'B','X'},
																{'D','Z'}
																};

std::string readFile(std::string fileName){

	unsigned char x;
	std::ifstream input(fileName, std::ios::binary);
	input >> std::noskipws;

	std::ostringstream ss;

	while (input >> x) {
		ss << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << (unsigned int)x << " ";
	}
	return ss.str();
}

std::string convert2ocr(std::string input){
	std::string	out;
	out = input;
	std::cout << "Converting to ocr readable" << std::endl;

	for ( auto& val : mapping )
	{
		std::cout << "Replacing " << val.first << " with " << val.second << std::endl;
		std::replace( out.begin(), out.end(), val.first , val.second);
	}
	return out;
}

std::string convert2hex(std::string input){
	std::string	out;
	out = input;
	std::cout << "Converting to hex" << std::endl;

	for ( auto& val : mapping )
	{
		std::cout << "Replacing " << val.second << " with " << val.first << std::endl;
		std::replace( out.begin(), out.end(), val.second , val.first);
	}
	return out;
}

void saveFile(std::string fileName, std::string hexString){

	std::ofstream output(fileName + ".out", std::ios::out | std::ios::binary);

	std::istringstream hex_chars_stream(hexString);

	unsigned int c;
	while (hex_chars_stream >> std::hex >> c)
	{
		output.write((char *)&c, sizeof(c));
	}
}

std::string readFromFile(std::string fileName){
	std::ifstream input(fileName);
	input >> std::noskipws;
	std::ostringstream ss;
	unsigned char x;
	while (input >> x) {
		ss << x;
	}
  return ss.str();
}

int main(int argc, const char *argv[])
{
	assert (argc >= 3);
	std::string fileName = argv[2];
	if (!strcmp(argv[1], "show")){
		std::cout << "AAAAAA" << std::endl;
		std::string hexString = readFile(fileName);
		//std::cout << hexString << std::endl;
		std::string converted = convert2ocr(hexString);
		std::cout << std::endl << std::endl << converted << std::endl << std::endl << std::endl;
	}
	else if (!strcmp(argv[1], "decode")){
		std::cout << "BBBBBB" << std::endl;
		std::string input = readFromFile(fileName);
		std::string hexString2 = convert2hex(input);
		std::cout << hexString2 << std::endl;
		saveFile(fileName, hexString2);
	}

  return 0;
}
