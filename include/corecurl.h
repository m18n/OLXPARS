#pragma once
#include <curl/curl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct site
{
    char* html;
    int indexrecord;
    int size;
}site;
void CreateSite(site* s,int maxsize);
void DeleteSite(site* s);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *data);

site GetSite(CURL* curl,const char* url,int sizebuffer);
void SetSite(site* s,CURL* curl,const char* url);
void SetSitePost(site* s,CURL* curl,const char* url);