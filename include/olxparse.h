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
    string link;
    timepost time;
    float cof;
}PSsearch;

void ShowPSearch(PSsearch* p);
timepost ParseTime(site* s,int* index,int count);
int StrTimeToMin(string str);
void ProcLink(PSsearch* pr);
int ParsePrice(site* s,int* index,int count);
string ParseLink(site* s,int* index,int count);
stdarray ParseSearchPage(site* s,const char* url);
void ParseProductPage(site* s,stdarray ps,CURL* curl);
string ParseId(site* s);
int GetViews(site* s);
int GetCountPage(site* s);
void NextPage(char* url,char* result);
void NewMaxPrice(char* url,int price);
void NewMinPrice(char* url,int price);
int GetPage(char* url);
void SetPage(char* url,int page);