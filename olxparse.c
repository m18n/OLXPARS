#include"include/olxparse.h"

void SetPageUrl(string* url,int newpage){
    int page=url->SearchWordIndex(url,0,url->length,1,"page=");
    if(page==-1){

        url->Add(&url,"page=");
        url->AddInt(&url,newpage);
        
    }else{
        page+=5;
        url->length=page;
        url->AddInt(&url,newpage);
    }
}
int GetCountPageUrl(site* site){
    int getblock=site->html.GetCountWord(&site->html,0,"\"css-1mi714g\"");
    int index=site->html.SearchWordIndex(&site->html,0,site->indexrecord,getblock,"\"css-1mi714g\"");
    index=site->html.SearchWordIndex(&site->html,index,site->indexrecord,1,">");
    index++;
    string str=site->html.GetStringSignEnd(&site->html,index,site->indexrecord,'<');
    int count=atoi(str.chararray);
    DeleteString(&str);
    return count;
}
void ParseProduct(IParseInfoProduct_t* self,InfoProduct_t* info,site* s){
    if(self->ParseLink!=NULL)
        self->ParseLink(self,info,s);
    if(self->ParsePrice!=NULL)
        self->ParsePrice(self,info,s);
    if(self->ParseDescript!=NULL)
        self->ParseDescript(self,info,s);
    if(self->ParseTime!=NULL)
        self->ParseTime(self,info,s);
    if(self->ParseNameProduct!=NULL)
        self->ParseNameProduct(self,info,s);
    
    
    
}
void CreateIParseInfoProduct(IParseInfoProduct_t* iparse){
    iparse->ParseDescript=NULL;
    iparse->ParseNameProduct=NULL;
    iparse->ParsePrice=NULL;
    iparse->ParseProduct=ParseProduct;
    iparse->ParseTime=NULL;
    iparse->ParseLink=NULL;
    iparse->start=0;
    iparse->end=0;
}
void ParseSearchLink(IParseInfoProduct_t* self,InfoProduct_t* info,site* s){
    int divstart=s->html.SearchWordIndex(&s->html,self->start,self->end,1,"\"css-1bbgabe\"");
    if(divstart==-1)
        return;
    //Show(&s->html[divstart],120);
    int href=s->html.SearchWordIndex(&s->html,divstart,self->end,1,"href=\"");
    href+=6;
    string link=s->html.GetStringSign(&s->html,href,'\"');
    info->url=link;
}
void ParseSearchPrice(IParseInfoProduct_t* self,InfoProduct_t* info,site* s){
    int in=self->start;
    int divprice=s->html.SearchWordIndex(&s->html,in,self->end,1,"\"ad-price\"");
    if(divprice==-1){
        return -1;
    }
    int end = s->html.SearchWordIndex(&s->html, divprice,self->end, 1, ".<");
    if(end==-1){
        self->start=divprice;
        info->price=-1;
        return;
    }
    //printf("END:\n");
    //Show(&s->html[end-10],10);
    int start=s->html.SearchWordIndex(&s->html,end,0,1,">");
    start++;
    /*if (end == start) {
        printf("ERROR\n");
        Show(&s->html[divprice], 2000);
    }*/
    string price=s->html.GetStringSignEnd(&s->html,start,end,'г');
    
    if (price.chararray == NULL) {
        printf("DIV PRICE : %d, START DIV: %d, END DIV: %d\n",divprice,start,end);
        printf("ERROR PARSE PRICE\n");
        return -2;
    }
    //printf("SIZE INDEX: %d\n",s->indexrecord);
    //printf("STR PRICE:\n");
    //Show(&s->html[start], end-start);
    //printf("PRICE CHAR: %s\n",price);
    
    //printf("PRICEE: %s\n",price);
    price.DeleteSymbol(&price,' ');
    int inpr=atoi(price.chararray);
    
    DeleteString(&price);
    
    info->price=inpr;
    

}
void ParseNameProduct(IParseInfoProduct_t* self,InfoProduct_t* info,site* s){
    int index=s->html.SearchWordIndex(&s->html,self->start,self->end,1,"css-v3vynn-Text eu5v0x0");
    index+=25;
    string name=s->html.GetStringSignEnd(&s->html,index,self->end,'<');
    info->name=name;
}
stdarray ParseAllProduct(OlxSearchSite_t* olx){
    printf("COUNT PAGE: %d\n",olx->countpage);
    int indexparse=olx->site->html.SearchWordIndex(&olx->site->html,0,olx->site->indexrecord,1,"<body>");
    int count=olx->site->html.GetCountWord(&olx->site->html,0,"\"l-card\"");
    olx->iparse.end=olx->site->html.SearchWordIndex(&olx->site->html,indexparse,olx->site->indexrecord,1,"\"l-card\"");
    InfoProduct_t* arrp=malloc(sizeof(InfoProduct_t)*count);
    for(int i=0;i<count;i++){
        InfoProduct_t p;
        CreateInfoProduct(&p);
        olx->iparse.start=olx->iparse.end;
        olx->iparse.end=olx->site->html.SearchWordIndex(&olx->site->html,olx->iparse.start,olx->site->indexrecord,2,"\"l-card\"");
        if(olx->iparse.end==-1)
            olx->iparse.end=olx->site->indexrecord;
        olx->iparse.ParseProduct(&olx->iparse,&p,olx->site);
        
        printf("INDEX: %d ",i);
        p.Show(&p);
        arrp[i]=p;
    }
    stdarray ar;
    ar.array=arrp;
    ar.size=count;
    return ar;
}
void CreateOlxSearchSite(OlxSearchSite_t* olx,site* site){
    CreateIParseInfoProduct(&olx->iparse);
    olx->iparse.ParseLink=ParseSearchLink;
    olx->iparse.ParsePrice=ParseSearchPrice;
    olx->iparse.ParseNameProduct=ParseNameProduct;
    olx->ParseAllProduct=ParseAllProduct;
    olx->site=site;
    olx->countpage=GetCountPageUrl(site);
}
void AnalizSearch(OlxAnalizSearch_t* self){
    
}
void CreateOlxAnalizSearch(OlxAnalizSearch_t* olx,string url){
    olx->AnalizSearch=AnalizSearch;
    olx->url=url;
}
void DeleteOlxAnalizSearch(OlxAnalizSearch_t* olx){
    DeleteString(&olx->url);
}

// void ProcLink(PSsearch* pr){
//     if(pr->link.chararray==NULL)
//         return;
//     // const char add[]="https://www.olx.ua";
//     // int sizeadd=strlen(add);
//     // char temp[300];
//     // memcpy(temp,add,sizeadd);
//     // memcpy(temp+sizeadd,pr->link,sizelink);
//     // int allsize=sizelink+sizeadd;
//     // temp[allsize]='\0';
//     // strcpy(pr->link,temp);
// }
// int ParsePrice(site* s,int* index,int count){
//     int in=*index;
//     int divprice=s->html.SearchWordIndex(&s->html,in,s->indexrecord,1,"\"ad-price\"");
//     if(divprice==-1){
//         return -1;
//     }
//     int end = s->html.SearchWordIndex(&s->html, divprice, s->indexrecord, 1, ".<");
//     //printf("END:\n");
//     //Show(&s->html[end-10],10);
//     int start=s->html.SearchWordIndex(&s->html,end,0,1,">");
//     start++;
//     /*if (end == start) {
//         printf("ERROR\n");
//         Show(&s->html[divprice], 2000);
//     }*/
//     string price=s->html.GetStringSignEnd(&s->html,start,end,'г');
    
//     if (price.chararray == NULL) {
//         printf("DIV PRICE : %d, START DIV: %d, END DIV: %d\n",divprice,start,end);
//         printf("ERROR PARSE PRICE\n");
//         return -2;
//     }
//     //printf("SIZE INDEX: %d\n",s->indexrecord);
//     //printf("STR PRICE:\n");
//     //Show(&s->html[start], end-start);
//     //printf("PRICE CHAR: %s\n",price);
    
//     //printf("PRICEE: %s\n",price);
//     price.DeleteSymbol(&price,' ');
//     int inpr=atoi(price.chararray);
//     DeleteString(inpr);
//     *index=end;
//     return inpr;
// }
// int StrTimeToMin(string str){
//     int sizearr = 0;
//     string* arr=Tok(str,':',&sizearr);
//     string h=arr[0];
//     string min=arr[1];
//     int ih=atoi(h.chararray);
//     int imin=atoi(min.chararray);
//     imin+=ih*60;
//     for (int i = 0; i < sizearr; i++) {
//         DeleteString(&arr[i]);
//     }
//     //printf("HOURSE: %s, MINUTES: %s\n",h,min);
//     return imin;
// }
// string ParseLink(site* s,int* index,int count){
//     int divstart=s->html.SearchWordIndex(&s->html,*index,s->indexrecord,1,"\"css-1bbgabe\"");
//     if(divstart==-1)
//         return;
//     //Show(&s->html[divstart],120);
//     int href=s->html.SearchWordIndex(&s->html,divstart,s->indexrecord,1,"href=\"");
//     href+=6;
//     string link=s->html.GetStringSign(&s->html,href,'\"');
//     *index=href;
//     return link;
// }
// timepost ParseTime(site* s,int* index,int count){
//     int startdiv=s->html.SearchWordIndex(&s->html,*index,s->indexrecord,1,"\"location-date\"");
//     if(startdiv==-1)
//     {
//         timepost t;
//         t.day=-1;
//         t.minutes=-1;
//         return t;
//     }
//     int start=s->html.SearchWordIndex(&s->html,startdiv,s->indexrecord,3,">");
//     start++;
//     int end=s->html.SearchWordIndex(&s->html,start,s->indexrecord,1,"</p>");
//     //Show(s->html+start,120);
//     int done=s->html.SearchWordIndex(&s->html,start,end,1,":");
//     int minutest=0;
//     string time;
//     timepost p;
//       p.day=0;
//     if(done==-1){
//         //printf("START %d, END %d, START DIV %d\n", start, end, startdiv);
//         time=s->html.GetStringSignEnd(&s->html,start,end,' ');
//         p.day=atoi(time.chararray);
//         minutest=p.day*1440;
//     }else{
//         int space=s->html.SearchWordIndex(&s->html,done,0,1," ");
//         time=s->html.GetStringSign(&s->html,space+1,'<');
//         // printf("START SHOW:\n");
//         // Show(&s->html[start],100);
//         // printf("END SHOW:\n");
//         // Show(&s->html[end], 100);
//         // printf("DONE:\n");
//         // Show(&s->html[done], 100);
//         minutest=StrTimeToMin(time);
//     }
    
   
//     p.minutes=minutest;
  
//     *index=end;

//        // printf("PARSE TIME: %s\n",time);
    
//     DeleteString(&time);
//     int a = 10;
//     return p;
// }
// stdarray ParseSearchPage(site* s,const char* url){
//     int indexparse=s->html.SearchWordIndex(&s->html,0,s->indexrecord,1,"<body>");
//     int count=s->html.GetCountWord(&s->html,0,"\"css-1bbgabe\"");
//     PSsearch* arrp=malloc(sizeof(PSsearch)*count);
//     for(int i=0;i<count;i++){
//         PSsearch p;
//         string link=ParseLink(s,&indexparse,i);
//         if(link.chararray==NULL)
//             break;
//         StringMove(&p.link,&link);
//         ProcLink(&p);
//         p.price=ParsePrice(s,&indexparse,i);
//         //printf("PSEARCH: PRICE[ %d ] LINK[ %s ]\n",p.price,p.link);
//         timepost time=ParseTime(s,&indexparse,i);
//         //printf("TIME DAY: %d, MINUTES: %d\n",time.day,time.minutes);
//         p.time=time;
//         arrp[i]=p;
//     }
//     stdarray ar;
//     ar.array=arrp;
//     ar.size=count;
//     return ar;
// }
// string ParseId(site* s){
//     int index=s->html.SearchWordIndex(&s->html,0,s->indexrecord,1,"\"css-9xy3gn-Text eu5v0x0\"");
//     index = s->html.SearchWordIndex(&s->html, index,s->indexrecord, 2, ">");
//     index++;
//     string view=s->html.GetStringSign(&s->html,index,'<');
//     return view;
// }
// int GetViews(site* s){
//     int in= s->html.SearchWordIndex(&s->html,0,s->indexrecord,1,":");
//     in++;
//     string vi=s->html.GetStringSign(&s->html,in,'}');
//     if(vi.chararray==NULL)
//         return -1;
//     int v=atoi(vi.chararray);
//     DeleteString(&vi);
//     return v;
// }
// void ShowPSearch(PSsearch* p){
//     printf("PSEARCH: PRICE[ %d ] LINK[ %s ]\n",p->price,p->link);
//     printf("VIEWS: [ %d ] COF: [ %f ] TIME DAY: %d, MINUTES: %d\n",p->countview,p->cof,p->time.day,p->time.minutes);
// }
// void ParseProductPage(site* s,stdarray ps,CURL* curl){
//     PSsearch* pr=ps.array;
//     int indexview=0;
//     string link;
//     link.Resize(&link,300);
//     for(int i=0;i<ps.size;i++){
//         SetSite(s,curl,pr[i].link.chararray);
        
//         string id=ParseId(s);
//         if(id.chararray==NULL){
//             pr[i].countview=-1;
//             ShowPSearch(&pr[i]);
//             continue;
//         }
//         char buff[200];
        
        
//         CreateStringCopyConst(&link,"https://www.olx.ua/api/v1/offers/");
//         link.Add(&link,id.chararray);
//         link.Add(&link,"/page-views/");
//         DeleteString(&id);
//         SetSitePost(s,curl,buff,"access_token=fbe921f88fcfef8f26c2e23fcd8611b290311666");
//         Record(s->html.chararray,s->indexrecord,"views.html");
//         int views=GetViews(s);
//         pr[i].countview=views;
//         float cof=(34560-pr[i].time.minutes)/(double)pr[i].countview;
//         pr[i].cof=cof;
//         ShowPSearch(&pr[i]);
        
        
//     }
// }
// int GetCountPage(site* s){
//     int c=s->html.GetCountWord(&s->html,0,"\"css-1mi714g\"");
//     int end=s->html.SearchWordIndex(&s->html,0,s->indexrecord,c,"\"css-1mi714g\"");
//     end=s->html.SearchWordIndex(&s->html,end,s->indexrecord,1,">");
//     end++;
//     int pages=0;
//     string page=s->html.GetStringSign(&s->html,end,'<');
   
//     pages=atoi(page.chararray);
//     DeleteString(&page);
//     printf("COUNT PAGE: %d\n",pages);
//     if(pages==0)
//         return 1;
//     return pages;
// }
// void NextPage(string url,char* result){
//     string argum;
//     CreateStringCopyConst(&argum,"page=");
//     string arg=GetGETArg(url,argum);
//     int page=atoi(arg.chararray);
//     page++;
//     DeleteString(&arg);
//     char buff[200];
//     snprintf(buff,200,"%d",page);
//     SetGETArg(url,result,"page=",buff);
// }
// int GetPage(char* url){
//     char*arg=GetGETArg(url,);
//     int page=atoi(arg);
//     free(arg);
//     return page;
// }
// void SetPage(char* url,int page){
//     char buff[200];
//     snprintf(buff,200,"%d",page);
//     SetGETArg(url,url,"page=",buff);
// }
// void NewMaxPrice(char* url,int price){
    
//     char buff[200];
//     snprintf(buff,200,"%d",price);
//     SetGETArg(url,url,"3Ato%5D=",buff);
// }
// void NewMinPrice(char* url,int price){
    
//     char buff[200];
//     snprintf(buff,200,"%d",price);
//     SetGETArg(url,url,"3Afrom%5D=",buff);
// }