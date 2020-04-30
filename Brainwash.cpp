#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/ioctl.h>

#define MEMORY_SIZE 10000

int row;
int column;
uint8_t *head;

void within_range(uint8_t *now){
	if(now-head<0 || now>head+MEMORY_SIZE){
		std::cerr << "now:" << now << " head:" << head << std::endl;
		std::cerr << "now-head:" << (int)(now-head) << std::endl;
		std::cerr << "point out of range." << std::endl; std::exit(1); } }

void display_array(uint8_t *memory,char *output){
	int i;
	int x=2;
	int y=2;
	int address=memory-head;
	int box_num=(column-4)/5;
	uint8_t *pointer;
	uint8_t *pointer_start;
	static int index_start=0;

	//printf("\033[2J");
	std::system("clear");

	if(address==(index_start+box_num-1)){
		index_start++;
	}else if(address==index_start){
		index_start--;
	}

	printf("\033[%d;%dH",x,y);
	for(i=index_start;i<(index_start+box_num);i++){
		printf("+%3d",i);
	}
	printf("+\n");
	
	printf("\033[%d;%dH",++x,y);
	pointer_start=head+sizeof(uint8_t*)*index_start;
	for(pointer=pointer_start; pointer<(pointer_start+box_num); pointer++){
		printf("|%3d",*(pointer));
	}
	printf("|\n");
	
	printf("\033[%d;%dH",++x,y);
	for(i=0;i<box_num;i++){
		printf("+---");
	}
	printf("+\n");
	
	printf("\033[%d;%dH",++x,y);
	for(i=0;i<address-index_start;i++){
		printf("    ");
	}
	printf("  ^\n");
	
	printf("\033[%d;%dH",++x,y);
	printf("output:%s",output);
}

void processor(std::string code){
	char output[100000];
	int ms=50;
	int index=0;
	int len_out=0;
	int size=code.size();
	char c;
	uint8_t *memory;

	// ms to us
	ms*=1000;
	memory=(uint8_t *)malloc(sizeof(uint8_t)*MEMORY_SIZE);
	head=memory;

	while(index<size){
		display_array(memory,output);
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
				output[len_out]=*memory;
				len_out++;
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
		usleep(ms);
	}
}

int main(int argc,char *argv[]){
	if(argc!=2){
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./Brainwash brainfuck_script" << std::endl;
	}

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	std::cout << "row:" << size.ws_row << std::endl;
	std::cout << "column:" << size.ws_col << std::endl;
	
	row=size.ws_row;
	column=size.ws_col;

	std::ifstream file;
	file.open(argv[1]);

	if(!file){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	std::stringstream strStream;
	strStream << file.rdbuf();
	std::string str=strStream.str();

	processor(str);

	std::cout << std::flush;
}
