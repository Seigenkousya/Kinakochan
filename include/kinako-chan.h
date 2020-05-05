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
int ms;
int column;
uint8_t *head;
bool no_visualize;

// code_check
void bf2knk(std::wstring bf);
std::wstring knk2bf(std::wstring kinako);
void syntax_check(std::wstring& source);

// display
void create_flame();
void display_knk(std::wstring knk,int now);
void display_bf(std::wstring code,int now,char *output);
void display_array(uint8_t *memory,char *output);

// process
void within_range(uint8_t *now);
bool is_token(char c);
void processor(std::wstring bf,std::wstring kinako);
