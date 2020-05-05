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
		std::wcerr << L"now:" << now << L" head:" << head << std::endl;
		std::wcerr << L"now-head:" << (int)(now-head) << std::endl;
		std::wcerr << L"point out of range." << std::endl;
		std::exit(1);
	}
}

void create_flame(){
	int i;

	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"#";
	for(i=1;i<column-30;i++)
		std::wcout << L"=";

	std::wcout << L"#" << std::endl;
}
	
bool is_token(char c){
	int i;
	char tokens[]="><+-,.[]";
	for(i=0;i<8;i++){
		if(tokens[i]==c) return true;
	}
	return false;
}

void display_knk(std::wstring knk,int now){
	int index;
	int line_number;
	int counter=0;
	int knk_xsize=(column-33)/(12*2);
	int knk_ysize=row-14-2;
	int flamesize=knk_xsize*knk_ysize;
	static int start=0;
	static int line_start=1;

	index=start;
	line_number=line_start;

	//show source
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"kinako-chan code\n" << std::endl;
	create_flame();

	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << std::setw(2) << line_number << ": "<< std::flush;
	std::wcout << L"\033["<< x << L";" << y+5 << L"H" << std::flush;
	line_number++;

	while(counter<flamesize){
		if(index<knk.size()){
			if(index == now*12){
				std::wcout << L"\033[42m" << std::flush;
				std::wcout << knk.substr(index,12);
				std::wcout << L"\033[49m" << std::flush;
			}else{
				std::wcout << knk.substr(index,12);
			}

			if(((counter+1) %knk_xsize)==0 && counter+1 != flamesize){
				std::wcout << std::endl;
				std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
				std::wcout << std::setw(2) << line_number << ": " << std::flush;
				std::wcout << L"\033["<< x << L";" << y+5 << L"H" << std::flush;
				line_number++;
			}

			index+=12;
			counter++;
		}else{
			std::wcout << L"\033[0K" << std::flush;
			index++;
			break;
		}
	}

	create_flame();
	
	//scroll
	if((knk.size()/12)>flamesize && now==(start/12)+flamesize-(knk_xsize*2)-1){
		start+=(knk_xsize)*12;
		line_start++;
	}

}

void display_bf(std::wstring code,int now,char *output){
	int index=0;

	//show bf code
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"brainfuck code\n" << std::endl;
	create_flame();
	std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;

	while(index<code.size()){
		if(is_token(code[index])){
			if(index==now){
				std::wcout << L"\033[46m" << std::flush;
				std::wcout << code[index];
				std::wcout << L"\033[49m" << std::flush;
			}else{
				std::wcout << code[index];
			}

			if((index+1)%(column-33)==0){
				std::wcout << std::endl;
				std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;
			}
		}
		index++;

	}
	create_flame();
	
	//show output
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"output: " << output << std::endl;

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
	std::wcout << L"\033["<< x << L";" << y+2 << L"H" << std::flush;
	for(i=index_start;i<(index_start+box_num);i++){
		std::wcout << L"+" << std::setw(3) << i;
	}
	std::wcout << L"+" << std::endl;
	
	
	pointer_start=head+sizeof(uint8_t*)*index_start;
	std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;
	for(pointer=pointer_start; pointer<(pointer_start+box_num); pointer++){
		std::wcout << L"|" << std::setw(3) << unsigned(*(pointer));
	}
	std::wcout << L"|" << std::endl;
	
	std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;
	for(i=0;i<box_num;i++){
		std::wcout << L"+---";
	}
	std::wcout << L"+" << std::endl;
	
	//show pointer
	std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;
	for(i=0;i<address-index_start;i++){
		std::wcout << L"    ";
	}
	std::wcout << L"  ^" << std::endl;
}

void processor(std::wstring bf,std::wstring kinako){
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
				std::wcout << output[len_out];
				len_out++;
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
			display_knk(kinako,index);
			display_bf(bf,index,output);
		}

		index++;

		if(!no_visualize)
			usleep(ms);
	}
}

void bf2knk(std::wstring bf){
	int index=0;

	std::wcout << L"--brainfuck code--" << std::endl;
	while(index!=bf.size()){
		switch(bf[index]){
			case '+':
				std::wcout << L"黄奈子ちゃん黄奈子ちゃん";
				break;
			case '-':
				std::wcout << L"黄奈子ちゃん黃奈子ちゃん";
				break;
			case '>':
				std::wcout << L"黃奈子ちゃん黄奈子ちゃん";
				break;
			case '<':
				std::wcout << L"黃奈子ちゃん黃奈子ちゃん";
				break;
			case '.':
				std::wcout << L"黃奈子ちゃん黄奈孑ちゃん";
				break;
			case ',':
				std::wcout << L"黃奈子ちゃん黃奈孑ちゃん";
				break;
			case '[':
				std::wcout << L"黄奈子ちゃん黄奈孑ちゃん";
				break;
			case ']':
				std::wcout << L"黄奈孑ちゃん黄奈子ちゃん";
				break;
		}
		index++;
	}
	std::wcout << std::endl;
}

std::wstring knk2bf(std::wstring kinako){
	int index=0;
	std::wstring bf=L"";
	while(index!=kinako.size()){
		if(kinako.compare(index,12,L"黄奈子ちゃん黄奈子ちゃん")==0){
			bf.append(L"+");
		}else if(kinako.compare(index,12,L"黄奈子ちゃん黃奈子ちゃん")==0){
			bf.append(L"-");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黄奈子ちゃん")==0){
			bf.append(L">");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黃奈子ちゃん")==0){
			bf.append(L"<");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黄奈孑ちゃん")==0){
			bf.append(L".");
		}else if(kinako.compare(index,12,L"黃奈子ちゃん黃奈孑ちゃん")==0){
			bf.append(L",L");
		}else if(kinako.compare(index,12,L"黄奈子ちゃん黄奈孑ちゃん")==0){
			bf.append(L"[");
		}else if(kinako.compare(index,12,L"黄奈孑ちゃん黄奈子ちゃん")==0){
			bf.append(L"]");
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
		std::wcerr << L"undefined token." << std::endl;
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
			std::wcerr << L"Invalid argument." << std::endl;
			std::wcerr << L"Usage: ./kinako-chan -(h|n|s) terget_file" << std::endl;
			std::wcerr << L"	--help(-h) :show this help" << std::endl;
			std::wcerr << L"	--no-visualize(-n) :only print result" << std::endl;
			std::wcout << L"	--convert(-c) :convert brainfuck to kinako-chan L" << std::endl;
			std::wcout << L"	--rev-convert(-r) :convert kinako-chan to brainfuck L" << std::endl;
			std::wcerr << L"	--speed=(-s=) :run speed[ms]\n" << std::endl;
			exit(1);
		}
	}else if(argc==2){
		if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0){
			std::wcout << L"kinako-chan -Brainfuck interpreter and visualizer-" << std::endl;
			std::wcout << L"Usage: ./kinako-chan -(h|n|s) terget_file " << std::endl;
			std::wcout << L"	--help(-h) :show this help" << std::endl;
			std::wcout << L"	--no-visualize(-n) :only print result" << std::endl;
			std::wcout << L"	--convert(-c) :convert brainfuck to kinako-chan " << std::endl;
			std::wcout << L"	--rev-convert(-r) :convert kinako-chan to brainfuck " << std::endl;
			std::wcout << L"	--speed=(-s=) :run speed[ms]\n" << std::endl;
			std::wcout << L"Auter:seigenkousya" << std::endl;
			std::wcout << L"Repository:https://github.com/seigenkousya/kinako-chan " << std::endl;
			return 0;
		}
		filename=argv[1];
	}else{
		std::wcerr << L"argument error." << std::endl;
		std::wcerr << L"usage: ./kinako-chan kinako-chan_script" << std::endl;
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
		std::wcerr << L"failed to open file." << std::endl;
		std::exit(1);
	}

	//get stiring
	std::wstringstream wss;
	wss << file.rdbuf();
	std::wstring source=wss.str();

	if(bftoknk){
		std::wcout << L"bf to knk" << std::endl;
		bf2knk(source);
		return 0;
	}

	syntax_check(source);
	std::wstring bf=knk2bf(source);
	
	if(knktobf){
		std::wcout << bf << std::endl;
		return 0;
	}

	processor(bf,source);
	std::wcout << std::endl;
}
