#include"Headers.h"


char* checkMultiWordFolder(char* input)
{
    strcpy(input , lstrip(input));
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

void changeDirectory(char parsedInput[MAX][MAX] , int args , char input[MAX] )
{
    char newdir[MAX];
    memset(newdir , '\0' , MAX);
    for(int i = 0 ;  i< MAX- 8 ;i++)
    {
        newdir[i] = input[i+8];
    }
    strcpy(newdir, checkMultiWordFolder(newdir));
    if(chdir(newdir) == -1)
    printf("Invalid Directory\n");
}