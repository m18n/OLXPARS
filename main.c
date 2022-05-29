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
    strcpy(input.search,"https://www.olx.ua/d/detskiy-mir/?currency=UAH&search%5Bfilter_enum_state%5D%5B0%5D=new");
    //strcpy(input.search,"https://www.olx.ua/d/elektronika/telefony-i-aksesuary/mobilnye-telefony-smartfony/q-%D1%82%D0%B5%D0%BB%D0%B5%D1%84%D0%BE%D0%BD/");
    input.count=50;
    //printf("OKEY START PARSE COUNT: %d SITE: %s\n",input.count,input.search);
    CURL* curl=NULL;
    // site s;
    // CreateSite(&s,1000000000);
    //Read(&s);
    site s=GetSite(curl,input.search,100000000);
    for(int i=0;i<1000;i++){
        //SetSite(&s,curl,input.search);
        const char id[]="749348372";
        char buff[200];
        const char link[]="https://www.olx.ua/api/v1/offers/";
        int sizelink=strlen(link);
        strcpy(buff,link);
        strcpy(&buff[sizelink],id);
        strcpy(&buff[sizelink+strlen(id)],"/page-views/");
        //free(id);
        SetSitePost(&s,curl,buff,"access_token=668e88bcc07048328121d9219a01207d25a98ca7");
    }
    // //printf("HTML:\n%s\n",s.html);
    // Record(s.html,s.indexrecord,"search.html");
    // stdarray products=ParseSearchPage(&s,input);
    // ParseProductPage(&s,products,curl);
    

    //Record(s.html,s.indexrecord);
    DeleteSite(&s);
    return 0;
}