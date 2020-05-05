#include "kinako-chan.h"

ms=20;
no_visualize=false;

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
