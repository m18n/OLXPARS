#include"include/database.h"
void ShowOlxSearchLink(struct olxsearchlink* self){
    printf("ID: %d LINK: %s\n",self->id,self->link);
}
void DeleteDataBaseOlxSearchLink(struct olxsearchlink* self){
    char buffsql[1000];
    strcpy(buffsql,"DELETE FROM LinkSearch WHERE id=\"");
    char buffint[100];
    snprintf(buffint,200,"%d",self->id);
    int length=strlen(buffsql);
    strcpy(&buffsql[length],buffint);
    length=strlen(buffsql);
    strcpy(&buffsql[length],"\"");
    sql_exec(self->db,buffsql);
}
void InitOlxSearchLink(olxsearchlink_t* olx,char* link,int id,sqlite3* db){
    olx->id=id;
    olx->link=link;
    olx->Show=ShowOlxSearchLink;
    olx->DeleteOnDataBase=DeleteDataBaseOlxSearchLink;
    olx->db=db;
}
void DestroyOlxSearchLink(olxsearchlink_t* olx){
    free(olx->link);
}

void sql_exec(sqlite3* db,const char* sql){
    char* error=NULL;
    sqlite3_exec(db,sql,0,0,&error);
    if(error!=NULL){
        printf("ERROR SQL: %s\n",error);
    }
}
int GetCount(olxdatabase_t* self){
    char buffsql[1000];
    strcpy(buffsql,"SELECT COUNT(*) FROM LinkSearch");
    sqlite3_stmt* res;
    sqlite3_prepare_v2(self->db,buffsql,-1,&res,0);
    sqlite3_step(res);
    int count=sqlite3_column_int(res,0);
    sqlite3_finalize(res);
    return count;
}
stdarray_t GetSearchLink(struct olxdatabase* self,int start,int end,int* size){
    char buffsql[1000];
    int sizelocal=end-start;
    if(end!=start){
        strcpy(buffsql,"SELECT * FROM LinkSearch ORDER BY id LIMIT ");
        int length=strlen(buffsql);
        char buffint[200];
        snprintf(buffint,200,"%d",start);
        strcpy(&buffsql[length],buffint);
        length=strlen(buffsql);
        stpcpy(&buffsql[length],",");
        length++;
        snprintf(buffint,200,"%d",end);
        strcpy(&buffsql[length],buffint);
        length=strlen(buffsql);
        strcpy(&buffsql[length],";");
    }else{
        sizelocal=GetCount(self);
        strcpy(buffsql,"SELECT * FROM LinkSearch");
    }
    sqlite3_stmt* res;
    sqlite3_prepare_v2(self->db,buffsql,-1,&res,0);
    stdarray_t links;
    InitStdArraySize(&links,sizelocal,sizeof(olxsearchlink_t));
   
    int n=0;
    while (sqlite3_step(res)==SQLITE_ROW)
    {
        olxsearchlink_t* linke=(olxsearchlink_t*)links.array;
        int id = sqlite3_column_int(res,0); // = query.getColumn(0).getInt();
        char* link=sqlite3_column_text(res,1);
        olxsearchlink_t olx;
        InitOlxSearchLink(&olx,link,id,self->db);
        int length=strlen(link);
        olx.link=malloc(sizeof(char)*length);
        strcpy(olx.link,link);
        linke[n]=olx;
        n++;
        
    }
    sqlite3_finalize(res);
    *size=n;
    return links;
}
void AddSearchLink(olxdatabase_t* self,char link[LINK_S]){
    char buffsql[1000];
    strcpy(buffsql,"INSERT INTO LinkSearch (link) VALUES ('");
    int length=strlen(buffsql);
    strcpy(&buffsql[length],link);
    length=strlen(buffsql);
    strcpy(&buffsql[length],"');");
    sql_exec(self->db,buffsql);
}
void InitDataBase(olxdatabase_t* olx,const char namedatabase[50]){
    strcpy(olx->namedatabase,namedatabase);
    olx->AddSearchLink=AddSearchLink;
    olx->GetSearchLink=GetSearchLink;
    olx->GetCount=GetCount;
    sqlite3_open(namedatabase,&olx->db);
}
void DestroyDataBase(olxdatabase_t* olx){
    sqlite3_close(olx->db);
}