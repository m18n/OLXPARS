#include"include/olxmanager.h"
void CreateTask(task_t* task){
    task->fun=NULL;
    task->stat=NOT_INIT;
    task->data=NULL;
}
void ManagerFind(datapthread_t* info){
    findpthread_t* pth=(datapthread_t*)info->data;
    
    while (1)
    {
       for(int i=0;i<pth->arrtasks.length;i++){
            
           task_t* tasks=(task_t*)pth->arrtasks.array;
            
           if(tasks[i].stat==NOT_DONE){
                pthread_mutex_lock(&pth->mutex);
                if(tasks[i].stat==NOT_DONE)
                    tasks[i].stat=PROCESS;
                else{
                    pthread_mutex_unlock(&pth->mutex);
                    continue;
                }
                pthread_mutex_unlock(&pth->mutex);
                datapthread_t* in=malloc(sizeof(datapthread_t));
                in->data=tasks[i].data;
                in->pth=info->pth;
                task_t* t=&tasks[i];
                tasks[i].fun(in);
                pthread_mutex_lock(&pth->mutex);
                tasks[i].stat=DONE;
                pthread_mutex_unlock(&pth->mutex);
               
               
           }
          
       }
    }
    free(info);
}
void StartThreads(findpthread_t* self){
     for(int i=0;i<self->countpthread;i++){
        
        pthread_attr_t attr;
        pthread_attr_init(&attr);
       datapthread_t* info=malloc(sizeof(datapthread_t));
        info->data=self;
        info->pth=&self->pthfinds[i];
        pthread_create(&self->pthfinds[i], NULL,&ManagerFind,info);
        
        // pthread_create(&tid,&attr,Download,NULL);
    }
    self->stop=false;
}
void CreateFindPthread(findpthread_t* find){
    find->countpthread=0;
    find->stop=true;
    InitStdArraySize(&find->arrtasks,1000,sizeof(task_t));
    task_t* ts=(task_t*)find->arrtasks.array;
    for(int i=0;i<find->arrtasks.length;i++){
        CreateTask(&ts[i]);
    }
    find->StopThreads=StopThreads;
    find->StartThreads=StartThreads;
    find->AddTasks=AddTasks;
    find->pthfinds=NULL;
}
void AddTasks(findpthread_t* self,task_t task){
    pthread_mutex_lock(&self->mutex);
    task_t* ts=(task_t*)self->arrtasks.array;
    for(int i=0;i<self->arrtasks.length;i++){
        task_t* te=&ts[i];
        if(ts[i].stat==DONE||ts[i].stat==NOT_INIT){
           
            ts[i]=task;
            ts[i].stat=NOT_DONE;
            break;
        }
    }
    pthread_mutex_unlock(&self->mutex);
}
void InitFindPthread(findpthread_t* find,int count){
    CreateFindPthread(find);
    find->stop=false;
    find->countpthread=count;
    find->pthfinds=malloc(sizeof(pthread_t)*count);
    
}
void StopThreads(findpthread_t* self){
    self->stop=true;
     for(int i=0;i<FIND_THREAD;i++){
        pthread_join(self->pthfinds[i],NULL);
    }
    free(self->pthfinds);
}
void DeleteFindPthread(findpthread_t* find){
    StopThreads(find);
    DeleteStdArray(find->arrtasks);
}
void DownloadSearch(void*data){
    datapthread_t* d=(datapthread_t*)data;
    OlxSearch_t* olx=(OlxSearch_t*)d->data;
    
    site s=DownloadSite(olx->url,1000000000);
    printf("\nPRICE MIN:%d MAX:%d  DONWLOAD BYTE: %d THREAD: %d\n",olx->minprice,olx->maxprice,s.indexrecord,d->pth);
    free(d->data);
    free(data);
   
}