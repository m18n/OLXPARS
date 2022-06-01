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
void Record(char* arr,int size,const char* namefile){
    FILE* f;
    f=fopen(namefile,"w");
    if (f == NULL) {
        printf("ERROR RECORD TO FILE\n");
        return;
    }
    printf("SIZE INDEX: %d\n",size);
    arr[size]='\0';
    fprintf(f,"%s",arr);
    fclose(f);
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
void DeleteSpace(char* arr,int size){
    char buffer[100];
    int c=0;
    for(int i=0;i<size;i++){
        if(arr[i]==' '){
            memcpy(buffer,&arr[i+1],size-i);
            memcpy(&arr[i],buffer,size-i);
            c++;
        }
    }
    arr[size-c]='\0';
}
int GetCountWord(char* arr,int startindex,int size,const char* search){
    int len = strlen(search);
    int c = 0;
    for (int i = startindex; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                if (arr[j] == search[j - i])
                {
                    if (j - i == len - 1)
                    {
                        c++;
                    }
                }
                else
                {
                    i += j - i;
                    break;
                }
            }
        }
    return c;
}
char* GetNumberStr(char* url,int startindex){
    int size=strlen(url);
    int end=0;
    for(int i=startindex;i<size;i++){
        if(url[i]>=48&&url[i]<=57){
            end=i+1;
        }else{
            break;
        }
    }
    int strsize=end-startindex;
    char* strnumbers=NULL;
    if(strsize>0){
        strnumbers=malloc(strsize+1);
        memcpy(strnumbers,&url[startindex],strsize);
        strnumbers[strsize]='\0';
    }
    return strnumbers;
}
void SetGETArg(char* url,char* res,const char* arg,const char* newval){
    int sizeurl=strlen(url);
    int sizearg=strlen(arg);
    int sizeval=strlen(newval);
    int indexarg=SearchWordIndex(url,0,sizeurl,1,arg);
    if(indexarg==-1)
        return;
    indexarg+=sizearg;
    int indexend=SearchWordIndex(url,indexarg,sizeurl,1,"&");
    char* urlb=url;
    char ub[400];
    if(url==res){
        strcpy(ub,url);
        urlb=ub;
    }
    memcpy(res,url,indexarg);
    memcpy(&res[indexarg],newval,sizeval);
    if(indexend!=-1){
        memcpy(&res[indexarg+sizeval],&urlb[indexend],sizeurl-indexend);
        res[indexarg+sizeval+sizeurl-indexend]='\0';
    }
}
char* GetGETArg(char* url,const char* arg){
    int sizeurl=strlen(url);
    int sizearg=strlen(arg);
    int indexarg=SearchWordIndex(url,0,sizeurl,1,arg);
    indexarg+=sizearg;
    int end=SearchWordIndex(url,indexarg,sizeurl,1,"&");
    char* arge=NULL;
    if(end!=-1)
        arge=GetString(url,indexarg,end-indexarg);
    else
        arge=GetString(url,indexarg,sizeurl-indexarg);
    return arge;
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
    char *text = (char *)malloc(size+1);
    memcpy(text, arr + startindex, size);
    text[size]='\0';
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