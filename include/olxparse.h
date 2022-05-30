#pragma once
#include"coreparser.h"
#include"corecurl.h"
typedef struct olxdata
{
    char search[200];
    int count;
}olxdata;
typedef struct timepost
{
    int minutes;
    int day;
}timepost;
typedef struct PSsearch
{
    int price;
    int countview;
    char link[300];
    timepost time;
    float cof;
}PSsearch;

void ShowPSearch(PSsearch* p);
timepost ParseTime(site* s,int* index,int count);
int StrTimeToMin(char* str);
void ProcLink(PSsearch* pr);
int ParsePrice(site* s,int* index,int count);
char* ParseLink(site* s,int* index,int count);
stdarray ParseSearchPage(site* s,const char* url);
void ParseProductPage(site* s,stdarray ps,CURL* curl);
char* ParseId(site* s);
int GetViews(site* s);