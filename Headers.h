#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<fcntl.h>
#include<time.h>
#define MAX 256
#define cyan "\001\e[01;36m\002"
#define red "\001\e[01;31m\002"
#define rmcolor "\001\e[0m\002 "
#define rm "\001\e[0m\002"
#define yellow "\001\e[00;33m\002"

void changeDirectory(char parsedInput[MAX][MAX] , int args , char input[MAX]);
int list( char* dir , char parsedInput[MAX][MAX] , int args);
void CpMv(char parsedInput[MAX][MAX] , int args);
void myPS(char flags[MAX]);

struct split_string
{
    char file_name[MAX];
    char dir_name[MAX];
};


typedef struct split_string split_string;

void splitter(split_string* path , char * name );
void myGrep(char parsedInput[MAX][MAX] , int args);
void help(int args , char parsedInput[MAX][MAX] , char help[MAX]);

char* lstrip(char* input);
