#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"sqlite3.h"
#include"core.h"
#define LINK_S 500
#define PRICE_S 15
void sql_exec(sqlite3* db,const char* sql);
typedef struct olxsearchlink{
    char* link;
    int id;
    int minprice;
    void(*Show)(struct olxsearchlink* self);
    void(*DeleteOnDataBase)(struct olxsearchlink* self);
    sqlite3* db;

}olxsearchlink_t;
void ShowOlxSearchLink(struct olxsearchlink* self);
void DeleteDataBaseOlxSearchLink(struct olxsearchlink* self);
void CreateOlxSearchLink(olxsearchlink_t* olx);
void InitOlxSearchLink(olxsearchlink_t* olx,char* link,int id,sqlite3* db,int minprice);
void DestroyOlxSearchLink(olxsearchlink_t* olx);
typedef struct olxdatabase{
    char namedatabase[50];
    void(*AddSearchLink)(struct olxdatabase* self,char link[LINK_S],char minprice[PRICE_S]);
    stdarray_t(*GetSearchLink)(struct olxdatabase* self,int start,int end,int* size);
    int (*GetCount)(struct olxdatabase* self);
    sqlite3* db;
}olxdatabase_t;

int GetCount(olxdatabase_t* self);
stdarray_t GetSearchLink(struct olxdatabase* self,int start,int end,int* size);
void AddSearchLink(olxdatabase_t* self,char link[LINK_S],char minprice[PRICE_S]);
void CreateOlxDataBase(olxdatabase_t* olx);
void InitDataBase(olxdatabase_t* olx,const char namedatabase[50]);
void DestroyDataBase(olxdatabase_t* olx);