#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc,char *argv[]){
	FILE *file;
	std::vector<uint8_t> memory;

	if(argc!=2){
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./Brainwash brainfuck_script" << std::endl;
	}

	std::ifstream ifs(argv[1]);
	if(!ifs){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	std::string buf;
	std::getline(ifs,buf);
	if(!ifs){
		std::cerr << "failed to load buffer." << std::endl;
		std::exit(1);
	}

	std::cout << buf << std::endl;
}
