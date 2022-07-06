#include"include/olxmanager.h"
void CreateTask(task_t* task){
    task->fun=NULL;
    task->stat=NOT_DONE;
}
void ManagerFind(void* task_find){
    stdarray_t* arr_tasks=(stdarray_t*)task_find;
    task_t* tasks=(task_t*)arr_tasks->array;

    while (1)
    {
       for(int i=0;i<arr_tasks->length;i++){
           if(tasks[i].stat==NOT_DONE){
               tasks[i].fun();
           }
       }
    }
    
}
void CreateFindPthread(stdarray_t* tasks_find){
   pthread_t* finds=malloc(sizeof(pthread_t)*FIND_THREAD);
   for(int i=0;i<FIND_THREAD;i++){
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
       pthread_create(&finds[i], NULL,&ManagerFind,tasks_find);
      
        // pthread_create(&tid,&attr,Download,NULL);
    }
}
void DeleteFindPthread(pthread_t* finds){
    for(int i=0;i<FIND_THREAD;i++){
        pthread_join(finds[i],NULL);
    }
    free(finds);
}