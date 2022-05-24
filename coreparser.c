#include "include/coreparser.h"
int SearchWord(char *arr, int size, const char *search)
{
    int len = strlen(search);

    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            if (arr[j] == search[j - i])
            {
                if (j - i == len - 1)
                {

                    return i;
                }
            }
            else
            {
                i += j - i;
                break;
            }
        }
    }
    return -1;
}
void ReverChar(const char* arr,char* out){
   

    int len=strlen(arr);
    for(int i=0;i<len;i++){
        out[i]=arr[len-i-1];
    }
    out[len]='\0';
    
}
int SearchWordIndex(char *arr, int startindex, int size, int count, const char *search)
{
    int len = strlen(search);
    int c = 0;
    
    if (startindex > size)
    {
        char s[100];
        ReverChar(search,s);
        for (int i = startindex; i >= size; i--)
        {
            for (int j = i; j >= size; j--)
            {
                if (arr[j] == s[i-j])
                {
                    if (i-j == len - 1)
                    {
                        c++;
                        if (c == count)
                            return i;
                    }
                }
                else
                {
                    i -= i-j;
                    break;
                }
            }
        }
    }
    else
    {
        for (int i = startindex; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                if (arr[j] == search[j - i])
                {
                    if (j - i == len - 1)
                    {
                        c++;
                        if (c == count)
                            return i;
                    }
                }
                else
                {
                    i += j - i;
                    break;
                }
            }
        }
        return -1;
    }
}
void Show(char* str,int size){
    char test=str[size];
    str[size]='\0';
    printf("\n%s\n",str);
    str[size]=test;
}
char** Tok(char* str,char sign,int* rsize){
    int tsize=1;
    int sizestr=strlen(str)+1;
    for(int i=0;i<sizestr;i++){
        if(str[i]==sign){
            tsize++;
        }
    }
    int last=0;
    int index=0;
    char** arr=malloc(sizeof(char*)*tsize);
    for(int i=0;i<sizestr;i++){
        if(str[i]==sign||i==sizestr-1){
            int size=i-last;
            char* s=malloc(size+1);
            memcpy(s,&str[last],size);
            s[size]='\0';
            arr[index]=s;
            last=i+1;
            index++;
        }
    }
    *rsize = tsize;

    return arr;
}
char *GetString(char *arr, int startindex, int size)
{
    char *text = (char *)malloc(size);
    memcpy(text, arr + startindex, size);
    return text;
}
char *GetStringSign(char *arr, int sizearr, int startindex, char sign)
{
    int index = 0;
    for (int i = startindex; i < sizearr; i++)
    {
        if (arr[i] == sign)
        {
            index = i;
            break;
        }
    }
    if(arr[index-1]=='l'&&sign=='\"'){
        int a=10;
    
    }
    char* text = NULL;
    if (index != 0) {
        int size = index - startindex;
        text = malloc(size + 1);
        memcpy(text, arr + startindex, size);
        text[size] = '\0';
    }
    return text;
}