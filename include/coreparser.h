#pragma once
int SearchWord(char* arr,int size,const char* search);
int SearchWordIndex(char* arr,int startindex,int size,int count,const char* search);
char* GetString(char* arr,int startindex,int size);
void ReverChar(const char* arr,char* out);
char* GetStringSign(char* arr,int sizearr,int startindex,char sign);
char** Tok(char* str,char sign);
void Show(char* str,int size);