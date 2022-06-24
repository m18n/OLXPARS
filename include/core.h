#pragma once
#include<stdio.h>
#include<stdlib.h>

#include<string.h>
typedef struct stdarray
{
    void* array;
    int size;
}stdarray;


typedef struct string{
    int(*SearchWord)(struct string* self,const char* search);
    int(*SearchWordIndex)(struct string* self,int startindex,int size,int count,const char* search);
    struct string(*GetStringbyIndex)(struct string* self,int startindex,int length);
    void(*ReversString)(struct string* self);
    struct string(*GetStringSign)(struct string* self,int startindex,char sign);
    struct string(*GetStringSignEnd)(struct string* self,int startindex,int endindex,char sign);
    void(*Show)(struct string*self);
    int(*GetCountWord)(struct string* self,int startindex,const char* word);
    void(*DeleteSymbol)(struct string* self,char symbol);
    void (*SetRefArray)(struct string* self,char* chararray);
    void (*SetConstCharArray)(struct string*self,const char* arr);
    void (*SetCharArray)(struct string* self,char* chararray,int sizebuffer);
    void (*Add)(struct string* self,const char* arr);
    void (*Resize)(struct string* self,int newsize);
    char* chararray;
    int sizearray;
    int length;
}string;
void ResizeString(struct string* self,int newsize);
void AddChar(struct string* self,const char* arr);
void SetRefArray(struct string* self,char* chararray);
void SetConstCharArray(struct string* self,const char* arr);
void CopyCharArray(struct string* self,char* chararray,int sizebuffer);
int SearchWord(string* self,const char* search);
int SearchWordIndex(string* self,int startindex,int size,int count,const char* search);
string GetString(string* self,int startindex,int length);
void ReversString(string* self);
string GetStringSign(string* self,int startindex,char sign);
string GetStringSignEnd(string* self,int startindex,int endindex,char sign);
string* Tok(string str,char sign,int* rsize);
void ShowString(string* self);
void Record(char* arr,int size,const char* namefile);
int GetCountWord(string* self,int startindex,const char* search);
void DeleteSymbol(string* self,char symbol);
char* GetNumberStr(char* url,int startindex);
void SetGETArg(char* url,char* res,const char* arg,const char* newval);
string GetGETArg(string url,string arg);
void Show(char* str,int size);
void CreateString(string* self);
void CreateStringInit(string* self,int sizearray);
void CreateStringCopy(string* self,char* array,int sizebuffer);
void StringMove(string* self,string* two);
void CreateStringCopyConst(string* self,const char* array);
void DeleteString(string* self);
typedef struct time{
    int day;
    int month;
    int year;
    int hourse;
    int minutes;
    int(*GetMinutesBack)(struct time* time);
}coretime_t;
void CreateTime(coretime_t* self);
typedef struct InfoProduct{
    int price;
    string name;
    string descript;
    coretime_t time_create;
    string url;
    void(*Show)(struct InfoProduct* info);
}InfoProduct_t;
void ShowInfoProduct(InfoProduct_t* info);
void CreateInfoProduct(InfoProduct_t* self);