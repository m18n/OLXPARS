#include<stdio.h>
#include<stdlib.h>
#include"include/corecurl.h"
#include"include/olxparse.h"

olxdata Menu(){
    printf("INPUT SEARCH SITE: \n");
    olxdata in;
    scanf("%s",in.search);
    printf("COUNT PRODUCT: ");
    scanf("%d",&in.count);
    return in;
}
void Record(char* arr,int size){
    FILE* f;
    f=fopen("test.html","w");
    fprintf(f,"%s",arr);
    fclose(f);
}
void Read(site* s){
    FILE* f;
    f=fopen("test.html","r");
    fseek(f, 0L, SEEK_END);
    int size = ftell(f);
    s->indexrecord=size;
    fseek(f, 0L, SEEK_SET);
    fread(s->html,1,size,f);
    fclose(f);  
}
int main(){
    system("clear");
    printf("START PARSER OLX\n");
    olxdata input;
    strcpy(input.search,"https://www.olx.ua/d/elektronika/q-%D0%B7%D0%B0%D0%B6%D0%B8%D0%B3%D0%B0%D0%BB%D0%BA%D0%B0/?currency=UAH&search%5Bfilter_float_price:from%5D=50&search%5Bfilter_float_price:to%5D=400");
    //strcpy(input.search,"https://www.olx.ua/d/elektronika/telefony-i-aksesuary/mobilnye-telefony-smartfony/q-%D1%82%D0%B5%D0%BB%D0%B5%D1%84%D0%BE%D0%BD/");
    input.count=50;
    //printf("OKEY START PARSE COUNT: %d SITE: %s\n",input.count,input.search);
    CURL* curl=NULL;
    // site s;
    // CreateSite(&s,1000000000);
    //Read(&s);
   
    site s=GetSite(curl,input.search,100000000);
    //printf("HTML:\n%s\n",s.html);
    //Record(s.html,s.indexrecord);
   // stdarray ar=ParseSearchPage(&s,input);
    //ParseProductPage(&s,ar,curl);
    SetSitePost(&s,curl,"https://www.olx.ua/api/v1/offers/745060221/page-views");
    //printf("\n%s\n",s.html);
    Show(s.html,200);
    int index=0;
  //  ParseViews(&s);

    Record(s.html,s.indexrecord);
    DeleteSite(&s);
    return 0;
}