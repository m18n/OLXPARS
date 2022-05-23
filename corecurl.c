#include"include/corecurl.h"
void CreateSite(site* s,int maxsize){
    s->html=(char*)malloc(maxsize);
    s->indexrecord=0;
    s->size=maxsize;
}
void DeleteSite(site* s){
    free(s->html);
}
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *data)
{
    site* s=(site*)data;
    size_t realsize = size * nmemb;
    if(s->size<s->indexrecord){
        printf("ERROR SIZE\n");
        return 0;
    }else{
        memcpy(s->html+s->indexrecord,ptr,realsize);
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
    
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,s);
    int start=clock();
    res=curl_easy_perform(curl);
    int end=clock();
    printf("get SITE TIME: %d\n",end-start);
}
void SetSitePost(site* s,CURL* curl,const char* url){
    CURLcode res;
    s->indexrecord=0;
    
    curl=curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl,CURLOPT_URL,url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,s);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "authorization=Bearer 17397e6af1477154a2350cffb2e423031b847980");
    curl_easy_setopt(curl, CURLOPT_COOKIE, "mobile_default=desktop; fingerprint=MTI1NzY4MzI5MTs0OzA7MDswOzE7MDswOzA7MDswOzE7MTsxOzE7MTsxOzE7MTsxOzE7MTsxOzE7MTswOzE7MDswOzA7MDswOzA7MDswOzA7MDsxOzE7MDsxOzA7MDswOzA7MDsxOzA7MDswOzA7MDswOzA7MDswOzE7MDswOzA7MDswOzA7MTsxOzE7MDswOzE7MTswOzE7MDswOzE3MzM2ODcwMDsyOzI7MjsyOzI7Mjs1OzI4NDgwMDY0MTg7MTM1NzA0MTczODsxOzE7MTsxOzE7MTsxOzE7MTsxOzE7MTsxOzE7MTsxOzE7MDswOzA7MzE1NDY4MzIxMzszNDY5MzA2NTUxOzc3NzU3NjkzNzs3ODUyNDcwMjk7MzAyMTA1OTMzNjsxOTIwOzEwODA7MjQ7MjQ7MTgwOzEyMDsxODA7MTIwOzE4MDsxMjA7MTgwOzEyMDsxODA7MTIwOzE4MDsxMjA7MTgwOzEyMDsxODA7MTIwOzE4MDsxMjA7MTgwOzEyMDswOzA7MA==; ldTd=true; from_detail=0; laquesis=buy-1923@b#buy-2014@b#deluareb-1229@a#edu2r-3329@b#edu2r-3360@a#edu2r-3361@b#erm-724@a#erm-742@a#jobs-2491@a#jobs-3077@b; laquesisff=aut-716#euonb-114#euonb-48#kuna-307#oesx-1437#oesx-1643#oesx-645#oesx-867#olxeu-29763#srt-1289#srt-1346#srt-1434#srt-1593#srt-1758#srt-477#srt-479#srt-682; laquesissu=310@ad_page|1; observed_aui=796a819571774993bd3599c361ca02d2; _gid=GA1.2.1235528136.1653119897; __utmc=250720985; __utmz=250720985.1653119897.1.1.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); _hjSessionUser_2218922=eyJpZCI6IjBiY2JlNmIzLWJhODctNWQ2MS04MmE0LWY4OGVjOGFmMGViOCIsImNyZWF0ZWQiOjE2NTMxMTk4OTY3OTYsImV4aXN0aW5nIjp0cnVlfQ==; deviceGUID=343b78f7-8a90-4cef-8a0d-0dea2e798581; a_refresh_token=b0b72d43a58d5943715d501c83190b26b10f2e0b; a_grant_type=device; user_id=844313045; user_business_status=private; lister_lifecycle=1653120261; a_access_token=17397e6af1477154a2350cffb2e423031b847980; __utma=250720985.1390604199.1653119897.1653119897.1653219149.2; _hjIncludedInSessionSample=0; _hjSession_2218922=eyJpZCI6IjA0MDQxZGRjLTYwZDYtNDIzZC05YjFkLThlOTY5ZTlmOGFhYiIsImNyZWF0ZWQiOjE2NTMyMjM2OTc3NDEsImluU2FtcGxlIjpmYWxzZX0=; _hjAbsoluteSessionInProgress=1; sbjs_migrations=1418474375998%3D1; sbjs_current_add=fd%3D2022-05-22%2015%3A48%3A20%7C%7C%7Cep%3Dhttps%3A%2F%2Fwww.olx.ua%2Fd%2Fobyavlenie%2Fzazhigalka-elektricheskaya-tsvet-platinovyy-IDOuXGD.html%7C%7C%7Crf%3D%28none%29; sbjs_first_add=fd%3D2022-05-22%2015%3A48%3A20%7C%7C%7Cep%3Dhttps%3A%2F%2Fwww.olx.ua%2Fd%2Fobyavlenie%2Fzazhigalka-elektricheskaya-tsvet-platinovyy-IDOuXGD.html%7C%7C%7Crf%3D%28none%29; sbjs_current=typ%3Dtypein%7C%7C%7Csrc%3D%28direct%29%7C%7C%7Cmdm%3D%28none%29%7C%7C%7Ccmp%3D%28none%29%7C%7C%7Ccnt%3D%28none%29%7C%7C%7Ctrm%3D%28none%29; sbjs_first=typ%3Dtypein%7C%7C%7Csrc%3D%28direct%29%7C%7C%7Cmdm%3D%28none%29%7C%7C%7Ccmp%3D%28none%29%7C%7C%7Ccnt%3D%28none%29%7C%7C%7Ctrm%3D%28none%29; sbjs_udata=vst%3D1%7C%7C%7Cuip%3D%28none%29%7C%7C%7Cuag%3DMozilla%2F5.0%20%28X11%3B%20Linux%20x86_64%29%20AppleWebKit%2F537.36%20%28KHTML%2C%20like%20Gecko%29%20Chrome%2F101.0.0.0%20Safari%2F537.36; newrelic_cdn_name=CF; PHPSESSID=5n1mknh98vlankqir82slqotld; session_start_date=1653229168228; dfp_segment=%5B%5D; onap=180e59fcba3x206b7fe3-6-180ebcfba66x22c834ca-28-1653229170; _ga=GA1.1.1390604199.1653119897; _ga_QFCVKCHXET=GS1.1.1653223701.7.1.1653227485.60; lqstatus=1653228822|180eb768e6dx1bed0f7d|buy-2014|1655712167|310; sbjs_session=pgs%3D64%7C%7C%7Ccpg%3Dhttps%3A%2F%2Fwww.olx.ua%2Fd%2Fobyavlenie%2Fzazhigalka-dlya-gazovoy-plity-cricket-fireturbo-gnuschayasya-kachestvo-IDNp0UQ.html;");
    int start=clock();
    res=curl_easy_perform(curl);
    int end=clock();
    printf("get SITE TIME: %d\n",end-start);
}