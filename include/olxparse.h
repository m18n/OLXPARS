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
    char link[200];
    timepost time;
}PSsearch;


timepost ParseTime(site* s,int* index,int count);
int StrTimeToMin(char* str);
void ProcLink(PSsearch* pr);
int ParsePrice(site* s,int* index,int count);
char* ParseLink(site* s,int* index,int count);
stdarray ParseSearchPage(site* s,olxdata data);
void ParseProductPage(site* s,stdarray ps,CURL* curl);
int ParseViews(site* s);