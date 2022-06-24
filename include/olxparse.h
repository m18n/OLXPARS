#pragma once
#include"core.h"
#include"corecurl.h"
typedef struct IParseInfoProduct{
    void(*ParsePrice)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    void(*ParseNameProduct)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    void(*ParseDescript)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    void(*ParseTime)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    void(*ParseLink)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    void(*ParseProduct)(struct IParseInfoProduct* self,InfoProduct_t * info,site* s);
    int start;
    int end;
}IParseInfoProduct_t;
void ParseProduct(IParseInfoProduct_t* self,InfoProduct_t* info,site* s);
void CreateIParseInfoProduct(IParseInfoProduct_t* iparse);
typedef struct OlxSearchSite{
    IParseInfoProduct_t iparse;
    stdarray(*ParseAllProduct)(struct OlxSearchSite* olx);
    site* site;
}OlxSearchSite_t;
void ParseSearchLink(IParseInfoProduct_t* self,InfoProduct_t* info,site* s);
void ParseSearchPrice(IParseInfoProduct_t* self,InfoProduct_t* info,site* s);
stdarray ParseAllProduct(OlxSearchSite_t* olx);
void CreateOlxSearchSite(OlxSearchSite_t* olx,site* site);
// typedef struct olxdata
// {
//     char search[200];
//     int count;
// }olxdata;
// typedef struct timepost
// {
//     int minutes;
//     int day;
// }timepost;
// typedef struct PSsearch
// {
//     int price;
//     int countview;
//     string link;
//     timepost time;
//     float cof;
// }PSsearch;

// void ShowPSearch(PSsearch* p);
// timepost ParseTime(site* s,int* index,int count);
// int StrTimeToMin(string str);
// void ProcLink(PSsearch* pr);
// int ParsePrice(site* s,int* index,int count);
// string ParseLink(site* s,int* index,int count);
// stdarray ParseSearchPage(site* s,const char* url);
// void ParseProductPage(site* s,stdarray ps,CURL* curl);
// string ParseId(site* s);
// int GetViews(site* s);
// int GetCountPage(site* s);
// void NextPage(char* url,char* result);
// void NewMaxPrice(char* url,int price);
// void NewMinPrice(char* url,int price);
// int GetPage(char* url);
// void SetPage(char* url,int page);