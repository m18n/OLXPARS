#include"include/olxparse.h"
void ProcLink(PSsearch* pr){
    
    const char add[]="https://olx.ua";
    int sizeadd=strlen(add);
    int sizelink=strlen(pr->link);
    char temp[200];
    memcpy(temp,add,sizeadd);
    memcpy(temp+sizeadd,pr->link,sizelink);
    int allsize=sizelink+sizeadd;
    temp[allsize]='\0';
    strcpy(pr->link,temp);
}
int ParsePrice(site* s,int* index,int count){
    int in=*index;
    in=SearchWordIndex(s->html,in,s->indexrecord,1,"\"ad-price\"");
   
    // char test=s->html[in+1200];
    // s->html[in+1200]='\0';
    // printf("\n%s\n",&s->html[in]);
    // s->html[in+1200]=test;
    in=SearchWordIndex(s->html,in,s->indexrecord,1,"грн");
    
    int end=in;
    in=SearchWordIndex(s->html,in,0,1,">");
    in+=1;
    
    end=end-in;
    char* price=GetStringSign(s->html,s->indexrecord,in,'.');
    price[end]='\0';
    int inpr=atoi(price);
    free(price);
    *index=in;
    return inpr;
}
int StrTimeToMin(char* str){
    char** arr=Tok(str,':');
    char* h=arr[0];
    char* min=arr[1];
    int ih=atoi(h);
    int imin=atoi(min);
    imin+=ih*60;
    //printf("HOURSE: %s, MINUTES: %s\n",h,min);
    return imin;
}
char* ParseLink(site* s,int* index,int count){
    *index=SearchWordIndex(s->html,*index,s->indexrecord,1,"data-cy=\"l-card\"");
    *index=SearchWordIndex(s->html,*index,s->indexrecord,1,"href=\"");
    *index+=6;
    char* link=GetStringSign(s->html,s->indexrecord,*index,'\"');
    
    return link;
}
timepost ParseTime(site* s,int* index,int count){
    *index=SearchWordIndex(s->html,*index,s->indexrecord,1,"\"location-date\"");
    int start=SearchWordIndex(s->html,*index,s->indexrecord,3,">");
    start++;
    int end=SearchWordIndex(s->html,*index,s->indexrecord,1,"</p>");
    //Show(s->html+start,120);
    int done=SearchWordIndex(s->html,start,end,1,":");
    int minutest=0;
    char* time;
    timepost p;
      p.day=0;
    if(done==-1){
        time=GetStringSign(s->html,s->indexrecord,start,' ');
        p.day=atoi(time);
    }else{
        int space=SearchWordIndex(s->html,done,0,1," ");
        time=GetStringSign(s->html,s->indexrecord,space+1,'<');
        minutest=StrTimeToMin(time);
    }
    
   
    p.minutes=minutest;
  
    *index=end;
    free(time);
    
    return p;
}
stdarray ParseSearchPage(site* s,olxdata data){
    int indexprice=0;
    int indexlink=0;
    int indextime=0;
    PSsearch* arrp=malloc(sizeof(PSsearch)*data.count);
    for(int i=0;i<data.count;i++){
        PSsearch p;
        p.price=ParsePrice(s,&indexprice,i);
        char*link=ParseLink(s,&indexlink,i);
        strcpy(p.link,link);
        free(link);
        ProcLink(&p);
        printf("PSEARCH: PRICE[ %d ] LINK[ %s ]\n",p.price,p.link);
        timepost time=ParseTime(s,&indextime,i);
        printf("TIME DAY: %d, MINUTES: %d\n",time.day,time.minutes);
        p.time=time;
        arrp[i]=p;
    }
    stdarray ar;
    ar.array=arrp;
    ar.size=data.count;
    return ar;
}
int ParseViews(site* s){
    int index=SearchWordIndex(s->html,0,s->indexrecord,1,"\"page-view-text\"");
    index=SearchWordIndex(s->html,index,s->indexrecord,1,":");
    char* view=GetStringSign(s->html,s->indexrecord,index+1,'<');
    printf("VIEW: %s\n",view);
}
void ParseProductPage(site* s,stdarray ps,CURL* curl){
    PSsearch* pr=ps.array;
    int indexview=0;
    for(int i=0;i<1;i++){
        SetSite(s,curl,pr[i].link);
        Record(s->html,s->indexrecord);
        ParseViews(s);
    }
}