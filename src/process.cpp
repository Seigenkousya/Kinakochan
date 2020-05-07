#include "kinako-chan.h"

void within_range(uint8_t *now){
	if(now-head<0 || now>head+MEMORY_SIZE){
		std::wcerr << L"now:" << now << L" head:" << head << std::endl;
		std::wcerr << L"now-head:" << (int)(now-head) << std::endl;
		std::wcerr << L"point out of range." << std::endl;
		std::exit(1);
	}
}
	
bool is_token(char c){
	int i;
	char tokens[]="><+-,.[]";
	for(i=0;i<8;i++){
		if(tokens[i]==c) return true;
	}
	return false;
}

void processor(std::wstring bf,std::wstring kinako){
	char output[10000];
	int nest=0;
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
				if(no_visualize) std::wcout << output[len_out];
				len_out++;
				break;
			case ',':
				std::cin >> *memory;
				break;
			case '[':
				nest=1;
				if(*memory==0){
					while(bf[index]!=']' || nest!=0){
						index++;
						if(bf[index]=='[') nest++;
						if(bf[index]==']') nest--;
					}
				}
				break;
			case ']':
				nest=1;
				if(*memory!=0){
					while(bf[index]!='[' || nest!=0){
						index--;
						if(bf[index]=='[') nest--;
						if(bf[index]==']') nest++;
					}
				}
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
