#include"include/corecurl.h"
void CreateSite(site* s,int maxsize){
    CreateStringInit(&s->html,maxsize);
    s->indexrecord=0;
}
void DeleteSite(site* s){
    DeleteString(&s->html);
    DeleteString(&s->url);
}
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *data)
{
    site* s=(site*)data;
    size_t realsize = size * nmemb;
    if(s->html.sizearray<s->indexrecord){
        printf("ERROR SIZE\n");
        return 0;
    }else{
        memcpy(s->html.chararray+s->indexrecord,ptr,realsize);
        s->indexrecord+=realsize;
    }
  return realsize;
}

site GetSite(CURL* curl,const char* url,int sizebuffer){
    CURLcode res;
    curl=curl_easy_init();
    site s;
    CreateSite(&s,sizebuffer);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&s);
    int start=clock();
    res=curl_easy_perform(curl);
    int end=clock();
    printf("get SITE TIME: %d\n",end-start);
    return s;
}
void SetSite(site* s,CURL* curl,const char* url){
    CURLcode res;
    s->indexrecord=0;
    CreateStringCopyConst(&s->url,url);
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,s);
    int start=clock();
    res=curl_easy_perform(curl);
    int end=clock();
    printf("get SITE TIME: %d\n",end-start);
}
void SetSitePost(site* s,CURL* curl,const char* url,const char* postfile){
    CURLcode res;
    s->indexrecord=0;
    CreateStringCopyConst(&s->url,url);
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,s);
    //access_token=4846206661a1b83024b20b1fc1a98df241c609ad
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,postfile);
    //curl_easy_setopt(curl, CURLOPT_COOKIE, "access_token=4846206661a1b83024b20b1fc1a98df241c609ad");
    int start=clock();
    res=curl_easy_perform(curl);
    int end=clock();
    printf("get SITE TIME: %d\n",end-start);
}