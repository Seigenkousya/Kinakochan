#include "kinako-chan.h"

int x=2;
int y=0;
int ms=50;
int row;
int column;
uint8_t *head;
bool no_visualize=false;

int main(int argc,char *argv[]){
	bool bfmode=true;
	bool knktobf=false;
	bool bftoknk=false;
	char *filename;
	//std::locale::global(std::locale(""));
	std::ios_base::sync_with_stdio(false);
	std::locale::global(std::locale("")); 
	std::wcout.imbue(std::locale(""));

	// check argument
	if(argc==2){
		filename=argv[1];
		if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0){
			std::wcout << L"kinako-chan -Brainfuck interpreter and visualizer-" << std::endl;
			std::wcout << L"Usage: ./kinako-chan -(h|n|s) terget_file " << std::endl;
			std::wcout << L"	--help(-h) :show this help" << std::endl;
			std::wcout << L"	--no-visualize(-n) :only print result" << std::endl;
			std::wcout << L"	--convert(-c) (knk2bf|bf2knk):convert source code." << std::endl;
			std::wcout << L"	--rev-convert(-r) :convert kinako-chan to brainfuck " << std::endl;
			std::wcout << L"	--speed=(-s=) :run speed[ms]\n" << std::endl;
			std::wcout << L"Auter: seigenkousya" << std::endl;
			std::wcout << L"Repository: https://github.com/seigenkousya/kinako-chan " << std::endl;
			return 0;
		}
	}else if(argc==3){
		filename=argv[2];
		if(strcmp(argv[1],"--no-visualize")==0 || strcmp(argv[1],"-n")==0){
			no_visualize=true;
		}else if(strncmp(argv[1],"--speed=",8)==0 || strncmp(argv[1],"-s=",3)==0){
			char *str=argv[1];
			while(*(str++)!='=');
			ms=strtol(str,&str,10);
		}else if(strncmp(argv[1],"--convert",10)==0 || strncmp(argv[1],"-c",2)==0){
			bftoknk=true;
		}else if(strncmp(argv[1],"--brainfuck",12)==0 || strncmp(argv[1],"-b",2)==0){
			bfmode=true;
		}else{
			invalid_argument();
		}
	}else if(argc==4){
		filename=argv[3];
		if(strncmp(argv[1],"--convert",10)==0 || strncmp(argv[1],"-c",2)==0){
			if(strcmp(argv[2],"knk2bf")==0){
				knktobf=true;
			}else if(strcmp(argv[2],"bf2knk")==0){
				bftoknk=true;
			}else{
				invalid_argument();
			}
		}
	}else{
		std::wcerr << L"argument error." << std::endl;
		std::wcerr << L"usage: ./kinako-chan kinako-chan_script" << std::endl;
		std::exit(1);
	}

	// get window size
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);

	row=size.ws_row;
	column=size.ws_col;

	// read file
	std::wifstream file(filename);

	if(!file){
		std::wcerr << L"failed to open file." << std::endl;
		std::exit(1);
	}

	// get stiring
	std::wstringstream wss;
	wss << file.rdbuf();
	std::wstring source=wss.str();

	if(bftoknk){
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
