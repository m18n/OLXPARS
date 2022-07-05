#pragma once
#include"olxparse.h"
#include<stdbool.h>
#include<pthread.h>
#define FIND_THREAD 10
#define NOT_DONE 0
#define PROСESS 1
#define DONE 2
typedef char status_task;
typedef struct task{
    void(*fun)();
    status_task stat; 
}task_t;
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
//             stdarray products=ParseSearchPage(&s,urlf);
//             ParseProductPage(&s,products,curl);
            
//             free(products.array);
//             NextPage(urlf,urlf);
           
//         }
//         min++;
//         max++;
//     }
    
        
    
// }

void ManagerFind(void*em);
void CreateFindPthread(stdarray* tasks_find);
void DeleteFindPthread(pthread_t* finds);