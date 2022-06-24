#include<stdio.h>
#include<stdlib.h>
#include"include/core.h"
#include"include/olxparse.h"
#include"include/olxmanager.h"
// olxdata Menu(){
//     printf("INPUT SEARCH SITE: \n");
//     olxdata in;
//     scanf("%s",in.search);
//     printf("COUNT PRODUCT: ");
//     scanf("%d",&in.count);
//     return in;
// }

// void Read(site* s){
//     FILE* f;
//     f=fopen("test.html","r");
//     fseek(f, 0L, SEEK_END);
//     int size = ftell(f);
//     s->indexrecord=size;
//     fseek(f, 0L, SEEK_SET);
//     fread(s->html,1,size,f);
//     fclose(f);  
// }
int main(){
    system("clear");
    printf("START PARSER OLX\n");
    string str;
    //strcpy(input.search,"https://www.olx.ua/d/list/q-car/?search%5Bfilter_float_price%3Afrom%5D=10&search%5Bfilter_float_price%3Ato%5D=200&page=1");    
    CURL* curl=NULL;
    site s=DownloadSite(&curl,"https://www.olx.ua/d/list/?currency=UAH&search%5Bfilter_float_price:from%5D=100&search%5Bfilter_float_price:to%5D=1000",10000000);
    Record(s.html.chararray,s.indexrecord,"my.html");
    OlxSearchSite_t olx;
    CreateOlxSearchSite(&olx,&s);
    olx.ParseAllProduct(&olx);
    DeleteSite(&s);
    return 0;
}