#include"Headers.h"



char user[MAX];
char dir[MAX];
char hostname[MAX];
char helpadd[MAX];
char prompt[MAX];   
int args = 0;

void getAddress()
{
    getcwd(dir, MAX);
    getlogin_r(user, MAX);
    gethostname(hostname, MAX);
    strcat(prompt, red);
    strcat(prompt, user);
    strcat(prompt, "@");
    strcat(prompt, hostname);
    strcat(prompt, ":");
    strcat(prompt, cyan);
    strcat(prompt, dir);
    strcat(prompt, "$");
    strcat(prompt, rmcolor);
}

char* lstrip(char* input)
{
    char *modInput = (char *)malloc(MAX * sizeof(char));
    bool isInitialSpace = 0;
    int j = 0;
    for (int i = 0; i < MAX; i++)
    {
        if (input[i] != ' ' && !isInitialSpace)
        {
            isInitialSpace = 1;
            modInput[j] = input[i];
            j++;
        }
        else if (isInitialSpace)
        {
            modInput[j] = input[i];
            j++;
        }
    }
    return modInput;

}

void Parse(char * input , char parsedInput[MAX][MAX])
{
    int z =0;
    bool switc =0;
    bool command =1;
    int flag = 0;
    for(int i = 0 ; i < strlen(input); i++)
    {
        if(command && input[i]!= ' ')
        {
            parsedInput[0][z] = input[i];
            z++;
        }
        else if(input[i] == ' ')
        {
            command = 0;
            switc =1;
            z = 0;
        }
        else if(switc == 1 && input[i] == '-')
        {
            i++;
            while(input[i]!=' ' && i < strlen(input))
            {
                parsedInput[1][flag] = input[i];
                flag++;
                i++;
            }
        }
        else if(switc == 1 && input[i] != '-')
        {
            while(input[i]!= ' ' && i < strlen(input))
            {
                parsedInput[args+2][z] = input[i];
                i++;
                z++;
            }
            parsedInput[args+2][z] = '\0';
            z=0;
            args++;
        }
    }

    lstrip(parsedInput[0]);
}


int main()
{
    memset(helpadd , '\0' , MAX);
    getcwd(helpadd , MAX);
    while(1)
    {
        prompt[0] = '\0';
        getAddress();
        args = 0;
        char parsedInput[MAX][MAX];
        char input[MAX];
        for(int i = 0 ; i< MAX ;i++)
        {
            input[i] = '\0';
            for(int j = 0 ; j<MAX ;j++)
            {
                parsedInput[i][j] = '\0';
            }
            
        }
        strcpy(input , readline(prompt));
        strcpy(input , lstrip(input));
        Parse(input , parsedInput);
        getcwd(parsedInput[args+2] , MAX);
        if(strlen(input) != 0)
        add_history(input);
        if(!strcmp(parsedInput[0] , "chngdir"))
        {
            if(args ==0)chdir(getenv("HOME"));
            else  changeDirectory(parsedInput , args, input);
        }
        else if(!strcmp(parsedInput[0], "exit")) 
        {
            if(args> 0 || parsedInput[1][0] != '\0')
            {
                printf("Invalid syntax \nPlease check help exit\n");
                continue;
            }
            printf("Exiting...\n");
            break;
        }
        else if(!strcmp(parsedInput[0] , "list") ) 
        {
            list(dir , parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "copy") || !strcmp(parsedInput[0] , "move"))
        {
            CpMv(parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "process"))
        {
            if(args!= 0)
            {
                printf("Invalid Syntax for process\nPlease check help\n");
                continue;
            }
            myPS(parsedInput[1]);
        }
        else if(!strcmp(parsedInput[0] , "search"))
        {
            myGrep(parsedInput , args);
        }
        else if(!strcmp(parsedInput[0] , "help"))
        {
            if(parsedInput[1][0] != '\0')
            {
                printf("Please try help [command-name]\n");
                continue;
            }
            else if(args > 1)
            {
                printf("Please try help [command-name]\n");
                continue;
            }

            help(args , parsedInput , helpadd);
        }
        else printf("Invalid Command\n");
    }
    return 0;
}