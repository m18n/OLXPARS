#pragma once
#include <curl/curl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"core.h"
typedef struct site
{
    string html;
    int indexrecord;
    string url;
}site;
void CreateSite(site* s,int maxsize);
void DeleteSite(site* s);
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *data);

site DownloadSite(const char* url,int maxsize);
void DownloadSitePtr(site* s,CURL* curl,const char* url);
void DownloadSitePtrPOST(site* s,CURL* curl,const char* url,const char* postfile);
