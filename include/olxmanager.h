#pragma once
#include"olxparse.h"
#include<stdbool.h>
#include <unistd.h>
#include<pthread.h>
#define FIND_THREAD 10
#define NOT_INIT 0
#define NOT_DONE 1
#define PROCESS 2
#define DONE 3

typedef char status_task;
typedef struct task{
    void(*fun)(void* data);
    void* data;
    status_task stat; 
}task_t;
/*
Статуси FIND PTHREAD
void* data
1=Знаходження найдорожчого оголошення
2=Знаходження кроку для категорії
3=
4=
5=
6=
*/
void CreateTask(task_t* task);

// void ParseOlxPages(CURL* curl,const char* url){
//     int sizeurl=strlen(url);
//     site s=GetSite(curl,url,10000000);
    
//     char urlf[400];
//     strcpy(urlf,url);
//     int min=10;
//     int max=11;
//     int pages=1;
//     while (pages!=0)
//     {
//         SetPage(urlf,1);
//         NewMinPrice(urlf,min);
//         NewMaxPrice(urlf,max);
//         SetSite(&s,curl,urlf);
//         pages=GetCountPage(&s);
//         printf("\nURL: %s\n\n",urlf);
//         for(int i=0;i<pages;i++){
//             printf("\nURL: %s\n\n",urlf);
//             SetSite(&s,curl,urlf);
//             stdarray_t products=ParseSearchPage(&s,urlf);
//             ParseProductPage(&s,products,curl);
            
//             free(products.array);
//             NextPage(urlf,urlf);
           
//         }
//         min++;
//         max++;
//     }
    
        
    
// }
typedef struct datapthread
{
    void* data;
    pthread_t* pth;
} datapthread_t;


void DownloadSearch(void*data);
typedef struct findpthread{
    int countpthread;
    stdarray_t arrtasks;
    bool stop;
    void(*StartThreads)(struct findpthread* self);
    void(*AddTasks)(struct findpthread* self,task_t task);
    void(*StopThreads)(struct findpthread* self);
    pthread_t* pthfinds;
    pthread_mutex_t mutex;
}findpthread_t;
void ManagerFind(datapthread_t* info);
void StopThreads(findpthread_t* self);
void AddTasks(findpthread_t* self,task_t taks);
void StartThreads(findpthread_t* self);
void CreateFindPthread(findpthread_t* find);
void DeleteFindPthread(findpthread_t* find);
void InitFindPthread(findpthread_t* find,int count);