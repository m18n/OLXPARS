#pragma once
#include"olxparse.h"
void ParseOlxPages(CURL* curl,const char* url){
    int sizeurl=strlen(url);
    site s=GetSite(curl,url,10000000);
    stdarray products=ParseSearchPage(&s,input);
    ParseProductPage(&s,products,curl);
}