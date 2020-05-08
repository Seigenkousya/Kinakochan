#include "kinako-chan.h"

void create_flame(){
	int i;

	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"#";
	for(i=1;i<column-30;i++)
		std::wcout << L"=";

	std::wcout << L"#" << std::endl;
}

void display_knk(std::wstring knk,int now_word){
	static int start=0;
	static int line_start=1;
	int index;
	int counter=0;
	int line_number;
	int start_word=start/12;
	int knk_xsize=(column-33)/(12*2);
	int knk_ysize=row-14-2;
	int flamesize=knk_xsize*knk_ysize;

	//scroll jump up 
	if((knk.size()/12)>flamesize && now_word<start_word){
		start-=(knk_xsize)*12*((start_word-now_word)/knk_xsize+1);
		line_start-=(start_word-now_word)/knk_xsize+1;
	}

	//scroll jump down 
	if((knk.size()/12)>flamesize && (start_word+flamesize-1)<now_word){
		start+=(knk_xsize)*12*((now_word-(start_word+flamesize-1))/knk_xsize+1);
		line_start+=(now_word-(start_word+flamesize-1))/knk_xsize+1;
	}

	// set value
	index=start;
	line_number=line_start;

	//show source
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"kinako-chan code\n" << std::endl;
	create_flame();

	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << std::setw(2) << line_number << ": " << std::flush;
	std::wcout << L"\033["<< x << L";" << y+5 << L"H" << std::flush;
	line_number++;

	while(counter<flamesize){
		if(index<knk.size()){
			if(index == now_word*12){
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
	
	//scroll down
	if((knk.size()/12)>flamesize && now_word==start_word+flamesize-(knk_xsize*2)-1){
		start+=(knk_xsize)*12;
		line_start++;
	}

}

void display_bf(std::wstring code,int now_char,char *output){
	int index;
	int counter=0;
	int bf_xsize=(column-33);
	int bf_ysize=3;
	int flamesize=bf_xsize*bf_ysize;
	static int start=0;

	// show bf code
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"brainfuck code\n" << std::endl;
	create_flame();
	std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;

	//scroll jump up 
	if(now_char<start){
		start-=bf_xsize*((start-now_char)/bf_xsize+1);
	}

	//scroll jump up 
	if((start+flamesize-1)<now_char){
		start+=bf_xsize*((now_char-(start+flamesize-1))/bf_xsize+1);
	}

	index=start;
	while(counter<flamesize){
		if(index<code.size()){
			if(index==now_char){
				std::wcout << L"\033[46m" << std::flush;
				std::wcout << code[index];
				std::wcout << L"\033[49m" << std::flush;
			}else{
				std::wcout << code[index];
			}

			if((index+1)%(column-33)==0 && counter+1 != flamesize){
				//std::wcout << std::flush;
				std::wcout << L"\033["<< ++x << L";" << y+2 << L"H" << std::flush;
			}
		}
		index++;
		counter++;
	}
	create_flame();
	
	//show output
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"\033["<< ++x << L";" << y << L"H" << std::flush;
	std::wcout << L"output: " << output << std::flush;

	//scroll
	if(now_char==start+flamesize-1){
		start+=bf_xsize;
	}
}

void display_array(uint8_t *memory,char *output){
	int i;
	int address=memory-head;
	int box_num=(column-4)/5;
	uint8_t *pointer;
	uint8_t *pointer_start;
	static int index_start=0;

	x=1;
	y=2;

	//std::system("clear");
	std::wcout << L"\033[2J" << std::flush;
	//fflush(stdout);

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
