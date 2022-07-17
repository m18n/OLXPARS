#include"include/corecurl.h"
void CreateSite(site* s,int maxsize){
    CreateStringInit(&s->html,maxsize);
    s->indexrecord=0;
    CreateString(&s->url);
}
void DeleteSite(site* s){
    DeleteString(s->html);
    DeleteString(s->url);
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
        
        s->html.length=s->indexrecord;
    }
  return realsize;
}

site DownloadSite(const char* url,int maxsize){
    CURLcode res;
    CURL* curl=curl_easy_init();
    site s;
    CreateSite(&s,maxsize);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,&s);
    clock_t start = clock();
    res=curl_easy_perform(curl);
    clock_t end = clock();
     double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("DOWNLOAD SITE time: %f seconds\n", seconds);

    return s;
}
void DownloadSitePtr(site* s,CURL* curl,const char* url){
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
void DownloadSitePtrPOST(site* s,CURL* curl,const char* url,const char* postfile){
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