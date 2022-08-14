#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include"include/core.h"
#include"include/olxparse.h"
#include"include/olxmanager.h"
#include <unistd.h>
#include <math.h>
#include"include/database.h"
findpthread_t find;
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
void* Download(void* empty){
   
 site s=DownloadSite("https://www.olx.ua/d/obyavlenie/odnorazki-elf-bar-pustye-bez-zhidkosti-IDP0B3Y.html",10000000);
 DeleteSite(&s);
}
void Test(CURL* curl){
    pthread_t* tids=malloc(sizeof(pthread_t)*200);
  clock_t start = clock();
    
    for(int i=0;i<150;i++){
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
       pthread_create(&tids[i], NULL, &Download, NULL);
      
        // pthread_create(&tid,&attr,Download,NULL);
    }

    for(int i=0;i<150;i++){
        pthread_join(tids[i],NULL);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("The time: %f seconds\n", seconds);
}
void InputLink(olxdatabase_t* olx){
   
  while(true){
    printf("INPUT LINK AND MIN PRICE,MAX PRICE : EXIT: 0\n");
    int size=LINK_S+6;
    char data[size];
    strget(data,size,stdin);
    if(strcmp(data,"0")==0){
      printf("END INPUT LINK\n");
      break;
    }else{
      string d;
      CreateStringRef(&d,data,size);
      int rsize=0;
      string* str=Tok(d,' ',&rsize);
      if(rsize>=2)
        olx->AddSearchLink(olx,str[0].chararray,str[1].chararray,str[2].chararray);
      DeleteStringArr(str,rsize);
    }
  }
}
void IndexNext(int size,int *index,int *end){
  if(size-*end>10){
    *index=*end;
    *end+=10;
  }
  else{
    if(*end+size-*end!=*end){
      *index=*end;
      *end+=size-*end;
    }
  }
  return end;
}
void IndexBack(int size,int *index,int *end){
  if(*end>10){
    *end=*index;
    *index-=10;
  }else{
    *index=0;
    if(size>10)
      *end=10;
    else
      *end=size;
  }
  return end;
}
bool CheckId(void* elem1,void* elem2){
  olxsearchlink_t* olx=(olxsearchlink_t*)elem1;
  int id2=(int)elem2;
  if(olx->id==(int)elem2){
    return true;
  }
  return false;
}
void ShowLink(olxdatabase_t* olx){
  int size=0;
  stdarray_t arr=olx->GetSearchLink(olx,0,0,&size);
  int index=0;
  int end=0;
  IndexNext(size,&index,&end);
  while(true){
    olxsearchlink_t* s=(olxsearchlink_t*)arr.array;
    
    for(int i=index;i<end;i++){
        s[i].Show(&s[i]);
  
      }
    printf("NEXT | 0\nBACK | 1\nREMOVE ID | 2\nEXIT | 3\n");
    int number=0;
    scanf("%d",&number);
    if(number==0){
      
      IndexNext(size,&index,&end);
      system("clear");
    }else if(number==1){
      
      IndexBack(size,&index,&end);
      system("clear");
    }else if(number==2){
      char id[200];
      printf("INPUT ID: ");
      strget(id,200,stdin);
      string td;
      CreateString(&td);
      td.SetRefArray(&td,id,200);
      int sizes=0;
      string* str=Tok(td,' ',&sizes);
      for(int i=0;i<sizes;i++){
       
        printf("ID: %s\n",str[i].chararray);
        int id=atoi(str[i].chararray);
        int index=arr.SearchItemPred(&arr,id,CheckId);
        if(index!=-1){
          printf("INDEX: %d\n",index);
          s[index].DeleteOnDataBase(&s[index]);
          arr.DeleteElement(&arr,index);
          s=(olxsearchlink_t*)arr.array;
          size--;
        }
        DeleteString(str[i]);
      }
      end=0;
      index=0;
      IndexNext(size,&index,&end);
      IndexBack(size,&index,&end);
      system("clear");
    }else if(number==3){
      break;
    }
  
  }
  for(int i=0;i<size;i++){
     olxsearchlink_t* s=(olxsearchlink_t*)arr.array;
    DestroyOlxSearchLink(s[i]);
  }
  DeleteStdArray(arr);
}
int RoundUp(int n){
  if(n%50!=0){
    if ( n / 10 % 10 < 5 ){
      n = (n / 100 + 1) * 100;
      n-=50;
    }
    else{
      n = (n / 100 + 1) * 100;
     
    }
  }
return n;
}
int RoundDown(int n){
  if(n%50!=0){
    if ( n / 10 % 10 < 5 ){
      n = n / 100 * 100;
      
    }
    else{
       n = n / 100 * 100;
      n+=50;
    }
  }
return n;
}
void StartAnaliz(olxdatabase_t* olx){
    system("clear");
  int size=0;
  stdarray_t arr=olx->GetSearchLink(olx,0,0,&size);
  olxsearchlink_t* s=(olxsearchlink_t*)arr.array;
  
  printf("ANALIZ LINKS START\n");
  CreateFindPthread(&find);
  InitFindPthread(&find,10);
  find.StartThreads(&find);
  for(int i=0;i<arr.length;i++){
    s[i].Show(&s[i]);
   
    int minprice=RoundUp(s[i].minprice);
    printf("MIN PRICE: %d\n",minprice);
    int maxprice=RoundDown(s[i].maxprice);
    printf("MAX PRICE: %d\n",maxprice);
    for(int j=minprice;j<maxprice;j+=50){
      task_t task;
      CreateTask(&task);
      OlxSearch_t* olx=malloc(sizeof(OlxSearch_t));
      CreateOlxSearch(olx);
      olx->minprice=j;
      olx->maxprice=j;
      strcpy(olx->url,s[i].link);
      task.data=olx;
      task.fun=DownloadSearch;
      find.AddTasks(&find,task);
      OlxSearch_t* olx2=malloc(sizeof(OlxSearch_t));
      CreateOlxSearch(olx2);
      olx2->minprice=j+1;
      olx2->maxprice=j+49;
       strcpy(olx2->url,s[i].link);
      task.data=olx2;
      find.AddTasks(&find,task);
      if(j==maxprice-50){
        OlxSearch_t* olx3=malloc(sizeof(OlxSearch_t));
        CreateOlxSearch(olx3);
        olx3->minprice=j+50;
        olx3->maxprice=j+50;
         strcpy(olx3->url,s[i].link);
        task.data=olx3;
        find.AddTasks(&find,task);
      }
  
    }
    // for(int j=s[i].minprice;j<=s[i].maxprice;j+=50){
    //   printf("URL: %s PRICE: %d\n",s[i].link,j);
    // }
    
  }

  int number=0;
  scanf("%d",&number);
  for(int i=0;i<arr.length;i++){
    DestroyOlxSearchLink(s[i]);
  }
}
void Menu(olxdatabase_t* olx){
  while (true)
  {
 
  
  printf("HAY MENU OLXANL\nSHOW LINKS ANALIZ | 0\nADD LINKS ANALIZ | 1\nSTART ANALIZ LINK | 2\nEXIT | 3\n");
  printf("INPUT NUMBER ITEM:");
  int number=0;
  scanf("%d",&number);
  system("clear");
  if(number==0){
    ShowLink(olx);
  }else if(number==1){
    InputLink(olx);
  }else if(number==2){
    StartAnaliz(olx);
  }else if(number==3){
    break;
  }
  system("clear");
  }
}
int main(){
    system("clear");
    olxdatabase_t olx;
    InitDataBase(&olx,"olx.sqlite");
    Menu(&olx);
    //strcpy(input.search,"https://www.olx.ua/d/list/q-car/?search%5Bfilter_float_price%3Afrom%5D=10&search%5Bfilter_float_price%3Ato%5D=200&page=1");    
    CURL* curl=NULL;
  //Test(curl);
    //sleep(10000);
    site s=DownloadSite("https://www.olx.ua/d/uk/obyavlenie/umnyy-smart-fitnes-braslet-chasy-treker-xiaomi-mi-band-mi-bend-5-6-IDNpx7q.html",10000000);
    Record(s.html.chararray,s.indexrecord,"my.html");
    
    // OlxSearchSite_t olx;
    // CreateOlxSearchSite(&olx,&s);
    // olx.ParseAllProduct(&olx);
    // DeleteSite(&s);
    return 0;
}