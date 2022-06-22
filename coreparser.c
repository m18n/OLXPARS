#include "include/coreparser.h"
int SearchWord(string* self,const char* search)
{
    int len = strlen(search);

    for (int i = 0; i < self->length; i++)
    {
        for (int j = i; j < self->length; j++)
        {
            if (self->chararray[j] == search[j - i])
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
void ReversString(string* self){
   

    
    
    for(int i=0;i<self->length/2;i++){
        self->chararray[i]=self->chararray[self->length-i];
    }
    
    
}
int SearchWordIndex(string* self,int startindex,int size,int count,const char* search)
{
    int len = strlen(search);
    int c = 0;
    
    if (startindex > size)
    {
        char s[100];
        string revers;
        CreateStringCopy(&revers,search,len);
        revers.ReversString(&revers);
        for (int i = startindex; i >= size; i--)
        {
            for (int j = i; j >= size; j--)
            {
                if (self->chararray[j] == s[i-j])
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
                if (self->chararray[j] == search[j - i])
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
void DeleteSymbol(string* self,char symbol){
    char buffer[100];
    int c=0;
    for(int i=0;i<self->length;i++){
        if(self->chararray[i]==symbol){
            memcpy(buffer,&self->chararray[i+1],self->length-i);
            memcpy(&self->chararray[i],buffer,self->length-i);
            c++;
        }
    }
    self->chararray[self->length-c]='\0';
}

int GetCountWord(string* self,int startindex,const char* search){
    int len = strlen(search);
    int c = 0;
    for (int i = startindex; i < self->length; i++)
        {
            for (int j = i; j <self->length; j++)
            {
                if (self->chararray[j] == search[j - i])
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
string GetGETArg(string url,string arg){
    
    int indexarg=url.SearchWordIndex(&url,0,url.length,1,arg.chararray);
    indexarg+=arg.length;
    int end=url.SearchWordIndex(&url,indexarg,url.length,1,"&");
    string arge;
    if(end!=-1)
        arge=url.GetStringbyIndex(&url,indexarg,end-indexarg);
    else
        arge=url.GetStringbyIndex(&url,indexarg,url.length-indexarg);
    return arge;
}
void Show(char* str,int size){
    char test=str[size];
    str[size]='\0';
    printf("\n%s\n",str);
    str[size]=test;
}
void ShowString(string* self){
    printf("%s SIZE: %d",self->chararray,self->sizearray);
}
string* Tok(string str,char sign,int* rsize){
    int tsize=1;
    
    for(int i=0;i<str.length;i++){
        if(str.chararray[i]==sign){
            tsize++;
        }
    }
    int last=0;
    int index=0;
    string* arr=malloc(sizeof(string)*tsize);
    for(int i=0;i<str.length;i++){
        if(str.chararray[i]==sign||i==str.length-1){
            int size=i-last;
            string s;
            CreateStringInit(&s,size+1);
            memcpy(s.chararray,&str.chararray[last],size);
            s.chararray[size]='\0';
            s.length=size;
            arr[index]=s;
            last=i+1;
            index++;
        }
    }
    *rsize = tsize;

    return arr;
}
string GetString(string* self,int startindex,int length)
{
    char *text = (char *)malloc(length+1);
    memcpy(text, self->chararray + startindex, length);
    text[length]='\0';
    string str;
    CreateString(&str);
    str.SetCharArray(&str,text);
    return str;
}
string GetStringSign(string* self,int startindex,char sign)
{
    int index = 0;
    for (int i = startindex; i < self->length; i++)
    {
        if (self->chararray[i] == sign)
        {
            index = i;
            break;
        }
    }
    if(self->chararray[index-1]=='l'&&sign=='\"'){
        int a=10;
    
    }
    char* text = NULL;
    int size=0;
    if (index != 0) {
        size = index - startindex;
        text = malloc(size + 1);
        memcpy(text, self->chararray + startindex, size);
        text[size] = '\0';
    }
    string str;
    CreateString(&str);
    str.SetCharArray(&str,text);
    return str;
}
string GetStringSignEnd(string* self,int startindex,int endindex,char sign){
    int index = 0;
    for (int i = startindex; i < endindex; i++)
    {
        if (self->chararray[i] == sign)
        {
            index = i;
            break;
        }
    }
    if(self->chararray[index-1]=='l'&&sign=='\"'){
        int a=10;
    
    }
    char* text = NULL;
    int size=0;
    if (index != 0) {
        size = index - startindex;
        text = malloc(size + 1);
        memcpy(text, self->chararray + startindex, size);
        text[size] = '\0';
    }
    string str;
    CreateString(&str);
    str.SetCharArray(&str,text);
    return str;
}
void SetCharArray(struct string* self,char* chararray){
    self->chararray=chararray;
    self->sizearray=strlen(chararray);
    self->length=self->sizearray;
}
void SetConstCharArray(struct string* self,const char* arr){
    int length=strlen(arr);
    self->chararray=malloc(length);
    self->sizearray=length;
    self->length=length;
    memcpy(self->chararray,arr,length);
}
void AddChar(struct string* self,const char* arr){
    int length=strlen(arr);
    int clearmemory=self->sizearray-self->length;
    if(clearmemory>=length){
        memcpy(&self->chararray[self->length],arr,length);
        self->length+=length;
    }else{
        int size=self->sizearray+(length-clearmemory);
        char* newstr=malloc(size);
        memcpy(newstr,self->chararray,self->length);
        memcpy(&newstr[self->length],arr,length);
        free(self->chararray);
        self->chararray=newstr;
        self->length=size;
        self->sizearray=size;
    }
    
}
void ResizeString(struct string* self,int newsize){
    if(self->sizearray>=newsize){
        self->chararray[newsize]='\0';
        self->length=newsize;
    }else{
        char* newstr=malloc(newsize);
        memcpy(newstr,self->chararray,self->length);
        free(self->chararray);
        self->chararray=newstr;
        self->sizearray=newsize;
    }
}
void CopyCharArray(struct string* self,char* chararray,int sizebuffer){
    if(self->sizearray>=sizebuffer){
        memcpy(self->chararray,chararray,sizebuffer);
        self->length=strlen(chararray);
    }else{
        if(self->sizearray!=0)
            free(self->chararray);
        self->chararray=malloc(sizebuffer);
        memcpy(self->chararray,chararray,sizebuffer);
        self->length=strlen(chararray);
    }
}
void CreateString(string* self){
    self->chararray=NULL;
    self->sizearray=0;
    self->SearchWord=SearchWord;
    self->SearchWordIndex=SearchWordIndex;
    self->GetStringbyIndex=GetString;
    self->ReversString=ReversString;
    self->GetStringSign=GetStringSign;
    self->GetStringSignEnd=GetStringSignEnd;
    self->Show=ShowString;
    self->GetCountWord=GetCountWord;
    self->DeleteSymbol=DeleteSymbol;
    self->CopyCharArray=CopyCharArray;
    self->SetCharArray=SetCharArray;
    self->SetConstCharArray=SetConstCharArray;
    self->Add=AddChar;
    self->Resize=ResizeString;
}
void StringMove(string* self,string* two){
    *self=*two;
    two->chararray=NULL;
    two->length=0;
    two->sizearray=0;
}
void CreateStringInit(string* self,int sizearray){
    CreateString(self);
    self->chararray=malloc(sizearray);
}
void CreateStringCopy(string* self,char* array,int sizebuffer){
    CreateString(self);
    self->CopyCharArray(self,array,sizebuffer);
}
void CreateStringCopyConst(string* self,const char* array){
    CreateString(self);
    self->CopyCharArray(self,array,strlen(array));
}
void DeleteString(string* self){
    free(self->chararray);
}
