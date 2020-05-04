#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdint.h>
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

	//show source
	std::cout << "\033["<< ++x << ";" << y << "H" << std::flush;
	std::cout << "brainfuck code\n" << std::endl;
	create_flame();
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;

	while(index<code.size()){
		if(is_token(code[index])){
			if(index==now){
				std::cout << "\033[47m" << std::flush;
				std::cout << code[index];
				std::cout << "\033[49m" << std::flush;
			}else{
				std::cout << code[index];
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
	std::cout << "output: " << output << std::endl;

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
		std::cout << "+" << std::setw(3) << i;
	}
	std::cout << "+" << std::endl;
	
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	pointer_start=head+sizeof(uint8_t*)*index_start;
	for(pointer=pointer_start; pointer<(pointer_start+box_num); pointer++){
		std::cout << "|" << std::setw(3) << unsigned(*(pointer));
	}
	std::cout << "|" << std::endl;
	
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	for(i=0;i<box_num;i++){
		std::cout << "+---";
	}
	std::cout << "+" << std::endl;
	
	//show pointer
	std::cout << "\033["<< ++x << ";" << y+2 << "H" << std::flush;
	for(i=0;i<address-index_start;i++){
		std::cout << "    ";
	}
	std::cout << "  ^" << std::endl;
}

void processor(std::string bf,std::wstring kinako){
	char output[10000];
	int index=0;
	int len_out=0;
	int size=bf.size();
	uint8_t *memory;

	// ms to us
	ms*=1000;
	memory=(uint8_t *)calloc(MEMORY_SIZE,sizeof(uint8_t));
	head=memory;

	while(index!=size){
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
		}
		
		//visualize
		if(!no_visualize){
			display_array(memory,output);
			display_bf(bf,index,output);
		}

		index++;

		if(!no_visualize)
			usleep(ms);
	}
}

void bf2knk(std::wstring bf){
	int index=0;

	std::cout << "--brainfuck code--" << std::endl;
	while(index!=bf.size()){
		switch(bf[index]){
			case '+':
				std::cout << "黄奈子ちゃん黄奈子ちゃん";
				break;
			case '-':
				std::cout << "黄奈子ちゃん黃奈子ちゃん";
				break;
			case '>':
				std::cout << "黃奈子ちゃん黄奈子ちゃん";
				break;
			case '<':
				std::cout << "黃奈子ちゃん黃奈子ちゃん";
				break;
			case '.':
				std::cout << "黃奈子ちゃん黄奈孑ちゃん";
				break;
			case ',':
				std::cout << "黃奈子ちゃん黃奈孑ちゃん";
				break;
			case '[':
				std::cout << "黄奈子ちゃん黄奈孑ちゃん";
				break;
			case ']':
				std::cout << "黄奈孑ちゃん黄奈子ちゃん";
				break;
		}
		index++;
	}
	std::cout << std::endl;
}

std::string knk2bf(std::wstring kinako){
	int index=0;
	std::string bf="";
	while(index!=kinako.size()){
		if(kinako.compare(index,12,L"黄奈子ちゃん黄奈子ちゃん")==0){
			bf.append("+");
		}else if(kinako.compare(index,12,L"黄奈子ちゃん黃奈子ちゃん")==0){
			bf.append("-");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黄奈子ちゃん")==0){
			bf.append(">");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黃奈子ちゃん")==0){
			bf.append("<");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黄奈孑ちゃん")==0){
			bf.append(".");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黃奈孑ちゃん")==0){
			bf.append(",");
		}else if(kinako.compare(index,12,L"黄奈子ちゃん黄奈孑ちゃん")==0){
			bf.append("[");
		}else if(kinako.compare(index,12,L"黄奈孑ちゃん黄奈子ちゃん")==0){
			bf.append("]");
		}
		index+=12;
	}

	return bf;
}

void syntax_check(std::wstring& source){
	int index=0;
	std::wstring tokens=L"黄奈子ちゃん黃孑";
	while(index!=source.size()){
		if(tokens.find(source[index])==std::wstring::npos){
			source.erase(index,1);
		}else{
			index++;
		}
	}

	if(source.size()%12!=0){
		std::cerr << "undefined token." << std::endl;
	}
}

int main(int argc,char *argv[]){
	bool bfmode=false;
	bool knktobf=false;
	bool bftoknk=false;
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
		}else if(strncmp(argv[1],"--convert",10)==0 || strncmp(argv[1],"-c",2)==0){
			bftoknk=true;
		}else if(strncmp(argv[1],"--rev-convert",13)==0 || strncmp(argv[1],"-r",2)==0){
			knktobf=true;
		}else if(strncmp(argv[1],"--brainfuck",12)==0 || strncmp(argv[1],"-b",2)==0){
			bfmode=true;
		}else{
			std::cerr << "Invalid argument." << std::endl;
			std::cerr << "Usage: ./kinako-chan -(h|n|s) terget_file" << std::endl;
			std::cerr << "	--help(-h) :show this help" << std::endl;
			std::cerr << "	--no-visualize(-n) :only print result" << std::endl;
			std::cout << "	--convert(-c) :convert brainfuck to kinako-chan " << std::endl;
			std::cout << "	--rev-convert(-r) :convert kinako-chan to brainfuck " << std::endl;
			std::cerr << "	--speed=(-s=) :run speed[ms]\n" << std::endl;
			exit(1);
		}
	}else if(argc==2){
		if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0){
			std::cout << "kinako-chan -Brainfuck interpreter and visualizer- " << std::endl;
			std::cout << "Usage: ./kinako-chan -(h|n|s) terget_file " << std::endl;
			std::cout << "	--help(-h) :show this help" << std::endl;
			std::cout << "	--no-visualize(-n) :only print result" << std::endl;
			std::cout << "	--convert(-c) :convert brainfuck to kinako-chan " << std::endl;
			std::cout << "	--rev-convert(-r) :convert kinako-chan to brainfuck " << std::endl;
			std::cout << "	--speed=(-s=) :run speed[ms]\n" << std::endl;
			std::cout << "Auter:seigenkousya" << std::endl;
			std::cout << "Repository:https://github.com/seigenkousya/kinako-chan " << std::endl;
			return 0;
		}
		filename=argv[1];
	}else{
		std::cerr << "argument error." << std::endl;
		std::cerr << "usage: ./kinako-chan kinako-chan_script" << std::endl;
		exit(1);
	}

	//get window size
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	row=size.ws_row;
	column=size.ws_col;

	//read file
	std::wifstream file(filename);

	if(!file){
		std::cerr << "failed to open file." << std::endl;
		std::exit(1);
	}

	//get stiring
	std::wstringstream wss;
	wss << file.rdbuf();
	std::wstring source=wss.str();

	if(bftoknk){
		std::cout << "bf to knk" << std::endl;
		bf2knk(source);
		return 0;
	}

	syntax_check(source);
	std::string bf=knk2bf(source);
	
	if(knktobf){
		std::cout << bf << std::endl;
		return 0;
	}

	processor(bf,source);
	std::cout << std::endl;
}
