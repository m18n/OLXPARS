#include"include/olxparse.h"
void ProcLink(PSsearch* pr){
    if(pr->link==NULL)
        return;
    const char add[]="https://olx.ua";
    int sizeadd=strlen(add);
    int sizelink=strlen(pr->link);
    char temp[300];
    memcpy(temp,add,sizeadd);
    memcpy(temp+sizeadd,pr->link,sizelink);
    int allsize=sizelink+sizeadd;
    temp[allsize]='\0';
    strcpy(pr->link,temp);
}
int ParsePrice(site* s,int* index,int count){
    int in=*index;
    int divprice=SearchWordIndex(s->html,in,s->indexrecord,1,"\"ad-price\"");
    if(divprice==-1){
        return -1;
    }
    int end = SearchWordIndex(s->html, divprice, s->indexrecord, 1, ".<");
    //printf("END:\n");
    //Show(&s->html[end-10],10);
    int start=SearchWordIndex(s->html,end,0,1,">");
    start++;
    /*if (end == start) {
        printf("ERROR\n");
        Show(&s->html[divprice], 2000);
    }*/
    char* price=GetStringSign(s->html,end,start,' ');
    if (price == NULL) {
        printf("DIV PRICE : %d, START DIV: %d, END DIV: %d\n",divprice,start,end);
        printf("ERROR PARSE PRICE\n");
        return -2;
    }
    //printf("SIZE INDEX: %d\n",s->indexrecord);
    //printf("STR PRICE:\n");
    //Show(&s->html[start], end-start);
    //printf("PRICE CHAR: %s\n",price);

    int inpr=atoi(price);
    free(price);
    *index=end;
    return inpr;
}
int StrTimeToMin(char* str){
    int sizearr = 0;
    char** arr=Tok(str,':',&sizearr);
    char* h=arr[0];
    char* min=arr[1];
    int ih=atoi(h);
    int imin=atoi(min);
    imin+=ih*60;
    for (int i = 0; i < sizearr; i++) {
        free(arr[i]);
    }
    
    //printf("HOURSE: %s, MINUTES: %s\n",h,min);
    return imin;
}
char* ParseLink(site* s,int* index,int count){
    int divstart=SearchWordIndex(s->html,*index,s->indexrecord,1,"\"css-1bbgabe\"");
    if(divstart==-1)
        return NULL;
    //Show(&s->html[divstart],120);
    int href=SearchWordIndex(s->html,divstart,s->indexrecord,1,"href=\"");
    href+=6;
    char* link=GetStringSign(s->html,s->indexrecord,href,'\"');
    *index=href;
    return link;
}
timepost ParseTime(site* s,int* index,int count){
    int startdiv=SearchWordIndex(s->html,*index,s->indexrecord,1,"\"location-date\"");
    if(startdiv==-1)
    {
        timepost t;
        t.day=-1;
        t.minutes=-1;
        return t;
    }
    int start=SearchWordIndex(s->html,startdiv,s->indexrecord,3,">");
    start++;
    int end=SearchWordIndex(s->html,start,s->indexrecord,1,"</p>");
    //Show(s->html+start,120);
    int done=SearchWordIndex(s->html,start,end,1,":");
    int minutest=0;
    char* time=NULL;
    timepost p;
      p.day=0;
    if(done==-1){
        //printf("START %d, END %d, START DIV %d\n", start, end, startdiv);
        time=GetStringSign(s->html,end,start,' ');
        p.day=atoi(time);
    }else{
        int space=SearchWordIndex(s->html,done,0,1," ");
        time=GetStringSign(s->html,s->indexrecord,space+1,'<');
        // printf("START SHOW:\n");
        // Show(&s->html[start],100);
        // printf("END SHOW:\n");
        // Show(&s->html[end], 100);
        // printf("DONE:\n");
        // Show(&s->html[done], 100);
        minutest=StrTimeToMin(time);
    }
    
   
    p.minutes=minutest;
  
    *index=end;

       // printf("PARSE TIME: %s\n",time);
    
    free(time);
    int a = 10;
    return p;
}
stdarray ParseSearchPage(site* s,olxdata data){
    int indexparse=SearchWordIndex(s->html,0,s->indexrecord,1,"<body>");
    PSsearch* arrp=malloc(sizeof(PSsearch)*data.count);
    for(int i=0;i<data.count;i++){
        PSsearch p;
        char*link=ParseLink(s,&indexparse,i);
        if(link==NULL)
            break;
        strcpy(p.link,link);
        free(link);
        ProcLink(&p);
        p.price=ParsePrice(s,&indexparse,i);
        printf("PSEARCH: PRICE[ %d ] LINK[ %s ]\n",p.price,p.link);
        timepost time=ParseTime(s,&indexparse,i);
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
    int index=SearchWordIndex(s->html,0,s->indexrecord,1,"\"css-9xy3gn-Text eu5v0x0\"");
    index = SearchWordIndex(s->html, 0,index, 1, ":");
    index++;
    
    char* view=GetStringSign(s->html,s->indexrecord,index+1,'<');
    printf("VIEW: %s\n",view);
}
void ParseProductPage(site* s,stdarray ps,CURL* curl){
    PSsearch* pr=ps.array;
    int indexview=0;
    for(int i=0;i<1;i++){
        SetSite(s,curl,pr[i].link);
        //Record(s->html,s->indexrecord);
        ParseViews(s);
    }
}