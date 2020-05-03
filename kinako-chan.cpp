#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>

#define MEMORY_SIZE 10000

int x;
int y;
int row;
int ms=20;
int column;
uint8_t *head;
bool no_visualize=false;

void within_range(uint8_t *now){
	if(now-head<0 || now>head+MEMORY_SIZE){
		std::cerr << "now:" << now << " head:" << head << std::endl;
		std::cerr << "now-head:" << (int)(now-head) << std::endl;
		std::cerr << "point out of range." << std::endl;
		std::exit(1);
	}
}

void create_flame(){
	int i;

	std::cout << "\033["<< ++x << ";" << y << "H" << std::flush;
	std::cout << "#";
	for(i=1;i<column-30;i++)
		std::cout << "=";

	std::cout << "#" << std::endl;
}
	
bool is_token(char c){
	int i;
	char tokens[]="><+-,.[]";
	for(i=0;i<8;i++){
		if(tokens[i]==c) return true;
	}
	return false;
}

void display_bf(std::string code,int now,char *output){
	int index=0;
	bool flag=false;

	//show source
	std::cout << "\033["<< ++x << ";" << y << "H" << std::flush;
	std::cout << "brainfuck code\n" << std::endl;
	create_flame();
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	while(index<code.size()){
		if(is_token(code[index])){
			if(index==now){
				std::cout << "\033[47m" << std::endl;
				std::cout << code[index] << std::endl;
				std::cout << "\033[49m" << std::endl;
			}else{
				std::cout << code[index] << std::endl;
			}

			if((index+1)%(column-33)==0){
				std::cout << std::endl;
				std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
			}
		}
		index++;

	}
	create_flame();
	
	//show output
	std::cout << "\033["<< ++x << ";" << y << "H" << std::flush;
	std::cout << "\033["<< ++x << ";" << y << "H" << std::flush;
	std::cout << "output" << output << std::endl;

}

void display_array(uint8_t *memory,char *output){
	int i;
	int address=memory-head;
	int box_num=(column-4)/5;
	uint8_t *pointer;
	uint8_t *pointer_start;
	static int index_start=0;

	x=2;
	y=2;

	std::system("clear");

	if(address==(index_start+box_num-1)){
		index_start++;
	}else if(address==index_start && address!=0){
		index_start--;
	}

	//show memory
	std::cout << "\033["<< x << ";" << y+2 << "H" << std::flush;
	for(i=index_start;i<(index_start+box_num);i++){
		std::cout << "+" << std::setw(3) << i << std::flush;
	}
	std::cout << "+" << std::endl;
	
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	pointer_start=head+sizeof(uint8_t*)*index_start;
	for(pointer=pointer_start; pointer<(pointer_start+box_num); pointer++){
		std::cout << "|" << std::setw(3) << *(pointer) << std::flush;
	}
	std::cout << "|" << std::endl;
	
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	for(i=0;i<box_num;i++){
		std::cout << "+---" << std::flush;
	}
	std::cout << "+" << std::endl;
	
	//show pointer
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	for(i=0;i<address-index_start;i++){
		std::cout << "    " << std::flush;
	}
	std::cout << "  ^" << std::endl;
}

void processor(std::string bf,std::wstring kinako){
	char output[100000];
	int index=0;
	int len_out=0;
	int size=bf.size();
	char c;
	uint8_t *memory;

	// ms to us
	ms*=1000;
	memory=(uint8_t *)malloc(sizeof(uint8_t)*MEMORY_SIZE);
	head=memory;

	while(index<size){
		//visualize
		if(!no_visualize){
			display_array(memory,output);
			display_bf(bf,index,output);
		}

		switch(bf[index]){
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
				output[len_out]=*memory;
				len_out++;
				std::cout << *memory;
				break;
			case ',':
				std::cin >> *memory;
				break;
			case '[':
				if(*memory==0)
					while(bf[index]!=']') index++;
				break;
			case ']':
				if(*memory!=0)
					while(bf[index]!='[') index--;
				break;
			default:
				index++;
				continue;
		}
		index++;

		if(!no_visualize)
			usleep(ms);
	}
}

std::string knk2bf(std::wstring kinako){
	std::string bf;
	while(0){}
	return bf;
}

int main(int argc,char *argv[]){
	char *filename;
	std::locale::global(std::locale(""));
	
	if(argc==3){
		filename=argv[2];
		if(strcmp(argv[1],"--no-visualize")==0 || strcmp(argv[1],"-n")==0){
			no_visualize=true;
		}else if(strncmp(argv[1],"--speed=",8)==0 || strncmp(argv[1],"-s=",3)==0){
			char *str=argv[1];
			while(*(str++)!='=');
			ms=strtol(str,&str,10);
		}else{
			std::cerr << "Invalid argument." << std::endl;
			std::cerr << "Usage: ./kinako-chan -(h|n|s) terget_file" << std::endl;
			std::cerr << "	--help(-h) :show this help" << std::endl;
			std::cerr << "	--no-visualize(-n) :only print result" << std::endl;
			std::cerr << "	--speed=(-s=) :run speed[ms]\n" << std::endl;
			exit(1);
		}
	}else if(argc==2){
		if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0){
			std::cout << "kinako-chan -Brainfuck interpreter and visualizer- " << std::endl;
			std::cout << "Usage: ./kinako-chan -(h|n|s) terget_file " << std::endl;
			std::cout << "	--help(-h) :show this help" << std::endl;
			std::cout << "	--no-visualize(-n) :only print result" << std::endl;
			std::cout << "	--speed=(-s=) :run speed[ms]\n" << std::endl;
			std::cout << "Auter:Takana Norimasa " << std::endl;
			std::cout << "Repository:https://github.com/Takana-Norimasa/kinako-chan " << std::endl;
			return 0;
		}
		filename=argv[1];
	}else{
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./kinako-chan brainfuck_script" << std::endl;
		exit(1);
	}

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	row=size.ws_row;
	column=size.ws_col;


	std::wifstream file(filename);

	if(!file){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	std::wstringstream wss;
	wss << file.rdbuf();
	std::wstring source=wss.str();

	//std::string bf=knk2bf(source);
	//processor(bf,source);

	std::cout << std::endl;
}
