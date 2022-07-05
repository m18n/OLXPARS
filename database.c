#include"include/database.h"
void ShowOlxSearchLink(struct olxsearchlink* self){
    printf("ID: %d LINK: %s\n",self->id,self->link);
}
void InitOlxSearchLink(olxsearchlink_t* olx,char* link,int id){
    olx->id=id;
    olx->link=link;
    olx->Show=ShowOlxSearchLink;
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
olxsearchlink_t* GetSearchLink(struct olxdatabase* self,int start,int end,int* size){
    char buffsql[1000];
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
    sqlite3_stmt* res;
    sqlite3_prepare_v2(self->db,buffsql,-1,&res,0);
    int sizelocal=end-start;
    olxsearchlink_t* links=malloc(sizeof(olxsearchlink_t)*sizelocal);
    int n=0;
    while (sqlite3_step(res)==SQLITE_ROW)
    {
        int id = sqlite3_column_int(res,0); // = query.getColumn(0).getInt();
        char* link=sqlite3_column_text(res,1);
        olxsearchlink_t olx;
        InitOlxSearchLink(&olx,link,id);
        int length=strlen(link);
        olx.link=malloc(sizeof(char)*length);
        strcpy(olx.link,link);
        links[n]=olx;
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
    sqlite3_open(namedatabase,&olx->db);
}
void DestroyDataBase(olxdatabase_t* olx){
    sqlite3_close(olx->db);
}