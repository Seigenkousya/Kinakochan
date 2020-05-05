#include "kinako-chan.h"

void invalid_argument(){
	std::wcerr << L"Invalid argument." << std::endl;
	std::wcerr << L"Usage: ./kinako-chan -(h|n|s) terget_file" << std::endl;
	std::wcerr << L"	--help(-h) :show this help" << std::endl;
	std::wcerr << L"	--no-visualize(-n) :only print result" << std::endl;
	std::wcout << L"	--convert(-c) :convert brainfuck to kinako-chan L" << std::endl;
	std::wcout << L"	--rev-convert(-r) :convert kinako-chan to brainfuck L" << std::endl;
	std::wcerr << L"	--speed=(-s=) :run speed[ms]\n" << std::endl;
	exit(1);
}

void bf2knk(std::wstring bf){
	int index=0;

	//std::wcout << L"--brainfuck code--" << std::endl;
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
			bf.append(L",");
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
