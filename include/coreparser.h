#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct stdarray
{
    void* array;
    int size;
}stdarray;
int SearchWord(char* arr,int size,const char* search);
int SearchWordIndex(char* arr,int startindex,int size,int count,const char* search);
char* GetString(char* arr,int startindex,int size);
void ReverChar(const char* arr,char* out);
char* GetStringSign(char* arr,int sizearr,int startindex,char sign);
char** Tok(char* str,char sign,int* rsize);
void Show(char* str,int size);
void Record(char* arr,int size,const char* namefile);
int GetCountWord(char* arr,int startindex,int size,const char* search);
void DeleteSpace(char* arr,int size);