#pragma once
#include"olxparse.h"

void ParseOlxPages(CURL* curl,const char* url){
    int sizeurl=strlen(url);
    site s=GetSite(curl,url,10000000);
    
    char urlf[400];
    strcpy(urlf,url);
    int min=10;
    int max=11;
    int pages=1;
    while (pages!=0)
    {
        SetPage(urlf,1);
        NewMinPrice(urlf,min);
        NewMaxPrice(urlf,max);
        SetSite(&s,curl,urlf);
        pages=GetCountPage(&s);
        printf("\nURL: %s\n\n",urlf);
        for(int i=0;i<pages;i++){
            printf("\nURL: %s\n\n",urlf);
            SetSite(&s,curl,urlf);
            stdarray products=ParseSearchPage(&s,urlf);
            ParseProductPage(&s,products,curl);
            
            free(products.array);
            NextPage(urlf,urlf);
           
        }
        min++;
        max++;
    }
    
        
    
}