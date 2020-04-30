#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define MEMORY_SIZE 10000

uint8_t *head;

void within_range(uint8_t *now){
	if(now-head<0 || now>head+MEMORY_SIZE){
		std::cerr << "now:" << now << " head:" << head << std::endl;
		std::cerr << "now-head:" << (int)(now-head) << std::endl;
		std::cerr << "point out of range." << std::endl;
		std::exit(1);
	}
}


void processor(std::string code){
	int index=0;
	int size=code.size();
	char c;
	uint8_t *memory;

	memory=(uint8_t *)malloc(sizeof(uint8_t)*MEMORY_SIZE);
	head=memory;

	while(index<size){
		switch(code[index]){
			case '>':
				within_range(++memory);
				break;
			case '<':
				within_range(--memory);
				break;
			case '+':
				(*memory)++;
				break;
			case '-':
				(*memory)--;
				break;
			case '.':
				//std::cout << "out";
				std::cout << *memory;
				break;
			case ',':
				std::cin >> *memory;
				break;
			case '[':
				if(*memory==0)
					while(code[index]!=']') index++;
				break;
			case ']':
				if(*memory!=0)
					while(code[index]!='[') index--;
				break;
		}
		index++;
	}
}

int main(int argc,char *argv[]){
	if(argc!=2){
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./Brainwash brainfuck_script" << std::endl;
	}

	std::ifstream file;
	file.open(argv[1]);

	if(!file){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	std::stringstream strStream;
	strStream << file.rdbuf();
	std::string str=strStream.str();
	
	//std::cout << str << std::endl;

	processor(str);

	std::cout << std::flush;
}
