#include"Headers.h"
#define line_size 256
#define reset "\033[0m" 
#define green "\033[1;32m" 

bool check(char* pattern , char* line , int start , bool I , bool w)
{
    int j = 0;
    bool dot =0;
    int i;
    for(i = start ; i< start + strlen(pattern);i++)
    {   
        if(pattern[j] == '.')
        {
            if(line[i] == '\n' || line[i] == '\0') return 0;
            dot =1;
            j++;
            continue;
        }
        else if(pattern[j]!= (!I?line[i]: tolower(line[i])))
        {
            return 0;
        }
        j++;
    }
    if(j!= strlen(pattern) && dot && i!= start + strlen(pattern)) return 0;
    if(w)
    {
        int x = strlen(pattern) + start;
        // check left side
        if(start != 0 && ((47<line[start -1] &&line[start -1] < 58) || (64 < line[start -1] && line[start -1]< 91) || (96 < line[start-1]  && line[start -1] < 123))) return 0;
        else if(x < strlen(line)-1 &&((47<line[x] &&line[x] < 58) ||( 64 < line[x] && line[x]< 91 )|| (96 < line[x] &&line[x] < 123))) 
        {
            char u = line[x];
            return 0;
        }
    }
    return 1;
}


char* Unpack(char* input)
{
    int len = strlen(input);
    char *modinput = (char *)malloc(MAX * sizeof(char));
    if ((input[0] == '\'' && input[len - 1] == '\'') ||(input[0] == '\"' && input[len - 1] == '\"'))
    {
        for (int i = 0; i < len - 2; i++)
        {
            modinput[i] = input[i + 1];
        }
        modinput[len - 2] = '\0';
        return modinput;
    }
    else
        return input;
}

void Search(char* pattern , FILE* file , bool I , bool c ,bool n , bool w , int args , char* filer)
{
    char line[line_size];
    int count_line =0;
    int line_num =1;
    while(fgets(line , line_size ,file))
    {
        bool this = 0;
        int x = strlen(line) - strlen(pattern);
        for(int i = 0 ; i< x -1 ; i++)
        {
            if(check(pattern , line , i ,I ,w))
            {
                this =1;
                i = i + strlen(pattern) -1;
                count_line++;
                break;
            }
        }
        if(c) 
        {
            memset(line ,'\0',line_size );
            line_num++;
            continue;
        }
        if(this)
        {
            if(args > 2) printf("%s%s%s%s:%s" , green , filer , reset , cyan , rm);
            if(n) printf("%s%d%s%s:%s" ,  yellow , line_num , rm , cyan , rm);
            for(int i = 0 ; i< strlen(line) -1 ; i++)
            {
                if(check(pattern , line , i ,I ,w))
                {
                    printf("%s" , red);
                    for(int j = i ; j < i + strlen(pattern) ;j++) printf("%c" , line[j]);
                    printf("%s", rm);
                    i = i + strlen(pattern) -1;
                }
                else printf("%c" , line[i]);
            }
        }
        memset(line ,'\0',line_size );
        if(this) printf("\n");
        line_num++;
    }
    if(c && args ==2) printf("%d\n" , count_line);
    else if(c && args > 2) printf("%s%s%s%s:%s%d\n", green , filer , reset , cyan ,rm , count_line);
}


void myGrep(char parsedInput[MAX][MAX] , int args)
{
    bool I = 0,c =0 , n=0 , w =0;
    for(int i = 0 ; i< strlen(parsedInput[1]);i++)
    {
        if(parsedInput[1][i] == 'i') I =1;
        else if(parsedInput[1][i] == 'c') c =1;
        else if(parsedInput[1][i] == 'w') w =1;
        else if(parsedInput[1][i] == 'n') n =1;
        else 
        {
            printf("Invalid flag\n");
            return;
        }
    }
    if(args < 2) 
    {
        printf("Invalid Syntax\n");
        return;
    }
    char pattern[MAX];
    strcpy(pattern , parsedInput[2]);
    char curdir[MAX];
    getcwd(curdir , MAX);
    if(I)  for(int i = 0 ; i< MAX ;i++) pattern[i] =tolower(pattern[i]);
    strcpy(pattern , Unpack(pattern));
    for(int i = 3; i< args + 2 ;i++)
    {
        char filer[MAX];
        memset(filer , '\0' , MAX);
        strcpy(filer , parsedInput[i]);
        split_string searched;
        char filedir[MAX];
        memset(searched.dir_name , '\0' , MAX);
        memset(searched.file_name , '\0' , MAX);
        splitter(&searched , filer);
        FILE* file;
        if(searched.dir_name[0] == '\0') file = fopen(searched.file_name , "r");
        else 
        {
            chdir(searched.dir_name);
            file = fopen(searched.file_name , "r");
        }

        if(file == NULL)
        {
            printf("Invalid file %s\n" , searched.file_name);
            chdir(curdir);
            return;
        }
        Search(pattern, file , I ,c , n ,w, args , filer);  
        getcwd(filedir , MAX);
        fclose(file);
        chdir(curdir);
    }
}