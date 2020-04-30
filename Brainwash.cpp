#include <cstdio>
#include <cstring>
#include <cstdlib>
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
		std::cerr << "point out of range." << std::endl; std::exit(1); }
}

void create_flame(){
	int i;

	printf("\033[%d;%dH",++x,y);
	printf("#");
	for(i=1;i<column-30;i++)
		printf("=");

	printf("#\n");

}
	
bool is_token(char c){
	int i;
	char tokens[]="><+-,.[]";
	for(i=0;i<8;i++){
		if(tokens[i]==c) return true;
	}
	return false;
}

void display_code(std::string code,int now,char *output){
	int index=0;
	bool flag=false;

	//show source
	printf("\033[%d;%dH",++x,y);
	printf("code\n");
	create_flame();
	printf("\033[%d;%dH",++x,y+2);
	while(index<code.size()){
		if(is_token(code[index])){
			if(index==now){
				printf("\033[47m");
				printf("%c",code[index]);
				printf("\033[49m");
			}else{
				printf("%c",code[index]);
			}

			if((index+1)%(column-33)==0){
				printf("\n");
				printf("\033[%d;%dH",++x,y+2);
			}
		}
		index++;

	}
	create_flame();
	
	//show output
	printf("\033[%d;%dH",++x,y);
	printf("\033[%d;%dH",++x,y);
	printf("output:%s\n",output);

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
	printf("\033[%d;%dH",x,y+2);
	for(i=index_start;i<(index_start+box_num);i++){
		printf("+%3d",i);
	}
	printf("+\n");
	
	printf("\033[%d;%dH",++x,y+2);
	pointer_start=head+sizeof(uint8_t*)*index_start;
	for(pointer=pointer_start; pointer<(pointer_start+box_num); pointer++){
		printf("|%3d",*(pointer));
	}
	printf("|\n");
	
	printf("\033[%d;%dH",++x,y+2);
	for(i=0;i<box_num;i++){
		printf("+---");
	}
	printf("+\n");
	
	//show pointer
	printf("\033[%d;%dH",++x,y+2);
	for(i=0;i<address-index_start;i++){
		printf("    ");
	}
	printf("  ^\n");
}

void processor(std::string code){
	char output[100000];
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
		//visualize
		if(!no_visualize){
			display_array(memory,output);
			display_code(code,index,output);
		}

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
			default:
				index++;
				continue;
		}
		index++;

		if(!no_visualize)
			usleep(ms);
	}
}

int main(int argc,char *argv[]){
	char *filename;
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
			std::cerr << "Usage:./Brainwash -(h|n|s) terget_file" << std::endl;
			std::cerr << "	--help(-h) :show this help" << std::endl;
			std::cerr << "	--no-visualize(-n) :only print result" << std::endl;
			std::cerr << "	--speed=(-s=) :run speed[ms]\n" << std::endl;
			exit(1);
		}
	}else if(argc==2){
		if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0){
			printf("Brainwash -Brainfuck interpreter and visualizer- \n");
			printf("Usage:./Brainwash -(h|n|s) terget_file \n");
			printf("	--help(-h) :show this help\n");
			printf("	--no-visualize(-n) :only print result\n");
			printf("	--speed=(-s=) :run speed[ms]\n\n");
			printf("Auter:Takana Norimasa \n");
			printf("Repository:https://github.com/Takana-Norimasa/Brainwash \n");
			return 0;
		}
		filename=argv[1];
	}else{
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./Brainwash brainfuck_script" << std::endl;
		exit(1);
	}

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	row=size.ws_row;
	column=size.ws_col;

	std::ifstream file;
	file.open(filename);

	if(!file){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	std::stringstream strStream;
	strStream << file.rdbuf();
	std::string str=strStream.str();

	processor(str);

	std::cout << std::endl;
}
